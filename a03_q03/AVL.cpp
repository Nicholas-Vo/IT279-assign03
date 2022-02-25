#include "AVL.h"
#include <iostream>

using namespace std;

template<typename Comparable>
AvlTree<Comparable>::AvlTree() : root{nullptr} {
}

template<typename Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree &rhs) : root{nullptr} {
    root = clone(rhs.root);
}

template<typename Comparable>
AvlTree<Comparable>::AvlTree(AvlTree &&rhs) : root{rhs.root} {
    rhs.root = nullptr;
}

template<typename Comparable>
AvlTree<Comparable>::~AvlTree() {
    makeEmpty();
}

/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template<typename Comparable>
bool AvlTree<Comparable>::isEmpty() const {
    return root == nullptr;
}

/**
 * Print the tree contents in sorted order.
 */
template<typename Comparable>
void AvlTree<Comparable>::printTree() const {
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}

/**
 * Make the tree logically empty.
 */
template<typename Comparable>
void AvlTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

/**
 * Internal method to make subtree empty.
 */
template<typename Comparable>
void AvlTree<Comparable>::makeEmpty(AvlTree<Comparable>::AvlNode *&t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

/**
 * Internal method to print a subtree rooted at t in sorted order.
 */
template<typename Comparable>
void AvlTree<Comparable>::printTree(AvlNode *t) const {
    if (t != nullptr) {
        cout << t->element << "  ";
        printTree(t->left);
        printTree(t->right);
    }
}

/**
 * Internal method to clone subtree.
 */
template<typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::clone(AvlNode *t) const {
    if (t == nullptr)
        return nullptr;
    else
        return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
}
// Avl manipulations
/**
 * Return the height of node t or -1 if nullptr.
 */
template<typename Comparable>
int AvlTree<Comparable>::height(AvlNode *t) const {
    return t == nullptr ? -1 : t->height;
}

template<typename Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs) const {
    return lhs > rhs ? lhs : rhs;
}

// Get Balance factor of node N
template<typename Comparable>
int AvlTree<Comparable>::getBalance(AvlNode *N) {
    if (N == NULL) {
        return 0;
    }

    return height(N->left) - height(N->right);
}

template<typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x) {
    insert(x, root);
}

template<typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x, AvlNode *&t) {
    if (t == nullptr) {
        t = new AvlNode(x, nullptr, nullptr);
    }

    if (x < t->element)
        insert(x, t->left);
    if (t->element < x)
        insert(x, t->right);

    balance(t);
}

template<typename Comparable>
void AvlTree<Comparable>::balance(AvlTree::AvlNode *&t) {
    if (t == nullptr) {
        return;
    }

    if (getBalance(t) > ALLOWED_IMBALANCE) {
        if (height(t->left->left) >= height(t->left->right)) {
            leftRotate(t);
        } else {
            rightRotate(t->left);
            leftRotate(t);
        }
    } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
        if (height(t->right->right) >= height(t->right->left)) {
            rightRotate(t);
        } else {
            leftRotate(t->right);
            rightRotate(t);
        }
    }

    t->height = max(height(t->left), height(t->right)) + 1;
}

template<typename Comparable>
void AvlTree<Comparable>::leftRotate(AvlTree::AvlNode *&k2) {
    AvlNode *temp = k2->left;

    k2->left = temp->right;
    temp->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    temp->height = max(height(temp->left), k2->height) + 1;

    k2 = temp;
}

template<typename Comparable>
void AvlTree<Comparable>::rightRotate(AvlTree::AvlNode *&k1) {
    AvlNode *temp = k1->right;

    k1->right = temp->left;
    temp->left = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    temp->height = max(height(temp->right), k1->height) + 1;

    k1 = temp;
}

template<typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x) {
    remove(x, root);
}

template<typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x, AvlTree::AvlNode *&t) {
    if (t == nullptr) {
        return; // Didn't find item, return out
    }

    if (x < t->element) {
        remove(x, t->left);
        return;
    } else if (x > t->element) {
        remove(x, t->right);
        return;
    } else if (t->left != nullptr && t->right != nullptr) {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
        return;
    } else {
        AvlNode *temp = t;

        t = t->left == nullptr ? t->right : t->left;
        delete temp;
    }

    balance(t);
}

template<typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMin() const {
    return findMin(root);
}

template<typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMin(AvlTree::AvlNode *t) const {
    if (t == nullptr) {
        return nullptr;
    }
    if (t->left == nullptr) {
        return t;
    }
    return findMin(t->left);
}

template<typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMax() const {
    return findMax(root);
}

template<typename Comparable>
typename AvlTree<Comparable>::AvlNode *AvlTree<Comparable>::findMax(AvlTree::AvlNode *t) const {
    if (t == nullptr) {
        return nullptr;
    }

    while (t->right != nullptr) {
        t = t->right;
    }
    return t;
}











