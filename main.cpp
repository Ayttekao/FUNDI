#include <iostream>
#define EPS 0.000001

class TeX_convertible /* 0 */
{
public:
    virtual std::string convert() const = 0;
};


class SquareMatrix : virtual public TeX_convertible /* 1 */
{
private:
    float**      matrix;
    unsigned int dimension;
public:
    SquareMatrix()
    {
        dimension = 0;
        matrix = nullptr;
    }
    /* Ключевое слово explicit делает этот конструктор закрытым для выполнения любых неявных преобразований */
    explicit SquareMatrix(int inputDimension)
    {
        dimension = inputDimension;

        matrix = new float*[inputDimension];
        for (int row = 0; row < inputDimension; row++)
        {
            matrix[row] = new float [inputDimension];
            for (int col = 0; col < inputDimension; col++)
                matrix[row][col] = 0;
        }
    }

    SquareMatrix(const SquareMatrix& originalMatrix)
    {
        unsigned int size = originalMatrix.dimension;
        dimension = originalMatrix.dimension;

        matrix = new float*[size];
        for (int row = 0; row < size; row++)
        {
            matrix[row] = new float[size];
            for (int col = 0; col < size; col++)
                matrix[row][col] = originalMatrix.matrix[row][col];
        }
    }

    ~SquareMatrix()
    {
        if ( matrix )
            for (int row = 0; row < dimension; row++ )
                delete []matrix[row];

        delete []matrix;
    }

    void setMatrix()
    {
        for (int row = 0; row < dimension; row++)
            for (int col = 0; col < dimension; col++)
                std::cin >> matrix[row][col];
    }

    bool operator==(const SquareMatrix&rightMatrix)
    {
        unsigned int size = rightMatrix.dimension;

        for (int row = 0; row < size; row++)
            for (int col = 0; col < size; col++)
                if (std::abs(matrix[row][col] - rightMatrix.matrix[row][col]) > EPS)
                    return false;

        return true;
    }

    bool operator!=(const SquareMatrix& rightMatrix)
    {
        return !(*this == rightMatrix);
    }

    SquareMatrix operator=(const SquareMatrix& rightMatrix)
    {
        if (dimension > 0)
        {
            for (int row = 0; row < dimension; row++)
                delete[] matrix[row];
            delete[] matrix;
        }
        dimension = rightMatrix.dimension;

        matrix = new float*[dimension];
        for (int row = 0; row < dimension; row++)
        {
            matrix[row] = new float[dimension];
            for (int col = 0; col < dimension; col++)
                matrix[row][col] = rightMatrix.matrix[row][col];
        }

        return *this;
    }

    SquareMatrix operator+=(const SquareMatrix& rightMatrix)
    {
        for (int row = 0; row < rightMatrix.dimension; row++)
            for (int col = 0; col < rightMatrix.dimension; col++)
                matrix[row][col] += rightMatrix.matrix[row][col];

        return *this;
    }

    SquareMatrix operator+(const SquareMatrix& rightMatrix)
    {
        return SquareMatrix(*this) += rightMatrix;
    }

    SquareMatrix operator*=(const SquareMatrix& rightMatrix)
    {
        for (int row = 0; row < rightMatrix.dimension; row++)
            for (int col = 0; col < rightMatrix.dimension; col++)
                matrix[]
    }

    float* operator[](int index)
    {
        return matrix[index];
    }

    friend std::ostream& operator<<(std::ostream &out, const SquareMatrix& rightMatrix)
    {
        out << "This is a Matrix of dimension " << rightMatrix.dimension << std::endl;
        for (int i = 0; i < rightMatrix.dimension; i++)
        {
            for (int j = 0; j < rightMatrix.dimension; j++)
                out << rightMatrix.matrix[i][j] << " ";
            out << std::endl;
        }

        return out;
    }

    virtual std::string convert() const override
    {
        return std::string();
    }
};


int main()
{
    SquareMatrix masmdasmd;
    SquareMatrix Matrix(2);
    Matrix.setMatrix();
    SquareMatrix mat(Matrix);
    SquareMatrix testMatrix;
    testMatrix = Matrix;
    std::cout << testMatrix[1][1] << std::endl;
    std::cout << testMatrix;
    testMatrix += Matrix;
    testMatrix = mat + Matrix;
    std::cout << (Matrix == mat);
    return 0;
}
