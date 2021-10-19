#pragma once

#include "Trie.h"

#include <vector>
#include <cctype>
#include <map>
#include <string>

class Compressor {
private:
    std::map<uint16_t, size_t> counter_;
    Trie trie_;
    std::vector<std::pair<uint16_t, size_t>> lens_;

    void TrieDfs(size_t len);

public:
    Compressor();
    void AddContent(uint16_t byte);
    std::vector<std::pair<std::string, uint16_t>> Compress() ;
};

void Compress(std::string_view archive_name, const std::vector<std::string_view>& files);
