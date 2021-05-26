//
// Created by ayttekao on 5/19/21.
//

#ifndef FUNDI_COURSEWORK_4_SEMESTER__DECORATORLIST_H
#define FUNDI_COURSEWORK_4_SEMESTER__DECORATORLIST_H

#include <memory>
#include <cstring>
#include "strategy.h"
#include "decorator.h"
#include "countingStatistics.h"
#include <map>

class DecoratorList : public Decorator<PopulationCensus>
{
private:
    std::list<std::shared_ptr<PopulationCensus>> list;
    std::shared_ptr<PopulationCensus> innerFind(const std::shared_ptr<PopulationCensus>& censusPtr,
                                                const Strategy<std::shared_ptr<PopulationCensus>>* currentStrategy)
    {
        if (censusPtr == nullptr)
            throw std::invalid_argument("");
        int comparisonResult;
        for (const auto& iter : list)
        {
            comparisonResult = currentStrategy->compare(iter, std::shared_ptr<PopulationCensus>(censusPtr));
            if (comparisonResult == 0)
                return std::shared_ptr<PopulationCensus>(iter);
        }
        return nullptr;
    }
    static void fieldSelectionMenu()
    {
        std::cout << "1. Номер переписного участка\n"
                     "2. Имя\n"
                     "3. Место рождения\n"
                     "4. Гражданство\n"
                     "5. Номер бланка\n>";
    }
    static void createComparerAndCensus(PopulationCensus** census, Strategy<std::shared_ptr<PopulationCensus>>** strategy, int choice)
    {
        int inputValue;
        std::string tmpString;

        *census = new PopulationCensus();

        switch (choice) {
            case 1:
                std::cout << "Введите номер участка: ";
                std::cin >> inputValue;
                (*census)->setEnumerationAreaNumber(inputValue);
                *strategy = new StrategyEnumerationAreaNumber();
                break;
            case 2:
                std::cout << "Введите имя: ";
                std::cin >> tmpString;
                (*census)->setFullName(tmpString);
                *strategy = new StrategyFullName();
                break;
            case 3:
                std::cout << "Введите место: ";
                std::cin >> tmpString;
                (*census)->setPlaceOfBirth(tmpString);
                *strategy = new StrategyPlaceOfBirth();
                break;
            case 4:
                std::cout << "Введите гражданство: ";
                (*census)->setCitizenship(tmpString);
                *strategy = new StrategyCitizenship();
                break;
            case 5:
                std::cout << "Введите номер бланка: ";
                std::cin >> inputValue;
                (*census)->setFormNumber(inputValue);;
                *strategy = new StrategyFormNumber();
                break;
            default:
                throw std::invalid_argument("");
        }
    }
public:
    void add(std::shared_ptr<PopulationCensus> data) override
    {
        this->list.emplace_back(data);
    }
    void remove() override
    {
        int comparisonResult;
        bool removeAllOccurrences;
        std::shared_ptr<PopulationCensus> censusPtr;

        PopulationCensus* census = nullptr;
        PopulationCensus tmp;
        Strategy<std::shared_ptr<PopulationCensus>> *strategy = nullptr;
        std::cout << "Удалить все совпадения? (если выбрано 'нет', то удалится первый найденный элемент):\n"
                     "1. Да\n"
                     "2. Нет\n>";
        std::cin >> comparisonResult;
        if (comparisonResult == 1)
            removeAllOccurrences = true;
        else if (comparisonResult == 2)
            removeAllOccurrences = false;
        else
            throw std::invalid_argument("Invalid input!");

        std::cout << "Выберете поле для удаления:\n";
        fieldSelectionMenu();
        std::cin >> comparisonResult;
        createComparerAndCensus(&census, &strategy, comparisonResult);
        tmp = *census;
        if (removeAllOccurrences) {
            while (true) {
                censusPtr = innerFind(std::shared_ptr<PopulationCensus>(std::shared_ptr<PopulationCensus>(census)),
                                      strategy);
                census = new PopulationCensus(tmp);
                if (censusPtr == nullptr)
                    break;
                list.remove(censusPtr);
            }
            delete census;
        }
        else
        {
            censusPtr = innerFind(std::shared_ptr<PopulationCensus>(census), strategy);
            if (censusPtr == nullptr)
            {
                std::cout << "Данные не найдены\n";
                return;
            }
            list.remove(censusPtr);
            std::cout << "Данные удалены\n";
        }
        delete strategy;
    }
    std::list<std::shared_ptr<PopulationCensus>> find() override
    {
        int comparisonResult;
        PopulationCensus* census;
        PopulationCensus tmp;
        Strategy<std::shared_ptr<PopulationCensus>> *strategy = nullptr;
        std::list<std::shared_ptr<PopulationCensus>> foundItems;
        std::cout << "Выберете поле для поиска:\n";
        fieldSelectionMenu();
        std::cin >> comparisonResult;
        createComparerAndCensus(&census, &strategy, comparisonResult);
        tmp = *census;
        for (const auto& iter : list)
        {
            comparisonResult = strategy->compare(iter, std::shared_ptr<PopulationCensus>(census));
            if (comparisonResult == 0)
                foundItems.emplace_back(iter);
            census = new PopulationCensus(tmp);
        }
        delete census;
        delete strategy;
        return foundItems;
    }
    void countingStatistics() override
    {
        CountingStatistics calculate(list);
        calculate.countingStatistics();
    }
    DecoratorList()= default;
    ~DecoratorList() override = default;

};


#endif //FUNDI_COURSEWORK_4_SEMESTER__DECORATORLIST_H
