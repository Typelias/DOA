#include <iostream>
#include "RedAndBlackTree.h"
int main()
{
    search::RedAndBlackTree<int> tree;

    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    auto s = tree.search(1);
    if (s == nullptr)
    {
        std::cout << "1 was not found\n";
    }
    else
    {
        std::cout << "1 was found\n";
    }

    return 0;
}