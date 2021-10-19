#pragma once

#include <cstdint>
#include <fstream>

class ArchiveReader {
private:
    uint8_t buffer_ = 0;
    size_t buffer_ptr_ = 0;
    std::ifstream input_;
public:
    ArchiveReader(std::string_view archive_name);
    bool ReadBit();
    uint16_t Read9Bits();
};
