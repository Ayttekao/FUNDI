#include <iostream>

class TeX_convertible /* 0 */
{
public:
    virtual std::string convert() const = 0;
};

class SquareMatrix : virtual public TeX_convertible /* 1 */
{
private:
    float        epsilon = 1e-6;
    float**      matrixData;
    unsigned int dimension;
public:
    SquareMatrix()
    {
        dimension = 0;
        matrixData = nullptr;
    }
    /* Ключевое слово explicit делает этот конструктор закрытым для выполнения любых неявных преобразований */
    explicit SquareMatrix(unsigned int inputDimension)
    {
        dimension = inputDimension;

        matrixData = new float*[inputDimension];
        for (int row = 0; row < inputDimension; row++)
        {
            matrixData[row] = new float [inputDimension];
            for (int col = 0; col < inputDimension; col++)
                matrixData[row][col] = 0;
        }
    }

    SquareMatrix(const SquareMatrix& originalMatrix)
    {
        unsigned int size = originalMatrix.dimension;
        dimension = originalMatrix.dimension;

        matrixData = new float*[size];
        for (int row = 0; row < size; row++)
        {
            matrixData[row] = new float[size];
            for (int col = 0; col < size; col++)
                matrixData[row][col] = originalMatrix.matrixData[row][col];
        }
    }

    ~SquareMatrix()
    {
        if ( matrixData )
            for (int row = 0; row < dimension; row++ )
                delete []matrixData[row];

        delete []matrixData;
    }

    void setMatrix()
    {
        for (int row = 0; row < dimension; row++)
            for (int col = 0; col < dimension; col++)
                std::cin >> matrixData[row][col];
    }

    unsigned int getDimension() const
    {
        return dimension;
    }

    float getEpsilon() const
    {
        return epsilon;
    }

    bool operator==(const SquareMatrix&rightMatrix)
    {
        unsigned int size = rightMatrix.dimension;

        for (int row = 0; row < size; row++)
            for (int col = 0; col < size; col++)
                if (std::abs(matrixData[row][col] - rightMatrix.matrixData[row][col]) > epsilon)
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
                delete[] matrixData[row];
            delete[] matrixData;
        }
        dimension = rightMatrix.dimension;

        matrixData = new float*[dimension];
        for (int row = 0; row < dimension; row++)
        {
            matrixData[row] = new float[dimension];
            for (int col = 0; col < dimension; col++)
                matrixData[row][col] = rightMatrix.matrixData[row][col];
        }

        return *this;
    }

    SquareMatrix operator+=(const SquareMatrix& rightMatrix) const
    {
        for (int row = 0; row < rightMatrix.dimension; row++)
            for (int col = 0; col < rightMatrix.dimension; col++)
                matrixData[row][col] += rightMatrix.matrixData[row][col];

        return *this;
    }

    SquareMatrix operator+(const SquareMatrix& rightMatrix) const
    {
        return SquareMatrix(*this) += rightMatrix;
    }

    SquareMatrix operator-=(const SquareMatrix& rightMatrix) const
    {
        for (int row = 0; row < rightMatrix.dimension; row++)
            for (int col = 0; col < rightMatrix.dimension; col++)
                matrixData[row][col] -= rightMatrix.matrixData[row][col];

        return *this;
    }

    SquareMatrix operator-(const SquareMatrix& rightMatrix) const
    {
        return SquareMatrix(*this) -= rightMatrix;
    }

    SquareMatrix operator*=(const SquareMatrix& rightMatrix)
    {
        SquareMatrix tempMatrix(getDimension());

        for (int row = 0; row < rightMatrix.dimension; row++)
            for (int col = 0; col < rightMatrix.dimension; col++)
            {
                for (int inner = 0; inner < rightMatrix.dimension; inner++)
                    tempMatrix.matrixData[row][col] += matrixData[row][inner] * rightMatrix.matrixData[inner][col];
            }

        *this = tempMatrix;
        return *this;
    }

    SquareMatrix operator*(const SquareMatrix& rightMatrix)
    {
        return SquareMatrix(*this) *= rightMatrix;
    }

    SquareMatrix operator*=(float num) const
    {
        for (int row = 0; row < this->dimension; row++)
            for (int col = 0; col < this->dimension; col++)
                this->matrixData[row][col] = this->matrixData[row][col] * float(num);

        return *this;
    }

    SquareMatrix operator*(float num) const
    {
        return *this *= num;
    }

    friend SquareMatrix operator*(float num, const SquareMatrix& rightMatrix)
    {
        for (int row = 0; row < rightMatrix.dimension; row++)
            for (int col = 0; col < rightMatrix.dimension; col++)
                rightMatrix.matrixData[row][col] = rightMatrix.matrixData[row][col] * num;

        return rightMatrix;
    }

    float* operator[](int index)
    {
        return matrixData[index];
    }

    friend std::ostream& operator<<(std::ostream &out, const SquareMatrix& rightMatrix)
    {
        out << "This is a Matrix of dimension " << rightMatrix.dimension << std::endl;
        for (int i = 0; i < rightMatrix.dimension; i++)
        {
            for (int j = 0; j < rightMatrix.dimension; j++)
                out << rightMatrix.matrixData[i][j] << " ";
            out << std::endl;
        }

        return out;
    }

    friend std::istream& operator>>(std::istream &in, SquareMatrix& rightMatrix)
    {
        if (rightMatrix.dimension > 0)
        {
            for (int row = 0; row < rightMatrix.dimension; row++)
                delete[] rightMatrix.matrixData[row];
            delete[] rightMatrix.matrixData;
        }

        in >> rightMatrix.dimension;

        rightMatrix.matrixData = new float*[rightMatrix.dimension];
        for (int row = 0; row < rightMatrix.dimension; row++)
        {
            rightMatrix.matrixData[row] = new float[rightMatrix.dimension];
            for (int col = 0; col < rightMatrix.dimension; col++)
                in >> rightMatrix.matrixData[row][col];
        }

        return in;

    }

    friend float determination(SquareMatrix& rightMatrix);

    friend SquareMatrix transpose(SquareMatrix& originalMatrix);

    friend void getCofactor(const SquareMatrix& originalMatrix, SquareMatrix& tempMatrix, int p, int q);

    friend void adjoint(const SquareMatrix& originalMatrix, SquareMatrix& adjMatrix);

    friend bool inverse(SquareMatrix& originalMatrix, SquareMatrix& inverseMatrix);

    friend float trace(SquareMatrix& originalMatrix);

    friend SquareMatrix fastMatrixPow(const SquareMatrix& originalMatrix, int n);

    virtual std::string convert() const override
    {
        return std::string();
    }
};

float determination(SquareMatrix& rightMatrix)
{
    SquareMatrix tmpMatrix = rightMatrix;
    float det = 1;

    if (rightMatrix.dimension == 1)
        det = rightMatrix[0][0];
    else if (rightMatrix.dimension == 2)
        det = rightMatrix.matrixData[0][0] * rightMatrix.matrixData[1][1] -
                (rightMatrix.matrixData[1][0] * rightMatrix.matrixData[0][1]);
    else
        for (int i = 0; i < rightMatrix.dimension; ++i)
        {
            int k = i;
            for (int j = i + 1; j < rightMatrix.dimension; ++j)
                if (std::abs(tmpMatrix.matrixData[j][i]) > std::abs(tmpMatrix.matrixData[k][i]))
                    k = j;

            if (std::abs(tmpMatrix.matrixData[k][i]) < rightMatrix.getEpsilon())
            {
                det = 0;
                break;
            }

            std::swap(tmpMatrix.matrixData[i], tmpMatrix.matrixData[k]);

            if (i != k)
                det = -det;
            det *= tmpMatrix.matrixData[i][i];

            for (int j = i + 1; j < rightMatrix.dimension; ++j)
                tmpMatrix.matrixData[i][j] /= tmpMatrix.matrixData[i][i];

            for (int j = 0; j < rightMatrix.dimension; ++j)
                if (j != i and std::abs(tmpMatrix.matrixData[j][i]) > tmpMatrix.getEpsilon())
                    for (k = i + 1; k < rightMatrix.dimension; ++k)
                        tmpMatrix.matrixData[j][k] -= tmpMatrix.matrixData[i][k] * tmpMatrix.matrixData[j][i];
        }

    return det;
}

SquareMatrix transpose(SquareMatrix& originalMatrix)
{
    SquareMatrix transposeMatrix(originalMatrix.getDimension());

    for(int row = 0; row < transposeMatrix.getDimension(); row++)
        for(int col = 0; col < transposeMatrix.getDimension(); col++)
            transposeMatrix.matrixData[row][col] = originalMatrix.matrixData[col][row];

    return transposeMatrix;
}

void getCofactor(const SquareMatrix& originalMatrix, SquareMatrix& tempMatrix, int p, int q)
{
    int i = 0, j = 0;

    for (int row = 0; row < originalMatrix.getDimension(); row++)
    {
        for (int col = 0; col < originalMatrix.getDimension(); col++)
        {
            if (row != p && col != q)
            {
                tempMatrix.matrixData[i][j++] = originalMatrix.matrixData[row][col];

                if (j == originalMatrix.getDimension() - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void adjoint(const SquareMatrix& originalMatrix, SquareMatrix& adjMatrix)
{
    int sign = 1;
    unsigned int size = originalMatrix.getDimension();
    SquareMatrix tempMatrix(size);

    if (size == 1)
    {
        adjMatrix[0][0] = 1;
        return;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            getCofactor(originalMatrix, tempMatrix, i, j);

            sign = ((i + j) % 2 == 0) ? 1 : -1;

            tempMatrix.dimension = size - 1;
            adjMatrix.matrixData[j][i] = float(sign) * (determination(tempMatrix));
        }
    }

    tempMatrix.dimension = size;
}

bool inverse(SquareMatrix& originalMatrix, SquareMatrix& inverseMatrix)
{
    unsigned int size = originalMatrix.getDimension();
    float det = determination(originalMatrix);

    SquareMatrix adjMatrix(size);
    adjoint(originalMatrix, adjMatrix);

    if (det == 0)
    {
        std::cout << "Singular matrix, can't find its inverse";
        return false;
    }


    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            inverseMatrix[i][j] = adjMatrix[i][j] / float(det);

    return true;
}

float trace(SquareMatrix& originalMatrix)
{
    float result = 0;
    for (int i = 0; i < originalMatrix.dimension; i++)
        result += originalMatrix.matrixData[i][i];

    return result;
}

int binpow(int a, int n)
{
    int res = 1;
    while (n)
        if (n & 1)
        {
            res *= a;
            --n;
        }
        else
        {
            a *= a;
            n >>= 1;
        }
    return res;
}

SquareMatrix fastMatrixPow(const SquareMatrix& originalMatrix, int n)
{
    SquareMatrix result = originalMatrix;

    while (n)
        if (n & 1)
        {
            result = result * originalMatrix;
            --n;
        }
        else
        {
            result = result * result;
            n >>= 1;
        }

    return result;
}

int main()
{
    SquareMatrix testMatrix;
    std::cin >> testMatrix;
    std::cout << testMatrix << std::endl;
    testMatrix *= testMatrix;
    std::cout << testMatrix << std::endl;
    return 0;
}
