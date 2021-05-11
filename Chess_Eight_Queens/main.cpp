#include <iostream>
#include "EightQueensProblem.h"
#include <ctime>

void compareRecursiveAndIterative()
{
    RecursiveSolve recursive;
    unsigned int start_time =  clock();
    recursive.setQueen(0);
    unsigned int end_time = clock();
    std::cout << "Recursive: " << (end_time - start_time)/1000.0 << std::endl;
    IterativeSolve iterative;
    start_time = clock();
    iterative.setQueen(0);
    end_time = clock();
    std::cout << "Iterative: " << (end_time - start_time)/1000.0 << std::endl;
}

int main()
{
    compareRecursiveAndIterative();
    return 0;
}
