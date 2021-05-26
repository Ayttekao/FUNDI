//
// Created by ayttekao on 5/20/21.
//

#ifndef FUNDI_COURSEWORK_4_SEMESTER__MENU_H
#define FUNDI_COURSEWORK_4_SEMESTER__MENU_H

#include "PopulationCensus.h"
#include "decoratorList.h"
#include "decoratorAVL.h"

void menu()
{
    uint16_t choice = 0;
    uint32_t count;
    Decorator<PopulationCensus> *decorator;
    while (choice != 255)
    {
        std::cout << "Приложение для обработки данных переписи населения\n"
                     "1. Сгенерировать и обработать данные\n"
                     "2. Выход\n>";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Обработать данные с помощью коллекции:\n"
                             "1. АВЛ Дерева\n"
                             "2. Двунаправленного связанного списка элементов (стандартная библиотека шаблонов)\n>";
                std::cin >> choice;
                if (choice == 1)
                    decorator = new DecoratorAVL();
                else if (choice == 2)
                    decorator = new DecoratorList();
                else
                {
                    std::cout << "Неккоректный ввод!\n";
                    break;
                }
                std::cout << "Какое количество анкет вы хотите сгенерировать?\n>";
                std::cin >> count;
                generateOver(decorator, count);
                while (choice != 254)
                {
                    std::cout << "Что вы хотите сделать?\n"
                                 "1. Найти форму по одному из полей\n"
                                 "2. Удалить форму по одному из полей\n"
                                 "3. Добавить форму\n"
                                 "4. Вывести статистическую обработку результатов\n"
                                 "5. Завершить работу с анкетами\n>";
                    std::cin >> choice;
                    switch (choice) {
                        case 1:
                        {
                            std::list<std::shared_ptr<PopulationCensus>> foundList;
                            foundList = decorator->find();
                            if (foundList.empty())
                                std::cout << "Поиск не дал результатов\n";
                            break;
                        }
                        case 2:
                            try {
                                decorator->remove();
                            } catch (const std::exception& e){
                                std::cout << e.what();
                            }
                            break;
                        case 3:
                        {
                            PopulationCensus tmpCensus;
                            std::cin >> tmpCensus;
                            decorator->add(std::shared_ptr<PopulationCensus>(&tmpCensus));
                            break;
                        }
                        case 4:
                            decorator->countingStatistics();
                            break;
                        case 5:
                            std::cout << "Завершение работы с анкетами\n";
                            choice = 254;
                            delete decorator;
                            break;
                        default:
                            std::cout << "Не удалось обработать выбор, попробуйте ещё раз\n";
                    }
                }
                break;
            case 2:
                std::cout << "Завершение работы\n";
                choice = 255;
                break;
            default:
                std::cout << "Не удалось обработать выбор, попробуйте ещё раз\n";
        }
    }
}

#endif //FUNDI_COURSEWORK_4_SEMESTER__MENU_H
