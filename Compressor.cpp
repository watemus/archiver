#include "Compressor.h"

#include <map>

#include "Trie.h"
#include "Common.h"
#include "ArchiveWriter.h"

Compressor::Compressor() : trie_({}) {
}

void Compressor::AddContent(uint16_t byte) {
    ++counter_[byte];
}

void Compressor::TrieDfs(size_t len) {
    if (trie_.IsLeaf()) {
        lens_.emplace_back(len, trie_.GetData());
    } else {
        for (size_t child : {0, 1}) {
            ++len;
            trie_.GoDown(child);
            TrieDfs(len);
            --len;
            trie_.GoUp();
        }
    }
}

std::vector<std::pair<std::string, uint16_t>> Compressor::Compress() {
    trie_ = Trie(counter_);
    trie_.StartTour();
    TrieDfs(0);
    std::sort(lens_.begin(), lens_.end());
    std::string cur;
    std::vector<std::pair<std::string, uint16_t>> res;
    for (const auto& [len, value] : lens_) {
        while (cur.size() < len) {
            cur.push_back('0');
        }
        res.emplace_back(cur, value);
        GetNextCode(cur);
    }
    return res;
}

void Compress(std::string_view archive_name, const std::vector<std::string_view>& files) {
    size_t count = 0;
    ArchiveWriter writer(archive_name);
    for (const auto& file : files) {
        Compressor compressor;
        std::vector<uint16_t> filename {file.begin(), file.end()};
        for (auto ch : filename) {
            compressor.AddContent(ch);
        }
        std::ifstream input(file, std::ios::binary | std::ios::in);
        uint8_t byte;
        while (input.read(reinterpret_cast<char*>(&byte), sizeof byte)) {
            compressor.AddContent(byte);
        }
        compressor.AddContent(FILENAME_END);
        compressor.AddContent(ONE_MORE_FILE);
        compressor.AddContent(ARCHIVE_END);

        const auto& table = compressor.Compress();
        writer.Write9Bits(table.size());
        std::map<std::string, uint16_t> code2val;
        std::map<uint16_t, std::string> val2code;
        size_t max_len = 0;
        std::map<size_t, size_t> counter_lens;
        for (const auto& [code, val] : table) {
            code2val[code] = val;
            val2code[val] = code;
            writer.Write9Bits(val);
            ++counter_lens[code.size()];
            max_len = std::max(max_len, code.size());
        }
        for (size_t len = 1; len <= max_len; ++len) {
            writer.Write9Bits(counter_lens[len]);
        }

        input.close();
        input.open(file, std::ios::binary | std::ios::in);

        auto write_val = [&writer, &val2code](uint16_t val) {
          const auto& code = val2code[val];
          for (auto bit : code) {
              writer.WriteBit(bit - '0');
          }
        };

        for (auto ch : filename) {
            write_val(ch);
        }
        write_val(FILENAME_END);
        while (input.read(reinterpret_cast<char*>(&byte), sizeof byte)) {
            write_val(byte);
        }

        ++count;
        if (count < files.size()) {
            write_val(ONE_MORE_FILE);
        } else {
            write_val(ARCHIVE_END);
        }
    }
}
