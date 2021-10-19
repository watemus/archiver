#include <iostream>
#include <string_view>
#include <vector>
#include <fstream>

#include "ArchiveWriter.h"
#include "ArchiveReader.h"
#include "Common.h"
#include "Compressor.h"
#include "Decompressor.h"

static void PrintIncorrectUsage() {
    std::cout << "This is not a right command. See 'archiver -h' for help." << std::endl;
}

int main(int argc, char** argv) {
    std::vector<std::string_view> args;
    for (size_t i = 0; i < argc; i++) {
        args.push_back(argv[i]);
    }
    if (args.size() < 2) {
        PrintIncorrectUsage();
        return 0;
    } else if (args[1] == "-h") {
        if (args.size() > 2) {
            PrintIncorrectUsage();
            return 0;
        } else {
            std::cout << "Usage: \n"
                         "'archiver -с archive_name file_1 [file_2, ... file_n]' - compress files to archive_name.\n"
                         "'archiver -d archive_name' - decompress archive.\n"
                         "'archiver -h' - show usage." << std::endl;
        }
    } else if (args[1] == "-c") {
        if (args.size() < 4) {
            PrintIncorrectUsage();
            return 0;
        }
        std::string_view archive_name(args[2]);
        std::vector<std::string_view> files {args.begin() + 3, args.end()};
        Compress(archive_name, files);
    } else if (args[1] == "-d") {
        if (args.size() > 3) {
            PrintIncorrectUsage();
            return 0;
        }
        std::string_view archive_name(args[2]);
        Decompress(archive_name);
    } else {
        PrintIncorrectUsage();
        return 0;
    }
    return 0;
}
