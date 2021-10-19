#include "Heap.h"

size_t Heap::GetRight(size_t node) {
    return node * 2 + 2;
}

size_t Heap::GetLeft(size_t node) {
    return node * 2 + 1;
}

size_t Heap::GetAncestor(size_t node) {
    return (node - 1) / 2;
}

void Heap::Push(const std::shared_ptr<Trie::TrieNode>& el) {
    data_.push_back(el);
    size_t pos = data_.size() - 1;
    while (pos > 0 && data_[pos]->GetCount() < data_[GetAncestor(pos)]->GetCount()) {
        std::swap(data_[pos], data_[GetAncestor(pos)]);
        pos = GetAncestor(pos);
    }
}


std::shared_ptr<Trie::TrieNode> Heap::Top() {
    return data_[0];
}

void Heap::Pop() {
    std::swap(data_.front(), data_.back());
    data_.pop_back();
    size_t pos = 0;
    while (GetLeft(pos) < data_.size()) {
        size_t left = GetLeft(pos);
        size_t right = GetRight(pos);
        if (right >= data_.size() || data_[left]->GetCount() < data_[right]->GetCount()) {
            if (data_[left]->GetCount() < data_[pos]->GetCount()) {
                std::swap(data_[left], data_[pos]);
                pos = left;
            } else {
                break;
            }
        } else if (data_[right]->GetCount() < data_[pos]->GetCount()) {
            std::swap(data_[right], data_[pos]);
            pos = right;
        } else {
            break;
        }
    }
}


size_t Heap::Size() {
    return data_.size();
}
