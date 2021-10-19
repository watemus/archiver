#pragma once

#include <tuple>
#include <queue>

#include "Trie.h"

class Heap {
private:
    std::vector<std::shared_ptr<Trie::TrieNode>> data_;
    size_t GetAncestor(size_t node);
    size_t GetLeft(size_t node);
    size_t GetRight(size_t node);
public:
    void Push(const std::shared_ptr<Trie::TrieNode>& el);
    std::shared_ptr<Trie::TrieNode> Top();
    void Pop();
    size_t Size();
};

