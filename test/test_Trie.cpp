#include <catch.hpp>

#include "Trie.h"

size_t dfs1(Trie& trie) {
    if (trie.IsLeaf()) {
        return trie.GetCount() == 1;
    }
    size_t res = 0;
    for (size_t u : {0, 1}) {
        trie.GoDown(u);
        res += dfs1(trie);
        trie.GoUp();
    }
    return res;
}

TEST_CASE("Trie1") {
    std::map<uint16_t, size_t> counter = {
        {1, 1},
        {2, 1},
        {3, 1},
        {4, 1}
    };
    Trie trie(counter);
    trie.StartTour();
    REQUIRE(dfs1(trie) == 4);
}