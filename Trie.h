#pragma once

#include <memory>
#include <cctype>
#include <map>
#include <vector>

class Trie {
public:
    class TrieNode {
    private:
        std::shared_ptr<TrieNode> left_ = nullptr;
        std::shared_ptr<TrieNode> right_ = nullptr;
        uint16_t data_ = 0;
        size_t count_ = 0;
    public:
        TrieNode(uint16_t data, size_t count);
        TrieNode(std::shared_ptr<TrieNode> left, std::shared_ptr<TrieNode> right);
        bool IsLeaf() const;
        uint16_t GetData() const;
        size_t GetCount() const;
        std::shared_ptr<TrieNode> GetLeft() const;
        std::shared_ptr<TrieNode> GetRight() const;
    };
private:
    std::shared_ptr<TrieNode> root_;
    mutable std::shared_ptr<TrieNode> cur_;
    mutable std::vector<std::shared_ptr<TrieNode>> stack_;
public:
    Trie(const std::map<uint16_t, size_t>& counter);
    void StartTour() const;
    void GoDown(uint8_t where) const;
    void GoUp() const;
    bool IsLeaf() const;
    uint16_t GetData() const;
    size_t GetCount() const;
};

void GetNextCode(std::string& code);
