#include <iostream>
#include "../lib_queue/queue.h"
#include "../lib_list/list.h"

enum Color { Red, Black, BlackBlack };

template <typename TValue>
struct TNode {
    TValue data;
    TNode* left;
    TNode* right;
    TNode* parent;
    Color color;

    TNode(TValue data, TNode* left = nullptr, TNode* right = nullptr, TNode* parent = nullptr, Color color = Red)
        : data(data), left(left), right(right), parent(parent), color(color) {}
};

template <typename TValue>
class RBTree {
    TNode<TValue>* root;

public:
    RBTree() : root(nullptr) {}
    RBTree(TValue* data, size_t size);

    bool empty() const { return root == nullptr; }

    TNode<TValue>* find(TValue value);
    void insert(TValue value);
    void remove(TValue value);

private:
    TNode<TValue>* BST_insert(TNode<TValue>* node);
    TNode<TValue>* BST_remove(TNode<TValue>* node);

    void right_rotate(TNode<TValue>* X);
    void left_rotate(TNode<TValue>* X);

    void swap_colors(TNode<TValue>* X1, TNode<TValue>* X2);

    void LL(TNode<TValue>* X);
    void RR(TNode<TValue>* X);
    void RL(TNode<TValue>* X);
    void LR(TNode<TValue>* X);

    void insert_fixup(TNode<TValue>* node);
};

template <typename TValue>
TNode<TValue>* RBTree<TValue>::BST_insert(TNode<TValue>* node) {
    if (root == nullptr) {
        root = node;
        return root;
    }

    TNode<TValue>* current = root;
    TNode<TValue>* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (node->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    node->parent = parent;
    if (node->data < parent->data)
        parent->left = node;
    else
        parent->right = node;

    return node;
}

template <typename TValue>
void RBTree<TValue>::right_rotate(TNode<TValue>* X) {
    /*
       Right Rotate
       Before:
           G
          / \
         X   U
        / \
       C   T5
      / \
     T3  T4

       After:
           G
          / \
         C   U
        / \
       T3  X
          / \
         T4  T5
    */
    TNode<TValue>* G = X->parent;
    TNode<TValue>* C = X->left;
    TNode<TValue>* T4 = C->right;

    if (G != nullptr) {
        if (G->right == X)
            G->right = C;
        else
            G->left = C;
    }
    else {
        root = C;
    }
    C->parent = G;

    C->right = X;
    X->parent = C;

    X->left = T4;
    if (T4 != nullptr)
        T4->parent = X;
}

template <typename TValue>
void RBTree<TValue>::left_rotate(TNode<TValue>* X) {
    /*
       Left Rotate
       Before:
           G
          / \
         X   U
        / \
       T1  C
          / \
         T3  T4

       After:
           G
          / \
         C   U
        / \
       X   T4
      / \
     T1  T3
    */
    TNode<TValue>* G = X->parent;
    TNode<TValue>* C = X->right;
    TNode<TValue>* T3 = C->left;

    if (G != nullptr) {
        if (G->left == X)
            G->left = C;
        else
            G->right = C;
    }
    else {
        root = C;
    }
    C->parent = G;

    C->left = X;
    X->parent = C;

    X->right = T3;
    if (T3 != nullptr)
        T3->parent = X;
}

template <typename TValue>
void RBTree<TValue>::swap_colors(TNode<TValue>* X1, TNode<TValue>* X2) {
    Color tmp = X1->color;
    X1->color = X2->color;
    X2->color = tmp;
}

template <typename TValue>
void RBTree<TValue>::LL(TNode<TValue>* X) {
    /*
       Left-Left Case (LL)
       Before:
           G
          / \
         P   U
        / \
       X   T3
      / \
     T1  T2

       After:
           P
          / \
         X   G
        / \   \
       T1  T2  U
              / \
             T3  T4
    */
    right_rotate(X->parent->parent);
}

template <typename TValue>
void RBTree<TValue>::RR(TNode<TValue>* X) {
    /*
       Right-Right Case (RR)
       Before:
           G
          / \
         U   P
            / \
           T3  X
              / \
             T4  T5

       After:
           P
          / \
         G   X
        / \   \
       U  T3  T5
          / \
         T1  T2
    */
    left_rotate(X->parent->parent);
}

template <typename TValue>
void RBTree<TValue>::LR(TNode<TValue>* X) {
    /*
       Left-Right Case (LR)
       Before:
           G
          / \
         P   U
        / \
       T1  X
          / \
         T2  T3

       After:
           X
          / \
         P   G
        / \ / \
       T1 T2 T3 U
    */
    left_rotate(X->parent);
    right_rotate(X->parent);
}

template <typename TValue>
void RBTree<TValue>::RL(TNode<TValue>* X) {
    /*
       Right-Left Case (RL)
       Before:
           G
          / \
         U   P
            / \
           X  T5
          / \
         T3  T4

       After:
           X
          / \
         G   P
        / \ / \
       U  T3 T4 T5
    */
    right_rotate(X->parent);
    left_rotate(X->parent);
}

template <typename TValue>
void RBTree<TValue>::insert(TValue value) {
    TNode<TValue>* node = new TNode<TValue>(value, nullptr, nullptr, nullptr, Red);
    TNode<TValue>* X = BST_insert(node);

    TNode<TValue>* P = X->parent;
    TNode<TValue>* G = nullptr;
    TNode<TValue>* U = nullptr;

    // recoloring
    while (P && P->color == Red) {
        G = P->parent;
        if (G->left == P) {
            U = G->right;
            if (U && U->color == Red) {
                // Case 1: Both parent and uncle are red (recoloring)
                P->color = Black;
                U->color = Black;
                G->color = Red;
                X = G;
            }
            else {
                if (X == P->right) {
                    // Case 2: X is the right child of its parent (left rotation)
                    X = P;
                    left_rotate(X);
                }
                // Case 3: X is the left child of its parent (right rotation)
                P->color = Black;
                G->color = Red;
                right_rotate(G);
            }
        }
        else {
            U = G->left;
            if (U && U->color == Red) {
                // Case 1: Both parent and uncle are red (recoloring)
                P->color = Black;
                U->color = Black;
                G->color = Red;
                X = G;
            }
            else {
                if (X == P->left) {
                    // Case 2: X is the left child of its parent (right rotation)
                    X = P;
                    right_rotate(X);
                }
                // Case 3: X is the right child of its parent (left rotation)
                P->color = Black;
                G->color = Red;
                left_rotate(G);
            }
        }
        P = X->parent;
    }
    root->color = Black;
}