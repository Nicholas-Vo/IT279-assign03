#include "BST.h"
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
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{rhs.root} {
    rhs.root = nullptr;
}

/**
 * Internal method to clone subtree.
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::clone(BinaryNode *t) const {
    if (t == nullptr) {
        return nullptr;
    } else {
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
}

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
        return nullptr;
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
        return nullptr;
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
        return nullptr;
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

/*
 * findSuccessor method
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode
*BinarySearchTree<Comparable>::findSuccessor(const Comparable &x) const {
    BinaryNode *theNode; // The node to find the successor of

    if (find(x) == nullptr) {
        cout << "Couldn't find value " << x << "." << endl;
        return nullptr;
    }

    theNode = find(x);

    if (theNode->right == nullptr) {
        cout << "No successor found." << endl;
        return nullptr;
    }

    return findMin(theNode->right);
}

/*
 * findPredecessor method
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode
*BinarySearchTree<Comparable>::findPredecessor(const Comparable &x) const {
    BinaryNode *theNode;

    if (find(x) == nullptr) {
        cout << "Couldn't find value " << x << "." << endl;
        return nullptr;
    }

    theNode = find(x);

    if (findMax(theNode->left) == nullptr) {
        cout << "null value" << endl;
        return nullptr;
    }

    return findMax(theNode->left);
}

/**
 * remove function wrapper
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x) {
    if (find(x) == nullptr) {
        cout << "nullptr remove" << endl;
        return;
    }

    remove(x, root); // call remove() internal function
}

/*
Update the recursive remove method in the file BST.cpp, i.e., when the node has two children, the
algorithm will use the remainder of a random number divided by 2 to determine whether to remove
the minimum node of the right subtree (remainder == 1) or the maximum node of the left subtree
(remainder == 0). For these two cases, the remove method will output “Remove the minimum node
of the right subtree” and “Remove the maximum node of the left subtree” respectively.
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinarySearchTree::BinaryNode *&t) const {
    if (t == nullptr) {
        return;
    }

    if (x < t->element) {
        remove(x, t->left);
        return;
    }

    if (x > t->element) {
        remove(x, t->right);
        return;
    }

    /*
     * Two children case
     * minimum node of the right subtree (remainder == 1)
     * maximum node of the left subtree (remainder == 0)
     */
//    if (t->left != nullptr && t->right != nullptr) {
//        int random = rand() % 2; // Random 0 or 1
//        cout << "Testy boy: " << random << endl;
//
//        BinaryNode *theNode = random ? t->right : t->left; // 40
//        cout << "theNode: " << theNode->element << endl;
//        int element = random ? findMin(theNode)->element : findMax(theNode)->element; // 35
//
//        remove(element, theNode);
//        return;
//    }

    if (t->left != nullptr && t->right != nullptr) {
        if (rand() % 2) {
            remove(findMin(t->right)->element, t->right);
            cout << "Remove the minimum node"
                    " of the right subtree" << endl;
        } else {
            remove(findMax(t->left)->element, t->left);
            cout << "Remove the maximum node "
                    " of the left subtree" << endl;
        }
        return;
    }

    BinaryNode *temp = t;

    /*
     * Ternary to determine right or left
     */
    t = t->left == nullptr ? t->right : t->left;
    delete temp;
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
    if (isEmpty()) {
        cout << "Empty tree" << endl;
    } else {
        printTree(root, cout);
    }
    cout << endl;
}

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