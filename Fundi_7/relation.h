//
// Created by ayttekao on 4/18/21.
//

#ifndef FUNDI_7_RELATION_H
#define FUNDI_7_RELATION_H

#include "binaryTree.h"
#include "AVLTree.h"
#include "RBTree.h"
#include <map>
#include <forward_list>

#define AVL 0
#define RB 1

template <typename T>
class Relation
{
private:
    std::forward_list<T> dataList;
    std::map<int, BinaryTree<T>*> indexMap;
    void addTreeToMap(int indexGuid, BinaryTree<T>* tree)
    {
        indexMap.insert(std::pair<int, BinaryTree<T>*>(indexGuid, tree));
        for (auto iter : dataList)
            (*tree).addNode(static_cast<T&&>(iter));
    }
public:
    Relation() = default;
    explicit Relation(const std::forward_list<T>& _dataList)
    {
        dataList = _dataList;
    }

    void addDataList(const std::forward_list<T>& _dataList)
    {
        dataList = _dataList;
        for (auto iter : indexMap)
            for (auto secondIter : dataList)
                iter.second->addNode(static_cast<T&&>(secondIter));
    }

    void addData(T&& data)
    {
        dataList.push_front(data);
        for (std::pair<int, BinaryTree<T>*> it : indexMap)
            it.second->addNode(static_cast<T&&>(data));
    }

    void deleteData(T&& data)
    {
        for (auto iter : dataList)
            if (iter == data)
            {
                dataList.remove(data);
                for (std::pair<int, BinaryTree<T>*> it : indexMap)
                    it.second->deleteNode(static_cast<T&&>(data));
                return;
            }
        throw std::invalid_argument("Value doesn't exist!");
    }

    int addIndex(bool typeTree, Strategy<T> *strategy)
    {
        BinaryTree<T>* tree;
        int indexGuid = (int)random();
        if (typeTree) // RB
            tree = new RBTree<T>(strategy);
        else // AVL
            tree = new AVLTree<T>(strategy);

        addTreeToMap(indexGuid, tree);

        return indexGuid;
    }

    void deleteIndex(int indexGuid)
    {
        if (indexMap.find(indexGuid) != indexMap.end())
        {
            delete indexMap[indexGuid];
            indexMap.erase(indexGuid);
        }
        else
            throw std::invalid_argument("Index does not exist!");
    }

    bool findDataByValue(T&& data)
    {
        for (auto iter : dataList)
            if (iter == data)
                return true;
        return false;
    }

    ~Relation()
    {
        for (std::pair<int, BinaryTree<T>*> it : indexMap)
            delete it.second;
    };
};

#endif //FUNDI_7_RELATION_H
