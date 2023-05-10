#ifndef CODEFORCES_TEST_SORTED_H
#define CODEFORCES_TEST_SORTED_H

#endif //CODEFORCES_TEST_SORTED_H

#include "treap.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>


void dfs(TreapNode* root, std::vector<int>& values) {
    if (!root) {
        return;
    }
    dfs(root->left, values);
    values.push_back(root->x);
    dfs(root->right, values);
}


void test_sorted() {
    constexpr int SIZE = 100'000;
    std::vector<int> arr(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    for (int iter = 0; iter < 20; ++iter) {
        std::shuffle(arr.begin(), arr.end(), g);
        TreapNode* root = nullptr;
        std::vector<TreapNode> nodes(SIZE);
        for (int idx = 0; idx < SIZE; ++idx) {
            nodes[idx].x = arr[idx];
            nodes[idx].y = g();
            root = Insert(root, &nodes[idx]);
        }
        std::vector<int> temp;
        temp.reserve(SIZE);
        dfs(root, temp);
        assert(temp.size() == (size_t)SIZE);
        for (int idx = 0; idx < SIZE; ++idx) {
            //std::cerr << temp[idx] << ' ';
            assert(temp[idx] == idx);
        }
    }
    std::cout << "SORTED_TEST: SUCCESS" << std::endl;

}