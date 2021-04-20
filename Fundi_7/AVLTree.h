//
// Created by ayttekao on 4/9/21.
//

#ifndef FUNDI_7_AVLTREE_H
#define FUNDI_7_AVLTREE_H

#include <vector>

template <typename T>
class AVLTreeNode : public TreeNode<T>
{
public:
    uint8_t height;
    AVLTreeNode *left, *right;
    AVLTreeNode()
    {
        this->value = 0;
        left = right = nullptr;
        height = 0;
    }
    explicit AVLTreeNode(T inputValue)
    {
        this->value = inputValue;
        left = right = nullptr;
        height = 1;
    }
    ~AVLTreeNode() = default;
};

template <class T>
class AVLTree : public BinaryTree<T> {
private:
    void freeMem(AVLTreeNode<T>* pTreeNode)
    {
        if (pTreeNode != nullptr)
        {
            freeMem(reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->left));
            freeMem(reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->right));
            delete pTreeNode;
        }
        this->root = nullptr;
    }
    void innerPrintBT(const std::string& prefix, const AVLTreeNode<T>* pTreeNode, bool isLeft)
    {
        if(pTreeNode != nullptr )
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the pTreeNode
            std::cout << pTreeNode->value << std::endl;

            // enter the next tree level - left and right branch
            innerPrintBT(prefix + (isLeft ? "│   " : "    "), reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->left),
                         true);
            innerPrintBT(prefix + (isLeft ? "│   " : "    "), reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->right),
                         false);
        }
    }
    uint8_t height(AVLTreeNode<T>* pTreeNode)
    {
        return pTreeNode ? pTreeNode->height : 0;
    }
    // Get Balance factor of node pTreeNode
    int getBalance(AVLTreeNode<T>* pTreeNode)
    {
        if (pTreeNode == nullptr)
            return 0;
        return height(reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->right)) -
               height(reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->left));
    }
    void updateBalanceFactor(AVLTreeNode<T>* pTreeNode) // update balance factor for current node
    {
        int heightLeft = height(reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->left));
        int heightRight = height(reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->right));
        pTreeNode->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
    }
    // A utility function to right
    // rotate subtree rooted with y
    void rightRotate(AVLTreeNode<T>** pTreeNode)
    {
        AVLTreeNode<T>* subtree = (*pTreeNode)->left;
        (*pTreeNode)->left = subtree->right;
        subtree->right = *pTreeNode;
        updateBalanceFactor(*pTreeNode);
        updateBalanceFactor(reinterpret_cast<AVLTreeNode<T>*>(subtree));
        *pTreeNode = reinterpret_cast<AVLTreeNode<T>*>(subtree);
    }
    // A utility function to left
    // rotate subtree rooted with x
    void leftRotate(AVLTreeNode<T>** pTreeNode)
    {
        AVLTreeNode<T>* subtree = (*pTreeNode)->right;
        (*pTreeNode)->right = subtree->left;
        subtree->left = *pTreeNode;
        updateBalanceFactor(*pTreeNode);
        updateBalanceFactor(reinterpret_cast<AVLTreeNode<T>*>(subtree));
        *pTreeNode = reinterpret_cast<AVLTreeNode<T>*>(subtree);
    }
    void rebalance(AVLTreeNode<T>** pTreeNode) // balance node root
    {
        updateBalanceFactor(*pTreeNode);
        if (getBalance(*pTreeNode) == 2)
        {
            if (getBalance(reinterpret_cast<AVLTreeNode<T>*>((*pTreeNode)->right)) < 0)
                rightRotate(reinterpret_cast<AVLTreeNode<T>**>(&((*pTreeNode)->right)));
            leftRotate(pTreeNode);
        }
        else if (getBalance(*pTreeNode) == -2)
        {
            if (getBalance(reinterpret_cast<AVLTreeNode<T>*>((*pTreeNode)->left)) > 0)
                leftRotate(reinterpret_cast<AVLTreeNode<T>**>(&((*pTreeNode)->left)));
            rightRotate(pTreeNode);
        }
    }
    void innerInsert(AVLTreeNode<T>** pTreeNode, T&& inputValue)// вставка ключа inputValue в дерево с корнем root
    {
        if (*pTreeNode == nullptr) /* Perform the normal BST insertion */
        {
            *pTreeNode = new AVLTreeNode<T>(inputValue);
            return;
        }
        int comparisonResult = this->strategy_->compare(inputValue, (*pTreeNode)->value);
        switch (comparisonResult)
        {
            case -1:
                if ((*pTreeNode)->left == nullptr)
                    (*pTreeNode)->left = new AVLTreeNode<T>(inputValue);
                else
                    innerInsert(reinterpret_cast<AVLTreeNode<T>**>(&((*pTreeNode)->left)), static_cast<T &&>(inputValue));
                break;
            case 1:
                if ((*pTreeNode)->right == nullptr)
                    (*pTreeNode)->right = new AVLTreeNode<T>(inputValue);
                else
                    innerInsert(reinterpret_cast<AVLTreeNode<T>**>(&((*pTreeNode)->right)), static_cast<T &&>(inputValue));
                break;
            case 0:
                throw std::invalid_argument("The value is already in the tree!");
            default:
                break;
        }
        rebalance(pTreeNode);
    }
    AVLTreeNode<T>* successor(AVLTreeNode<T>** pTreeNode)
    {
        AVLTreeNode<T>* current = *pTreeNode;
        while (current->left != nullptr)
            current = reinterpret_cast<AVLTreeNode<T>*>(current->left);
        return current;
    }
    void innerDelete(AVLTreeNode<T>** pTreeNode, T&& inputValue)
    {
        AVLTreeNode<T>* tmp;
        if (*pTreeNode == nullptr)
            throw std::exception();
        int comparisonResult = this->strategy_->compare(inputValue, (*pTreeNode)->value);
        switch (comparisonResult)
        {
            case -1:
                innerDelete(reinterpret_cast<AVLTreeNode<T>**>(&((*pTreeNode)->left)), static_cast<T &&>(inputValue));
                break;
            case 1:
                innerDelete(reinterpret_cast<AVLTreeNode<T>**>(&((*pTreeNode)->right)), static_cast<T &&>(inputValue));
                break;
            case 0:
                if ((*pTreeNode)->left == nullptr or (*pTreeNode)->right == nullptr)
                {
                    if (reinterpret_cast<AVLTreeNode<T> *>((*pTreeNode)->left))
                        tmp = reinterpret_cast<AVLTreeNode<T> *>((*pTreeNode)->left);
                    else
                        tmp = reinterpret_cast<AVLTreeNode<T> *>((*pTreeNode)->right);

                    if (tmp == nullptr) // no child case
                    {
                        tmp = *pTreeNode;
                        *pTreeNode = nullptr;
                    }
                    else // one child case
                        (*pTreeNode) = tmp; /* Copy contents of non-empty child */
                    delete tmp;
                }
                else
                {
                    // node with two children: Get the inorder
                    // successor (smallest in the right subtree)
                    tmp = successor(reinterpret_cast<AVLTreeNode<T> **>(&((*pTreeNode)->right)));
                    // Copy the inorder successor's
                    // data to this node
                    (*pTreeNode)->value = tmp->value;
                    // Delete the inorder successor
                    innerDelete(reinterpret_cast<AVLTreeNode<T>**>(&((*pTreeNode)->right)), static_cast<T &&>(tmp->value));
                }
                break;
            default:
                break;
        }
        if (*pTreeNode == nullptr)
            return;

        rebalance(pTreeNode);
    }
    AVLTreeNode<T>* getNodeByValue(AVLTreeNode<T>* pTreeNode, T&& inputValue)
    {
        int comparisonResult;

        while (pTreeNode != nullptr)
        {
            comparisonResult = this->strategy_->compare(inputValue, pTreeNode->value);
            if (comparisonResult == -1) /* left case */
                pTreeNode = reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->left);
            else if (comparisonResult == 1) /* right case */
                pTreeNode = reinterpret_cast<AVLTreeNode<T>*>(pTreeNode->right);
            else
                return pTreeNode;
        }
        return nullptr;
    }
public:
    AVLTree(std::vector<T> values, Strategy<T>* strategy) : AVLTree(strategy)
    {
        vectorToTree(values);
    }
    explicit AVLTree(Strategy<T>* strategy) : BinaryTree<T>(strategy) {}
    ~AVLTree() override
    {
        freeMem(reinterpret_cast<AVLTreeNode<T>*>(this->root));
    }
    void vectorToTree(std::vector<T> values)
    {
        for (auto& item : values)
            addNode(static_cast<T &&>(item));
    }
    void addNode(T&& data) override
    {
        innerInsert(reinterpret_cast<AVLTreeNode<T>**>(&this->root), static_cast<T &&>(data));
    }
    TreeNode<T>* searchByValue(T&& data) override
    {
        return getNodeByValue(reinterpret_cast<AVLTreeNode<T>*>(this->root), static_cast<T &&>(data));
    }
    void printTree()
    {
        innerPrintBT("", reinterpret_cast<AVLTreeNode<T>*>(this->root), false);
    }
    void deleteNode(T&& data) override
    {
        innerDelete(reinterpret_cast<AVLTreeNode<T>**>(&this->root), static_cast<T&&>(data));
    }
    bool empty()
    {
        return (this->root) ? 0 : 1;
    }
};

#endif //FUNDI_7_AVLTREE_H
