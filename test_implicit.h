#ifndef CODEFORCES_TEST_SORTED_H
#define CODEFORCES_TEST_SORTED_H

#endif //CODEFORCES_TEST_SORTED_H

#include <iostream>
#include "implicit_key.h"
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>


void dfs(TreapNode* root, std::vector<int>& values) {
    if (!root) {
        return;
    }
    dfs(root->left, values);
    values.push_back(root->x);
    dfs(root->right, values);
}


void test_implicit() {
    constexpr int SIZE = 5'000;
    std::vector<int> arr(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    for (int iter = 0; iter < 500; ++iter) {
        std::shuffle(arr.begin(), arr.end(), g);
        TreapNode* root = nullptr;
        std::vector<TreapNode> nodes(SIZE);


        std::vector<int> ref;
        ref.reserve(SIZE);


        for (int idx = 0; idx < SIZE; ++idx) {
            nodes[idx].x = arr[idx];
            nodes[idx].y = g();
            nodes[idx].size = 1;

            int rnd_num = g();
            if (rnd_num < 0) {
                rnd_num = -rnd_num;
            }
            int pos = rnd_num % (idx + 1);
            ref.insert(pos + ref.begin(), arr[idx]);

            root = Insert(root, &nodes[idx], pos);
        }
        std::vector<int> temp;
        temp.reserve(SIZE);
        dfs(root, temp);
        assert(temp.size() == (size_t)SIZE);
        for (int idx = 0; idx < SIZE; ++idx) {
            //std::cerr << temp[idx] << ' ';
            assert(temp[idx] == ref[idx]);
        }
    }
    std::cout << "IMPLICIT_TEST: SUCCESS" << std::endl;

}