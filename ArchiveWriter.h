#pragma once

#include <fstream>
#include <vector>

class ArchiveWriter {
    std::ofstream output_;
    uint8_t buffer_ = 0;
    size_t buffer_ptr_ = 0;

public:
    ArchiveWriter(std::string_view archive_name);
    ~ArchiveWriter();
    void WriteBit(bool bit);
    void Write9Bits(uint16_t bits);
};
