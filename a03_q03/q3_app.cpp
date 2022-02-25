#include <iostream>
#include "AVL.h"
#include "AVL.cpp"
#include "flags.h"

using namespace std;

// Testing program
int main() {
    cout << "Question 03: " << endl;
    AvlTree<int> t;

    /*
     * Test 0
     */
//    cout << "Test0: " << endl;
//    t.insert(50);
//    t.insert(30);
//    t.insert(20);
//    t.insert(40);
//    t.insert(10);
//    t.insert(5);
//    t.insert(45);
//    t.insert(48);
//
//    cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
//    t.printTree();
//    cout << endl;
//
//    t.remove(40);
//    cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
//    t.printTree();
//    cout << endl;
//
//    cout << "The max value of the AVL Tree is: " << t.findMax()->element << endl;
//    cout << "The min value of the AVL Tree is: " << t.findMin()->element << endl;

    /*
     * Test 1
     */
//     cout << "Test1: " << endl;
//     t.insert(50);
//     t.insert(40);
//     t.insert(35);
//     t.insert(40);
//     t.insert(10);
//     t.insert(15);
//     t.insert(45);
//     t.insert(48);
//     t.insert(5);
//
//     cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
//     t.printTree();
//     cout << endl;
//
//     t.remove(35);
//     cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
//     t.printTree();
//     cout << endl;
//
//     cout << "The max value of the AVL Tree is: " << t.findMax()->element << endl;
//     cout << "The min value of the AVL Tree is: " << t.findMin()->element << endl;

    /*
     * Test 2
     */
//     cout << "Test2: " << endl;
//
//     for (int num : {60, 50, 55, 58, 65, 75, 80, 85, 62}) {
//         t.insert(num);
//     }
//
//     cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
//     t.printTree();
//     cout << endl;
//
//     t.remove(80);
//     t.remove(85);
//
//     cout << "The built binary search tree (BST) is (preorder traversal):" << endl;
//     t.printTree();
//     cout << endl;
//
//     cout << "The max value of the AVL Tree is: " << t.findMax()->element << endl;
//     cout << "The min value of the AVL Tree is: " << t.findMin()->element << endl;
    return 0;
}
