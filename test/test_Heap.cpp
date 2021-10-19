#include <catch.hpp>

#include "Heap.h"

TEST_CASE("Heap1") {
    Heap hs;
    hs.Push(std::make_shared<Trie::TrieNode>(2, 10));
    REQUIRE(hs.Top()->GetData() == 2);
}

TEST_CASE("Heap2") {
    Heap hs;
    hs.Push(std::make_shared<Trie::TrieNode>(2, 10));
    hs.Push(std::make_shared<Trie::TrieNode>(3, 11));
    hs.Push(std::make_shared<Trie::TrieNode>(5, 6));
    hs.Push(std::make_shared<Trie::TrieNode>(4, 15));
    REQUIRE(hs.Top()->GetData() == 5);
}

TEST_CASE("Heap3") {
    Heap hs;
    hs.Push(std::make_shared<Trie::TrieNode>(2, 10));
    hs.Push(std::make_shared<Trie::TrieNode>(3, 11));
    hs.Push(std::make_shared<Trie::TrieNode>(5, 6));
    hs.Push(std::make_shared<Trie::TrieNode>(4, 15));
    hs.Pop();
    REQUIRE(hs.Top()->GetData() == 2);
}
