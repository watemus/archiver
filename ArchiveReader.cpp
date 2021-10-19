#include "ArchiveReader.h"

#include "Common.h"

ArchiveReader::ArchiveReader(std::string_view archive_name) : input_(archive_name, std::ios::binary | std::ios::in){
}

bool ArchiveReader::ReadBit() {
    if (buffer_ptr_ == BYTE_SIZE) {
        buffer_ptr_ = 0;
    }
    if (buffer_ptr_ == 0) {
        input_.read(reinterpret_cast<char*>(&buffer_), sizeof buffer_);
    }
    bool bit;
    if constexpr (std::endian::native != std::endian::big) {
        bit = ((buffer_ >> buffer_ptr_) & 1);
    } else {
        bit = ((buffer_ >> (BYTE_SIZE - 1 - buffer_ptr_)) & 1);
    }
    ++buffer_ptr_;
    return bit;
}

uint16_t ArchiveReader::Read9Bits() {
    uint16_t res = 0;
    for (size_t i = 0; i < 9; ++i) {
        res |= (static_cast<uint16_t>(ReadBit()) << i);
    }
    return res;
}
