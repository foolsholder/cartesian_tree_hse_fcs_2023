#include <utility>


struct TreapNode {
    int x;
    int y;
    int size;

    TreapNode* left;
    TreapNode* right;
};

int Size(TreapNode* v) {
    if (!v) {
        return 0;
    }
    return v->size;
}


std::pair<TreapNode*, TreapNode*> Split(TreapNode* root, int key) {
    if (!root) {
        return {nullptr, nullptr};
    }
    if (Size(root->left) < key) {
        auto pair = Split(root->right, key - 1 - Size(root->left));

        auto left = pair.first;
        auto right = pair.second;

        root->right = left;
        root->size = key;
        return {root, right};
    } else {
        auto [left, right] = Split(root->left, key);
        root->left = right;
        root->size = 1 + Size(root->left) + Size(root->right);
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
        A->size = 1 + Size(A->left) + Size(A->right);
        return A;
    } else {
        B->left = Merge(A, B->left);
        B->size = 1 + Size(B->left) + Size(B->right);
        return B;
    }
}

TreapNode* Insert(TreapNode* root, TreapNode* new_vertex, int pos) {
    auto [left, right] = Split(root, pos);
    return Merge(left, Merge(new_vertex, right));
}

