#include <utility>


struct TreapNode {
    int x;
    int y;

    TreapNode* left;
    TreapNode* right;
};


std::pair<TreapNode*, TreapNode*> Split(TreapNode* root, int key) {
    if (!root) {
        return {nullptr, nullptr};
    }
    if (root->x < key) {
        auto [left, right] = Split(root->right, key);
        root->right = left;
        return {root, right};
    } else {
        auto [left, right] = Split(root->left, key);
        root->left = right;
        return {left, root};
    }
}

TreapNode* Merge(TreapNode* A, TreapNode* B) {
    if (!A) {
        return B;
    }
    if (!B) {
        return A;
    }
    if (A->y > B->y) {
        A->right = Merge(A->right, B);
        return A;
    } else {
        B->left = Merge(A, B->left);
        return B;
    }
}

TreapNode* Insert(TreapNode* root, TreapNode* new_vertex) {
    auto [left, right] = Split(root, new_vertex->x);
    return Merge(left, Merge(new_vertex, right));
}

