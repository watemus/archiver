set(CMAKE_CXX_STANDARD 20)

add_executable(archiver
        main.cpp
        Compressor.cpp
        Trie.cpp
        ArchiveWriter.cpp
        ArchiveReader.cpp
        Heap.cpp
        Decompressor.cpp)

add_catch(test_Heap test/test_Heap.cpp Heap.cpp Trie.cpp)

add_catch(test_Archiver
        test/test_Archiver.cpp
        Compressor.cpp
        Decompressor.cpp
        Heap.cpp
        Trie.cpp
        ArchiveReader.cpp
        ArchiveWriter.cpp)

add_catch(test_Trie
        test/test_Trie.cpp
        Compressor.cpp
        Decompressor.cpp
        Heap.cpp
        Trie.cpp
        ArchiveReader.cpp
        ArchiveWriter.cpp)