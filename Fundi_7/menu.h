//
// Created by ayttekao on 4/17/21.
//

#ifndef FUNDI_7_MENU_H
#define FUNDI_7_MENU_H

#include <iostream>
#include <vector>
#include "binaryTree.h"
#include "AVLTree.h"
#include "RBTree.h"
#include <ctime>
#include <random>
#include <algorithm>

std::vector<int> randomVector(size_t size)
{
    std::vector<int> v(size);
    std::random_device r;
    generate(v.begin(), v.end(), [&]{return r();});
    return v;
}

int getRandomElement(const std::vector<int>& vector)
{
    return vector[rand() % vector.size()];
}

void menu()
{
    int choice = 0;
    Strategy<int> *testStrategy = new StrategyInt();
    AVLTree<int> AVLTree(testStrategy);
    RBTree<int> RBTree(testStrategy);
    unsigned int startTime;
    unsigned int endTime;
    unsigned int requiredTime;
    int randItem;

    std::cout << "Function for comparing AVL tree and red-black tree algorithms\n";
    uint32_t numOfElement;
    std::cout << "\nEnter the number of items: ";
    std::cin >> numOfElement;
    std::vector<int> vector = randomVector(numOfElement);

    while (choice != 4)
    {
        std::cout << "\n========MENU========";
        std::cout << "\n\n1.Compare Insert";
        std::cout << "\n2.Compare Search";
        std::cout << "\n3.Compare Delete";
        std::cout << "\n4.Exit";

        std::cout << "\n\nEnter your choice : ";

        std::cin >> choice;


        switch (choice)
        {
            case 1:
                if (!AVLTree.empty() or !RBTree.empty())
                {
                    std::cout << "Tree's are not empty!\n";
                    break;
                }
                startTime = clock();
                AVLTree.vectorToTree(vector);
                endTime = clock();
                requiredTime = endTime - startTime;
                std::cout << "Time to insert " << numOfElement << " elements into AVL tree: " << requiredTime / 1000.0
                          << " seconds" << std::endl;

                startTime = clock();
                RBTree.vectorToTree(vector);
                endTime = clock();
                requiredTime = endTime - startTime;
                std::cout << "Time to insert " << numOfElement << " elements into Red-Black tree: "
                          << requiredTime / 1000.0
                          << " seconds" << std::endl;
                break;
            case 2:
                if (AVLTree.empty() or RBTree.empty())
                {
                    std::cout << "Tree's are empty!\n";
                    break;
                }
                randItem = getRandomElement(vector);
                startTime = clock();
                AVLTree.searchByValue(static_cast<int &&>(randItem));
                endTime = clock();
                requiredTime = endTime - startTime;
                std::cout << "Time to find " << randItem << " into AVL tree: " << requiredTime / 1000.0
                          << " seconds" << std::endl;

                startTime = clock();
                RBTree.searchByValue(static_cast<int &&>(randItem));
                endTime = clock();
                requiredTime = endTime - startTime;
                std::cout << "Time to find " << randItem << " into Red-Black tree: " << requiredTime / 1000.0
                          << " seconds" << std::endl;
                break;
            case 3:
                if (AVLTree.empty() or RBTree.empty())
                {
                    std::cout << "Tree's are empty!\n";
                    break;
                }
                randItem = getRandomElement(vector);
                startTime = clock();
                AVLTree.deleteNode(static_cast<int &&>(randItem));
                endTime = clock();
                requiredTime = endTime - startTime;
                std::cout << "Time to delete " << randItem << " into AVL tree: " << requiredTime / 1000.0
                          << " seconds" << std::endl;

                startTime = clock();
                RBTree.deleteNode(static_cast<int &&>(randItem));
                endTime = clock();
                requiredTime = endTime - startTime;
                std::cout << "Time to delete " << randItem << " into Red-Black tree: " << requiredTime / 1000.0
                          << " seconds" << std::endl;
                break;
        default:
            std::cout << "Another input, retry\n";
        }
    }
    delete testStrategy;
}

#endif //FUNDI_7_MENU_H
