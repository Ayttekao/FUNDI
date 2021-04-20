//
// Created by ayttekao on 4/18/21.
//

#ifndef FUNDI_7_RELATION_H
#define FUNDI_7_RELATION_H

#include <forward_list>
#include <list>
#include <iostream>
#include <map>
#include "binaryTree.h"
#include "AVLTree.h"
#include "RBTree.h"

#define AVL 0
#define RB 1

template <typename T>
class Relation
{
private:
    std::forward_list<T> dataList;
    std::map<int, BinaryTree<T>*> indexMap;
public:
    Relation(const std::forward_list<T>& _dataList)
    {
        dataList = _dataList;
    }

    void addData(T&& data)
    {
        dataList.push_front(data);
        for (std::pair<int, BinaryTree<T>*> it : indexMap)
            it.second->addNode(static_cast<T&&>(data));
    }

    void deleteData(T&& data)
    {
        dataList.remove(data);
        for (std::pair<int, BinaryTree<T>*> it : indexMap)
            it.second->deleteNode(static_cast<T&&>(data));
    }

//    int addIndex(BinaryTree<T>* tree)
//    {
//        int indexGuid = (int)random();
//        indexMap.insert(std::pair<int, BinaryTree<T>*>(indexGuid, tree));
//        return indexGuid;
//
//    }

    void addTreeToMap(int indexGuid, BinaryTree<T>* tree)
    {
        indexMap.insert(std::pair<int, BinaryTree<T>*>(indexGuid, tree));
        for (auto iter : dataList)
            (*tree).addNode(static_cast<T&&>(iter));
    }

    int addIndex(bool typeTree, Strategy<T> *strategy)
    {
        BinaryTree<T>* tree;
        int indexGuid = (int)random();
        if (typeTree) // RB
            tree = new RBTree<T>(strategy);
        else // AVL
            tree = new AVLTree<T>(strategy);

        if (tree != nullptr)
            addTreeToMap(indexGuid, tree);
        else
            throw std::bad_alloc();

        return indexGuid;
    }

    void deleteIndex(int indexGuid)
    {
        delete indexMap[indexGuid];
        indexMap.erase(indexGuid);
    }

    bool findDataByValue(int indexGuid, T&& data)
    {
        return indexMap[indexGuid]->searchByValue(static_cast<T&&>(data)) != nullptr;
    }

    ~Relation()
    {
        for (std::pair<int, BinaryTree<T>*> it : indexMap)
            delete it.second;
    };
};

int main()
{
    Strategy<int> *testStrategy = new StrategyInt();

    std::forward_list<int> forwardList = { 18, 2, 4, 5, 6, 7 };
    Relation<int> relation(forwardList);

    int firstGuid = relation.addIndex(AVL, testStrategy);
    int secondGuid = relation.addIndex(RB, testStrategy);

    relation.deleteData(2);
    relation.deleteIndex(firstGuid);

    return 0;
}

#endif //FUNDI_7_RELATION_H
