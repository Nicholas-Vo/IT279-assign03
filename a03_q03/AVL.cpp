#include "AVL.h"
#include <algorithm>
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
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

template<typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x) {
    insert(x, root);
}

template<typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x, AvlNode *&t) {
    if (t == nullptr) {
        t = new AvlNode(x, nullptr, nullptr, 0);
        cout << "Created new AvlNode with a value of " << x << endl;
    } else if (x < t->element) {
        insert(x, t->left);
        cout << "Inserted " << x << " to the left..." << endl;
    } else if (x > t->element) {
        insert(x, t->right);
        cout << "Inserted " << x << " to the right..." << endl;
    } else;

    balance(t);
}

template<typename Comparable>
void AvlTree<Comparable>::balance(AvlTree::AvlNode *&t) {
    if (t == nullptr) {
        return;
    }

    if (height(t->left) - height(t->right) == 2) {
        if (t->element < t->left->element) {
            rightRotate(t);
        } else {
            rightRotate(t->left);
            leftRotate(t);
        }
    } else if (height(t->right) - height(t->left) == 2) {
        if (t->element > t->right->element) {
            leftRotate(t);
        } else {
            leftRotate(t->right);
            rightRotate(t);
        }
    }

    t->height = max(height(t->left), height(t->right) + 1);
}

template<typename Comparable>
void AvlTree<Comparable>::leftRotate(AvlTree::AvlNode *&k2) {
    AvlNode *k1 = k2->left;

    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right) + 1);
    k1->height = max(height(k1->left), k2->height) + 1;

    k2 = k1;
}

template<typename Comparable>
void AvlTree<Comparable>::rightRotate(AvlTree::AvlNode *&t) {
    AvlNode *k1 = t->right;

    t->right = k1->left;
    k1->left = t;
    t->height = max(height(t->right), height(t->left) + 1);
    t->height = max(height(k1->right), t->height) + 1;

    t = k1;
}


// a)	(10 pts) Complete findMax and findMin methods (both public and private). 
// b)	(15 pts) Complete rightRotate method
// c)	(15 pts) Complete leftRotate method
// d)	(40 pts) Complete balance method, must have the function of outputting each of the four cases to handle unbalance and the node that is used as root to rotate. For example:

// left left case: rightRotate (50)
// left left case: rightRotate (20)
// left right case: leftRotate (40), rightRotate(50)

// right left case: rightRotate (50), leftRotate(45)

// f)	(10 pts) Complete remove method











