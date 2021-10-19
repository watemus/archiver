#include "Trie.h"

#include <string>
#include <functional>

#include "Heap.h"

Trie::TrieNode::TrieNode(uint16_t data, size_t count) : data_(data), count_(count) {
}

Trie::TrieNode::TrieNode(std::shared_ptr<TrieNode> left, std::shared_ptr<TrieNode> right)
    : left_(left), right_(right), count_(left->GetCount() + right->GetCount()) {
}

uint16_t Trie::TrieNode::GetData() const {
    return data_;
}

size_t Trie::TrieNode::GetCount() const {
    return count_;
}

bool Trie::TrieNode::IsLeaf() const {
    return left_ == nullptr && right_ == nullptr;
}

std::shared_ptr<Trie::TrieNode> Trie::TrieNode::GetLeft() const {
    return left_;
}

std::shared_ptr<Trie::TrieNode> Trie::TrieNode::GetRight() const {
    return right_;
}

Trie::Trie(const std::map<uint16_t, size_t>& counter) {
    Heap heap;
    for (const auto& [value, count] : counter) {
        heap.Push(std::make_shared<TrieNode>(value, count));
    }
    if (heap.Size() > 0) {
        root_ = heap.Top();
        while (heap.Size() >= 2) {
            auto ptr1 = heap.Top();
            heap.Pop();
            auto ptr2 = heap.Top();
            heap.Pop();
            root_ = std::make_shared<TrieNode>(ptr1, ptr2);
            heap.Push(root_);
        }
        cur_ = root_;
    }
}

void Trie::StartTour() const {
    cur_ = root_;
    stack_ = {root_};
}

void Trie::GoDown(uint8_t where) const {
    if (cur_->IsLeaf()) {
        return;
    }
    if (where == 1) {
        cur_ = cur_->GetLeft();
        stack_.push_back(cur_);
    } else {
        cur_ = cur_->GetRight();
        stack_.push_back(cur_);
    }
}

void Trie::GoUp() const {
    if (stack_.size() == 1) {
        return;
    }
    stack_.pop_back();
    cur_ = stack_.back();
}

bool Trie::IsLeaf() const {
    return cur_->IsLeaf();
}

uint16_t Trie::GetData() const {
    return cur_->GetData();
}

size_t Trie::GetCount() const {
    return cur_->GetCount();
}

void GetNextCode(std::string& code) {
    size_t deleted = 0;
    while (!code.empty() && code.back() == '1') {
        code.pop_back();
        ++deleted;
    }
    if (!code.empty()) {
        code.pop_back();
    }
    code.push_back('1');
    for (size_t i = 0; i < deleted; ++i) {
        code.push_back('0');
    }
}
