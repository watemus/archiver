#include <catch.hpp>

#include <fstream>
#include <iostream>

#include "Compressor.h"
#include "Decompressor.h"

TEST_CASE("Archiver1") {
    std::vector<std::string_view> files = {"file1.txt", "file2.txt"};
    std::vector<std::string_view> contents = {"kek", "lol"};
    std::string_view archive_name = "a.arch";
    std::ofstream fout;
    for (size_t i = 0; i < files.size(); ++i) {
        fout.open(files[i]);
        fout << contents[i];
        fout.close();
    }
    Compress(archive_name, files);
    for (size_t i = 0; i < files.size(); ++i) {
        fout.open(files[i]);
        fout << "trash";
        fout.close();
    }
    Decompress(archive_name);
    std::ifstream fin;
    for (size_t i = 0; i < files.size(); ++i) {
        fin.open(files[i]);
        std::string content;
        fin >> content;
        fin.close();
        REQUIRE(content == contents[i]);
    }
}

