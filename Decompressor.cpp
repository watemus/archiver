#include "Decompressor.h"

#include <string_view>
#include <string>
#include <vector>
#include <tuple>
#include <cstdint>
#include <map>

#include "ArchiveReader.h"
#include "Common.h"
#include "Trie.h"

void Decompress(std::string_view archive_name) {
    ArchiveReader reader(archive_name);
    while (true) {
        uint16_t count = reader.Read9Bits();
        std::vector<std::pair<std::string, uint16_t>> table(count);
        for (size_t i = 0; i < count; ++i) {
            table[i].second = reader.Read9Bits();
        }
        size_t have = 0;
        std::string cur;
        for (size_t i = 0; i < count; ++i) {
            while (have == 0) {
                have = reader.Read9Bits();
                cur.push_back('0');
            }
            table[i].first = cur;
            GetNextCode(cur);
            --have;
        }
        std::map<std::string, uint16_t> code2val;
        std::map<uint16_t, std::string> val2code;
        for (const auto& [code, val] : table) {
            code2val[code] = val;
            val2code[val] = code;
        }
        auto read_val = [&code2val, &reader]() {
          std::string cur_code;
          while (!code2val.count(cur_code)) {
              cur_code.push_back(reader.ReadBit() + '0');
          }
          return code2val[cur_code];
        };
        std::string file_name;
        uint16_t ch;
        for (ch = read_val(); ch != FILENAME_END; ch = read_val()) {
            file_name.push_back(static_cast<char>(ch));
        }
        std::ofstream output(file_name, std::ios::binary | std::ios::out);
        for (ch = read_val(); ch != ONE_MORE_FILE && ch != ARCHIVE_END; ch = read_val()) {
            output.write(reinterpret_cast<const char*>(&ch), 1);
        }
        if (ch == ARCHIVE_END) {
            break;
        }
    }
}
