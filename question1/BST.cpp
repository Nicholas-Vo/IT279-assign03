#include "BST.h"
#include <algorithm>
#include <iostream>

using namespace std;

template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() : root{nullptr} {
}

/**
 * Copy constructor
 */
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs) : root{nullptr} {
    root = clone(rhs.root);
}

/**
 * Move constructor
 */
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree &&rhs) : root{rhs.root} {
    rhs.root = nullptr;
}

/**
 * Internal method to clone subtree.
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::clone(BinaryNode *t) const {
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
};

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode *&t) {
    if (t == nullptr)
        t = new BinaryNode{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else; // Duplicate; do nothing
}

/**
 * Find the smallest item in the tree.
 * Throw UnderflowException if empty.
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMin() const {
    if (isEmpty()) {
        cout << "\nCannot find the node." << endl;
        throw UnderflowException{};
    }
    return findMin(root);
}

/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMin(BinaryNode *t) const {
    if (t == nullptr) return nullptr;
    if (t->left == nullptr) return t;

    return findMin(t->left);
}

/**
 * Find the largest item in the tree.
 * Throw UnderflowException if empty.
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMax() const {
    if (isEmpty()) {
        cout << "\nCannot find the node." << endl;
        throw UnderflowException{};
    }
    return findMax(root);
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMax(BinaryNode *t) const {
    if (t == nullptr) return nullptr;
    if (t->right == nullptr) return t;

    return findMax(t->right);
}

/**
 * Insert x into the tree; duplicates are ignored.
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x) {
    insert(x, root);
}

/**
 * The find() wrapper function; Find an element within the BST.
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::find(const Comparable &x) const {
    if (isEmpty()) {
        cout << "\nCannot find the node." << endl;
        throw UnderflowException{};
    }
    if (x == root->element) {
        return root;
    }

    return find(x, root);
}

/*
 * The find() internal function
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode
*BinarySearchTree<Comparable>::find(const Comparable &x, BinarySearchTree::BinaryNode *t) const {
    if (x == t->element) return t;
    if (x < t->element) return find(x, t->left);

    return find(x, t->right);
}

/*
 * findParent function wrapper
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findParent(const Comparable &x) const {
    if (isEmpty() || x == root->element) {
        return nullptr;
    }

    return findParent(x, root);
}

/*
 * findParent internal method
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode
*BinarySearchTree<Comparable>::findParent(const Comparable &x, BinarySearchTree::BinaryNode *t) const {
    if (x == t->left->element || x == t->right->element) {
        return t;
    }

    if (x < t->element) {
        return findParent(x, t->left);
    }

    return findParent(x, t->right);
}

/**
 * remove function wrapper
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x) {
    root = remove(x, root);
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode
*BinarySearchTree<Comparable>::remove(const Comparable &x, BinarySearchTree::BinaryNode *t) const {
    if (t == nullptr) {
        return nullptr;
    }

    if (x < t->element) {
        t->left = remove(x, t->left);
        return t;
    }

    if (x > t->element) {
        t->right = remove(x, t->right);
        return t;
    }

    if (t->left == nullptr) {
        BinaryNode* temp = t->right;
        delete t;
        return temp;
    }

    if (t->right == nullptr) {
        BinaryNode* temp = t->left;
        delete t;
        return temp;
    }

    BinaryNode* tempX = findMin(t->right);
    t->right = remove(x, t->right);
    t->element = tempX->element;

    return t;
}

/**
 * Destructor for the tree
 */
template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {
    makeEmpty();
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

/**
 * Internal method to make subtree empty.
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *&t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

/**
  * Print the tree contents in sorted order.
  */
template<typename Comparable>
void BinarySearchTree<Comparable>::printTree() const {
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root, cout);
    cout << endl;
};

/**
 * Internal method to print a subtree rooted at t in sorted order.
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinarySearchTree<Comparable>::BinaryNode *t, ostream &out) const {
    if (t != nullptr) {
        cout << t->element << " ";
        printTree(t->left, out);

        printTree(t->right, out);
    }
}

/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template<typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {
    return root == nullptr;
}

//========================================================================================
//Add code to implement the functions listed in the header file
// public:
//     BinaryNode *find(const Comparable &x) const;
//     BinaryNode *findParent(const Comparable &x) const;
//     BinaryNode *findSuccessor(const Comparable &x) const;   
//     BinaryNode *findPredecessor(const Comparable &x) const;
// private:
//     BinaryNode *find(const Comparable &x, BinaryNode *t) const;
//     BinaryNode *findParent(const Comparable &x, BinaryNode *t) const;



//==========================================================================