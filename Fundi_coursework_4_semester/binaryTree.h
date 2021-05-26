//
// Created by ayttekao on 4/9/21.
//

#ifndef FUNDI_7_BINARYTREE_H
#define FUNDI_7_BINARYTREE_H

#include "strategy.h"

template <typename T>
class TreeNode
{
public:
    T value;
    TreeNode() : TreeNode(T())
    {

    }
    explicit TreeNode(T inputValue)
    {
        value = inputValue;
    }
    ~TreeNode() = default;
};

template <class T>
class BinaryTree {
protected:
    TreeNode<T> *root = nullptr;
    Strategy<T> *strategy_;
    explicit BinaryTree(Strategy<T> *strategy = nullptr) : strategy_(strategy) {}
public:
    virtual void addNode(const T& data) = 0;
    virtual void deleteNode(const T& data) = 0;
    virtual TreeNode<T>* searchByValue(const T& data) = 0;
    virtual ~BinaryTree() = default;
};


#endif //FUNDI_7_BINARYTREE_H
