#include <lib/BinarySearchTree.h>

#include <iostream>

int main() {
    BinarySearchTree<int> bst;
    bst.insert(2);
    bst.insert(1);
    bst.insert(10);
    bst.insert(5);
    bst.insert(6);

    std::cout << bst.exists(6);
}