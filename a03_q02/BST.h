#ifndef _BST_H_
#define _BST_H_

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>

using namespace std;

template<typename Comparable>
class BinarySearchTree {
private:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
                : element{theElement}, left{lt}, right{rt} {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
                : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

public:
    BinarySearchTree();

    BinarySearchTree(const BinarySearchTree &rhs);

    BinarySearchTree(BinarySearchTree &&rhs) noexcept;

    ~BinarySearchTree();

    void insert(const Comparable &x);

    void printTree() const;

    void makeEmpty();

    bool isEmpty() const;

    BinaryNode *findMin() const;

    // Copy assignment
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // Move assignment
    BinarySearchTree &operator=(BinarySearchTree &&rhs) {
        std::swap(root, rhs.root);
        return *this;
    }

    void remove(const Comparable &x);

    BinaryNode *findMax() const;

private:
    BinaryNode *root;

    void insert(const Comparable &x, BinaryNode *&t);

    void makeEmpty(BinaryNode *&t);

    void printTree(BinaryNode *t, ostream &out) const;

    BinaryNode *findMin(BinaryNode *t) const;

    BinaryNode *clone(BinaryNode *t) const;

    void remove(const Comparable &x, BinaryNode *&t) const;

    BinaryNode *findMax(BinaryNode *t) const;

public:
    BinaryNode *find(const Comparable &x) const;

    BinaryNode *findParent(const Comparable &x) const;

    BinaryNode *findSuccessor(const Comparable &x) const;

    BinaryNode *findPredecessor(const Comparable &x) const;

private:
    BinaryNode *find(const Comparable &x, BinaryNode *t) const;

    BinaryNode *findParent(const Comparable &x, BinaryNode *t) const;

};

#endif