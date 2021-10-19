#include "ArchiveWriter.h"

#include <bit>
#include <iostream>

#include "Common.h"

ArchiveWriter::ArchiveWriter(std::string_view archive_name) : output_(archive_name, std::ios::binary | std::ios::out) {
}

ArchiveWriter::~ArchiveWriter() {
    if (buffer_ptr_ > 0) {
        output_.write(reinterpret_cast<const char*>(&buffer_), sizeof buffer_);
    }
}

void ArchiveWriter::WriteBit(bool bit) {
    if (buffer_ptr_ == BYTE_SIZE) {
        output_.write(reinterpret_cast<const char*>(&buffer_), sizeof buffer_);
        buffer_ = 0;
        buffer_ptr_ = 0;
    }
    if constexpr (std::endian::native != std::endian::big) {
        buffer_ |= (static_cast<uint8_t>(bit) << buffer_ptr_);
    } else {
        buffer_ |= (static_cast<uint8_t>(bit) << (BYTE_SIZE - 1 - buffer_ptr_));
    }
    ++buffer_ptr_;
}

void ArchiveWriter::Write9Bits(uint16_t bits) {
    for (size_t i = 0; i < 9; ++i) {
        WriteBit((bits >> i) & 1);
    }
}
