//
// Created by ayttekao on 5/19/21.
//

#ifndef FUNDI_COURSEWORK_4_SEMESTER__DECORATORAVL_H
#define FUNDI_COURSEWORK_4_SEMESTER__DECORATORAVL_H

#include "AVLTree.h"
#include "strategy.h"
#include "countingStatistics.h"
#include <forward_list>
#include <map>

class DecoratorAVL : public Decorator<PopulationCensus>
{
private:
    std::forward_list<std::shared_ptr<PopulationCensus>> dataList;
    std::map<int, BinaryTree<std::shared_ptr<PopulationCensus>>*> indexMap;
    void addTreeToMap(int indexGuid, BinaryTree<std::shared_ptr<PopulationCensus>>* tree)
    {
        indexMap.insert(std::pair<int, BinaryTree<std::shared_ptr<PopulationCensus>>*>(indexGuid, tree));
        for (const auto& iter : dataList)
            (*tree).addNode(iter);
    }
    static void fieldSelectionMenu()
    {
        std::cout << "1. Номер переписного участка\n"
                     "2. Имя\n"
                     "3. Место рождения\n"
                     "4. Гражданство\n"
                     "5. Номер бланка\n>";
    }
    static void createCensus(PopulationCensus** census, int choice)
    {
        int inputValue;
        std::string tmpString;

        *census = new PopulationCensus();

        switch (choice) {
            case 1:
                std::cout << "Введите номер участка: ";
                std::cin >> inputValue;
                (*census)->setEnumerationAreaNumber(inputValue);
                break;
            case 2:
                std::cout << "Введите имя: ";
                std::cin >> tmpString;
                (*census)->setFullName(tmpString);
                break;
            case 3:
                std::cout << "Введите место: ";
                std::cin >> tmpString;
                (*census)->setPlaceOfBirth(tmpString);
                break;
            case 4:
                std::cout << "Введите гражданство: ";
                (*census)->setCitizenship(tmpString);
                break;
            case 5:
                std::cout << "Введите номер бланка: ";
                std::cin >> inputValue;
                (*census)->setFormNumber(inputValue);
                break;
            default:
                throw std::invalid_argument("");
        }
    }
    void deleteData(const std::shared_ptr<PopulationCensus>& data)
    {
        std::shared_ptr<PopulationCensus> tmpData = data;
        for (const auto& iter : dataList)
            if (iter == data)
            {
                tmpData = data;
                dataList.remove(tmpData);
                for (std::pair<int, BinaryTree<std::shared_ptr<PopulationCensus>>*> it : indexMap)
                    it.second->deleteNode(std::shared_ptr<PopulationCensus>(tmpData));
                return;
            }
        throw std::invalid_argument("Value doesn't exist!");
    }
public:
    void add(std::shared_ptr<PopulationCensus> data) override
    {
        dataList.emplace_front(data);
        for (std::pair<int, BinaryTree<std::shared_ptr<PopulationCensus>>*> it : indexMap)
            it.second->addNode(data);
    }
    std::list<std::shared_ptr<PopulationCensus>> find() override
    {
        int choice;
        std::list<std::shared_ptr<PopulationCensus>> list;
        AVLTreeNode<std::shared_ptr<PopulationCensus>>* tmpNode;
        PopulationCensus* census = nullptr;
        PopulationCensus tmp;
        std::cout << "Выберете поле для поиска:\n";
        fieldSelectionMenu();
        std::cin >> choice;
        createCensus(&census, choice);
        tmp = *census;
        while (true)
        {
            tmpNode = static_cast<AVLTreeNode<std::shared_ptr<PopulationCensus>> *>(indexMap.find(
                    choice)->second->searchByValue(std::shared_ptr<PopulationCensus>(census)));

            census = new PopulationCensus(tmp);
            if (tmpNode == nullptr)
                break;

            list.emplace_back(tmpNode->value);
        }
        delete census;

        return list;
    }
    void remove() override
    {
        bool removeAllOccurrences;
        int choice;
        std::shared_ptr<PopulationCensus> censusPtr;
        AVLTreeNode<std::shared_ptr<PopulationCensus>>* tmpNode;
        PopulationCensus* census = nullptr;
        PopulationCensus tmp;

        std::cout << "Удалить все совпадения? (если выбрано 'нет', то удалится первый найденный элемент):\n"
                     "1. Да\n"
                     "2. Нет\n>";
        std::cin >> choice;
        if (choice == 1)
            removeAllOccurrences = true;
        else if (choice == 2)
            removeAllOccurrences = false;
        else
            throw std::invalid_argument("Invalid input!");

        std::cout << "Выберете поле для удаления:\n";
        fieldSelectionMenu();
        std::cin >> choice;
        createCensus(&census, choice);
        tmp = *census;
        if (removeAllOccurrences)
        {
            while (true)
            {
                tmpNode = static_cast<AVLTreeNode<std::shared_ptr<PopulationCensus>> *>(indexMap.find(
                        choice)->second->searchByValue(std::shared_ptr<PopulationCensus>(census)));

                census = new PopulationCensus(tmp);
                if (tmpNode == nullptr)
                    break;

                deleteData(tmpNode->value);
            }
            delete census;
        }
        else
        {
            tmpNode = static_cast<AVLTreeNode<std::shared_ptr<PopulationCensus>> *>(indexMap.find(
                    choice)->second->searchByValue(std::shared_ptr<PopulationCensus>(census)));

            if (tmpNode == nullptr)
            {
                std::cout << "Данные не найдены\n";
                return;
            }
            deleteData(tmpNode->value);
            std::cout << "Данные удалены\n";
        }
    }
    void countingStatistics() override
    {
        CountingStatistics calculate(dataList);
        calculate.countingStatistics();
    }
    DecoratorAVL()
    {
        BinaryTree<std::shared_ptr<PopulationCensus>>* EnumerationAreaNumberTree = new AVLTree<std::shared_ptr<PopulationCensus>>(new StrategyEnumerationAreaNumber);
        BinaryTree<std::shared_ptr<PopulationCensus>>* FullNameTree = new AVLTree<std::shared_ptr<PopulationCensus>>(new StrategyFullName);
        BinaryTree<std::shared_ptr<PopulationCensus>>* placeOfBirthTree = new AVLTree<std::shared_ptr<PopulationCensus>>(new StrategyPlaceOfBirth);
        BinaryTree<std::shared_ptr<PopulationCensus>>* CitizenshipTree = new AVLTree<std::shared_ptr<PopulationCensus>>(new StrategyCitizenship);
        BinaryTree<std::shared_ptr<PopulationCensus>>* FormNumberTree = new AVLTree<std::shared_ptr<PopulationCensus>>(new StrategyFormNumber);
        addTreeToMap(1, EnumerationAreaNumberTree);
        addTreeToMap(2, FullNameTree);
        addTreeToMap(3, placeOfBirthTree);
        addTreeToMap(4, CitizenshipTree);
        addTreeToMap(5, FormNumberTree);
    }
    ~DecoratorAVL() override
    {
        for (std::pair<int, BinaryTree<std::shared_ptr<PopulationCensus>>*> it : indexMap)
            delete it.second;
    }
};

#endif //FUNDI_COURSEWORK_4_SEMESTER__DECORATORAVL_H
