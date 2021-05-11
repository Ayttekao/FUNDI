#include <iostream>
#define SIZE 8
class Solve
{
public:
    virtual void setQueen(int a) = 0;
};

class RecursiveSolve: public Solve
{
public:
    int checkerboard[SIZE][SIZE] = {0};
    int resultsCount = 0;
    RecursiveSolve() = default;

    void displayBoard()
    {
        for (auto & a : checkerboard)
        {
            for (int & b : a)
                std::cout << (b ? "Q " : ". ");
            std::cout << '\n';
        }
    }

    bool checkQueen(int a, int b)
    {
        for (int i = 0; i < a; ++i)
            if (checkerboard[i][b])
                return false;

        for (int i = 1; i <= a && b-i >= 0; ++i)
            if (checkerboard[a - i][b - i])
                return false;

        for (int i = 1; i <= a && b+i < SIZE; i++)
            if (checkerboard[a - i][b + i])
                return false;

        return true;
    }

    void setQueen(int a) override
    {
        if(a == SIZE)
        {
            displayBoard();
            std::cout << "Result recursive: " << ++resultsCount << "\n\n";
            return;
        }

        for(int i = 0; i < SIZE; ++i)
        {
            if(checkQueen(a, i))
            {
                checkerboard[a][i] = 1;
                setQueen(a + 1);
                checkerboard[a][i] = 0;
            }
        }
    }
    ~RecursiveSolve() = default;
};

class IterativeSolve: public Solve
{
public:
    struct Queens
    {
        int x, y;
        explicit Queens(int m_x = 0, int m_y = 0) : x(m_x), y(m_y) {}
    };

    static void Fill(int** field)
    {
        for (int row = 0; row < SIZE; row++)
            for (int col = 0; col < SIZE; col++) 
                field[row][col] = 0;
    }

    static void display(int** field)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++) 
                std::cout << field[i][j] << ' ';
            std::cout << std::endl;
        }
    }

    static void displayBoard(int** field)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if(field[i][j] == 0)
                    std::cout << ". ";
                else std::cout << "Q ";
            }
            std::cout << std::endl;
        }
    }

    static bool isKill(const Queens& queens, const Queens* allQueens, int N)
    {
        for (int i = 0; i < N; i++)
        {
            int dx = abs(queens.x - allQueens[i].x);
            int dy = abs(queens.y - allQueens[i].y);
            if (dx == 0 || dy == 0 || (dx  == dy)) return true;
        }
        return false;
    }

    void setQueen(int a) override
    {
        int     solution = 0;
        int     count_ferz = 0;
        int**   field = new int*[SIZE];
        auto*   allQueens = new Queens[SIZE];

        for (int i = 0; i < SIZE; i++)
            field[i] = new int[SIZE];
        Fill(field);

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                Queens temp(j, i);
                bool result = isKill(temp, allQueens, count_ferz);
                if (!result)
                {
                    field[i][j] = 1;
                    allQueens[count_ferz].x = j;
                    allQueens[count_ferz].y = i;
                    count_ferz++;
                    if (count_ferz == SIZE)
                    {
                        std::cout <<"Result iterative: "<< solution + 1 << std::endl;
                        displayBoard(field);
                        std::cout << std::endl;

                        solution++;
                        field[allQueens[count_ferz - 1].y][allQueens[count_ferz - 1].x] = 0;
                        i = allQueens[count_ferz - 1].y;
                        j = allQueens[count_ferz - 1].x;
                        count_ferz--;
                        if((j + 1) == SIZE && count_ferz != 0)
                        {
                            field[allQueens[count_ferz - 1].y][allQueens[count_ferz - 1].x] = 0;
                            i = allQueens[count_ferz - 1].y;
                            j = allQueens[count_ferz - 1].x;
                            count_ferz--;
                        }
                        continue;
                    }
                    break;
                }
                else if ((j + 1) == SIZE)
                {
                    field[allQueens[count_ferz - 1].y][allQueens[count_ferz - 1].x] = 0;
                    i = allQueens[count_ferz - 1].y;
                    j = allQueens[count_ferz - 1].x;
                    count_ferz--;
                    if ((j+1) == SIZE && count_ferz != 0)
                    {
                        field[allQueens[count_ferz - 1].y][allQueens[count_ferz - 1].x] = 0;
                        i = allQueens[count_ferz - 1].y;
                        j = allQueens[count_ferz - 1].x;
                        count_ferz--;
                    }
                }
            }
        }

        for (int i = 0; i < SIZE; i++) delete field[i];
        delete[] field;
        delete[] allQueens;
    }

};