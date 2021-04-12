#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

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
    explicit SquareMatrix(int inputDimension)
    {
//        if (inputDimension < 1)
//            // TODO: not do this!
//            throw std::invalid_argument("IncorrectSize");

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
        dimension = 0;
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

    void fillNum(const float& num)
    {
        for (int row = 0; row < dimension; row++)
            for (int col = 0; col < dimension; col++)
                matrixData[row][col] = num;
    }

    bool operator==(const SquareMatrix&rightMatrix) const
    {
        if (dimension != rightMatrix.dimension)
            return false;
        else
            for (int row = 0; row < dimension; row++)
                for (int col = 0; col < dimension; col++)
                    if (std::abs(matrixData[row][col] - rightMatrix.matrixData[row][col]) > epsilon)
                        return false;

        return true;
    }

    bool operator!=(const SquareMatrix& rightMatrix) const
    {
        return !(*this == rightMatrix);
    }

    SquareMatrix& operator=(const SquareMatrix& rightMatrix)
    {
        if (this == &rightMatrix)
        {
            return *this;
        }

        if (dimension > 0)
            clearMatrix();

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

    SquareMatrix& operator+=(const SquareMatrix& rightMatrix)
    {
        if (dimension != rightMatrix.dimension)
            throw std::invalid_argument("Matrix sizes must be the same");

        for (int row = 0; row < rightMatrix.dimension; row++)
            for (int col = 0; col < rightMatrix.dimension; col++)
                matrixData[row][col] += rightMatrix.matrixData[row][col];

        return *this;
    }

    SquareMatrix operator+(const SquareMatrix& rightMatrix) const
    {
        return SquareMatrix(*this) += rightMatrix;
    }

    SquareMatrix& operator-=(const SquareMatrix& rightMatrix)
    {
        if (dimension != rightMatrix.dimension)
            throw std::invalid_argument("Matrix sizes must be the same");
        for (int row = 0; row < rightMatrix.dimension; row++)
            for (int col = 0; col < rightMatrix.dimension; col++)
                matrixData[row][col] -= rightMatrix.matrixData[row][col];

        return *this;
    }

    SquareMatrix operator-(const SquareMatrix& rightMatrix) const
    {
        return SquareMatrix(*this) -= rightMatrix;
    }

    SquareMatrix& operator*=(const SquareMatrix& rightMatrix)
    {
        SquareMatrix tempMatrix((int(dimension)));

        if (dimension != rightMatrix.dimension)
            throw std::invalid_argument("Matrix sizes must be the same");
        for (int row = 0; row < rightMatrix.dimension; row++)
            for (int col = 0; col < rightMatrix.dimension; col++)
                for (int inner = 0; inner < rightMatrix.dimension; inner++)
                    tempMatrix.matrixData[row][col] += matrixData[row][inner] * rightMatrix.matrixData[inner][col];

        *this = tempMatrix;
        return *this;
    }

    SquareMatrix operator*(const SquareMatrix& rightMatrix) const
    {
        return SquareMatrix(*this) *= rightMatrix;
    }

    SquareMatrix& operator*=(const float& num)
    {
        for (int row = 0; row < dimension; row++)
            for (int col = 0; col < dimension; col++)
                matrixData[row][col] = matrixData[row][col] * float(num);

        return *this;
    }

    SquareMatrix operator*(const float& num) const
    {
        return SquareMatrix(*this) *= num;
    }

    friend SquareMatrix operator*(const float& num, const SquareMatrix& rightMatrix)
    {
        SquareMatrix result(rightMatrix);
        for (int row = 0; row < result.dimension; row++)
            for (int col = 0; col < result.dimension; col++)
                result.matrixData[row][col] = result.matrixData[row][col] * num;

        return result;
    }

    struct MatrixIndexer
    {
        int x;
        int y;

        MatrixIndexer(int x, int y) : x(x), y(y)
        {

        }
    };

    float& operator[](const struct MatrixIndexer& indexerParams) const
    {
        if (indexerParams.x < 0 || indexerParams.x >= dimension ||
            indexerParams.y < 0 || indexerParams.y >= dimension)
        {
            // TODO: throw an exception and handle it in calling method
            throw std::exception();
        }
        return matrixData[indexerParams.x][indexerParams.y];
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
        int tmpDimension;
        if (rightMatrix.dimension > 0)
        {
            for (int row = 0; row < rightMatrix.dimension; row++)
                delete[] rightMatrix.matrixData[row];
            delete[] rightMatrix.matrixData;
        }

        in >> tmpDimension;
        if (tmpDimension < 1)
            throw std::invalid_argument("IncorrectSize");
        else
            rightMatrix.dimension = tmpDimension;

        rightMatrix.matrixData = new float*[rightMatrix.dimension];
        for (int row = 0; row < rightMatrix.dimension; row++)
        {
            rightMatrix.matrixData[row] = new float[rightMatrix.dimension];
            for (int col = 0; col < rightMatrix.dimension; col++)
                in >> rightMatrix.matrixData[row][col];
        }

        return in;

    }

    void clearMatrix()
    {
        for (int row = 0; row < dimension; row++)
            delete[] matrixData[row];
        delete[] matrixData;
        matrixData = nullptr;
        // TODO: forgot to set dimension to zero :)
        dimension = 0;
    }

    void createMatrix(const std::vector<float>& values)
    {
        int inner = 0;

        if (dimension > 0)
            clearMatrix();
        dimension = unsigned(sqrt(values.size()));

        matrixData = new float*[dimension];
        for (int row = 0; row < dimension; ++row)
        {
            matrixData[row] = new float[dimension];
            for (int col = 0; col < dimension; ++col)
            {
                matrixData[row][col] = values[inner];
                inner++;
            }
        }
    }

    friend float determinant(const SquareMatrix& rightMatrix);

    friend SquareMatrix transpose(const SquareMatrix& originalMatrix);

    friend void getCofactor(const SquareMatrix& originalMatrix, SquareMatrix& tempMatrix, int p, int q);

    friend void adjoint(const SquareMatrix& originalMatrix, SquareMatrix& adjMatrix);

    friend SquareMatrix inverse(const SquareMatrix& originalMatrix);

    friend float trace(const SquareMatrix& originalMatrix);

    friend SquareMatrix matrixPow(const SquareMatrix& originalMatrix, int n);

/*  \left(\begin{matrix}
    30 & 36 & 42 \\
    66 & 81 & 96 \\
    102 & 126 & 150
    \end{matrix}\right)*/

    std::string convert() const override
    {
        std::string result = "\\left(\\begin{array}{ccc}\n";
        for (int row = 0; row < dimension; ++row)
        {
            for (int col = 0; col < dimension; ++col)
            {
                result += std::to_string(matrixData[row][col]);
                if (col != dimension - 1)
                    result += " & ";
            }
            if (row != dimension - 1)
                result += " \\\\";
            result += "\n";
        }
        result += "\\end{array}\\right)\n";

        return result;
    }
};

float determinant(const SquareMatrix& rightMatrix)
{
    SquareMatrix tmpMatrix = rightMatrix;
    float det = 1;

    if (rightMatrix.dimension == 1)
        det = rightMatrix[SquareMatrix::MatrixIndexer(0, 0)];
    else if (rightMatrix.dimension == 2)
        // TODO: use overloaded indexer :)
        det = rightMatrix[SquareMatrix::MatrixIndexer(0, 0)] * rightMatrix[SquareMatrix::MatrixIndexer(1, 1)] -
                (rightMatrix[SquareMatrix::MatrixIndexer(1, 0)] * rightMatrix[SquareMatrix::MatrixIndexer(0, 1)]);
    else if (rightMatrix.dimension == 3)
    {
        det = rightMatrix[SquareMatrix::MatrixIndexer(0, 0)] * rightMatrix[SquareMatrix::MatrixIndexer(1, 1)]
        * rightMatrix[SquareMatrix::MatrixIndexer(2, 2)] - rightMatrix[SquareMatrix::MatrixIndexer(0, 0)]
        * rightMatrix[SquareMatrix::MatrixIndexer(1, 2)] * rightMatrix[SquareMatrix::MatrixIndexer(2, 1)]
        - rightMatrix[SquareMatrix::MatrixIndexer(0, 1)] * rightMatrix[SquareMatrix::MatrixIndexer(1, 0)]
        * rightMatrix[SquareMatrix::MatrixIndexer(2, 2)] + rightMatrix[SquareMatrix::MatrixIndexer(0, 1)]
        * rightMatrix[SquareMatrix::MatrixIndexer(1, 2)] * rightMatrix[SquareMatrix::MatrixIndexer(2, 0)]
        + rightMatrix[SquareMatrix::MatrixIndexer(0, 2)] * rightMatrix[SquareMatrix::MatrixIndexer(1, 0)]
        * rightMatrix[SquareMatrix::MatrixIndexer(2, 1)] - rightMatrix[SquareMatrix::MatrixIndexer(0, 2)]
        * rightMatrix[SquareMatrix::MatrixIndexer(1, 1)] * rightMatrix[SquareMatrix::MatrixIndexer(2, 0)];
    }
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

SquareMatrix transpose(const SquareMatrix& originalMatrix)
{
    SquareMatrix transposeMatrix(int(originalMatrix.getDimension()));

    for(int row = 0; row < transposeMatrix.getDimension(); row++)
        for(int col = 0; col < transposeMatrix.getDimension(); col++)
            transposeMatrix[SquareMatrix::MatrixIndexer(row, col)] = originalMatrix[SquareMatrix::MatrixIndexer(col, row)];

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
    SquareMatrix tempMatrix((int(size)));

    if (size == 1)
    {
        adjMatrix[SquareMatrix::MatrixIndexer(0, 0)] = 1;
        return;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            getCofactor(originalMatrix, tempMatrix, i, j);

            sign = ((i + j) % 2 == 0) ? 1 : -1;

            tempMatrix.dimension = size - 1;
            adjMatrix.matrixData[j][i] = float(sign) * (determinant(tempMatrix));
        }
    }

    tempMatrix.dimension = size;
}

SquareMatrix inverse(const SquareMatrix& originalMatrix)
{
    SquareMatrix inverseMatrix;
    unsigned int size = originalMatrix.getDimension();
    float det = determinant(originalMatrix);

    SquareMatrix adjMatrix((int(size)));
    adjoint(originalMatrix, adjMatrix);

    if (det == 0)
        throw std::invalid_argument("Singular matrix, can't find its inverse");


    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            inverseMatrix[SquareMatrix::MatrixIndexer(i, j)] = adjMatrix[SquareMatrix::MatrixIndexer(i, j)] / float(det);

    return inverseMatrix;
}

float trace(const SquareMatrix& originalMatrix)
{
    float result = 0;
    for (int i = 0; i < originalMatrix.dimension; i++)
        result += originalMatrix[SquareMatrix::MatrixIndexer(i, i)];

    return result;
}

SquareMatrix matrixPow(const SquareMatrix& originalMatrix, int n)
{
    SquareMatrix result(originalMatrix);

    while (n - 1)
    {
        result *= originalMatrix;
        --n;
    }

    return result;
}

SquareMatrix matrixExp(const SquareMatrix& originalMatrix, int pow)
{
    auto fact = [](auto& self, int N)
    {
        if(N < 0) // если пользователь ввел отрицательное число
            return 0; // возвращаем ноль
        else if (N == 0) // если пользователь ввел ноль,
            return 1; // возвращаем факториал от нуля, который равен 1
        else // во всех остальных случаях
        {
            // Вызываем лямбду передавая в качестве аргумента лмябду по ссылке дальше в саму себя
            return N * self(self, N - 1); // выполняем рекурсивный вызовы функции
        }
    };

    SquareMatrix result(int(originalMatrix.getDimension()));
    int count = 0;
    for (int i = 0; i < result.getDimension(); i++)
        result[SquareMatrix::MatrixIndexer(i, i)] = 1.0;

    while (count++ < pow)
    {
        result += (float(1.0) / float(fact(fact, count))) * matrixPow(originalMatrix, count);
    }

    return result;
}

std::vector<std::string> split(const std::string& str, const std::string& delimer)
{
    std::vector<std::string> wordVector;
    std::stringstream stringStream(str);
    std::string line;
    while(std::getline(stringStream, line))
    {
        std::size_t prev = 0, pos;
        while ((pos = line.find_first_of(delimer, prev)) != std::string::npos)
        {
            if (pos > prev)
                wordVector.push_back(line.substr(prev, pos-prev));
            prev = pos + 1;
        }
        if (prev < line.length())
            wordVector.push_back(line.substr(prev, std::string::npos));
    }

    return wordVector;
}

SquareMatrix calculate(SquareMatrix& first, SquareMatrix& second, const std::string& operation)
{
    SquareMatrix result;
    if (first.getDimension() == 1 and operation == "*")
        result = second * first[SquareMatrix::MatrixIndexer(0, 0)];
    else if (second.getDimension() == 1 and operation == "*")
        result = first * second[SquareMatrix::MatrixIndexer(0, 0)];
    else if (operation == "+")
        result = second + first;
    else if (operation == "-")
        result = second - first;
    else if (operation == "*")
        result = second * first;
    return result;
}

std::string unaryOperators(const std::vector<std::string>& parsedString) /* det, inverse, transpose */
{
    std::string convertedExpression = "$$\n";
    std::string expressionOperator = parsedString[0];
    std::vector<float> tmpValues;
    SquareMatrix matrix;
    SquareMatrix result;
    int n; // MatrExp

    auto iter = parsedString.cbegin();
    iter++;
    for (; iter != parsedString.cend(); iter++)
    {
        if (*iter == ",")
        {
            iter++;
            n = std::stof(*iter);
            break;
        }
        tmpValues.push_back(std::stof(*iter));
    }

    if (expressionOperator != "Exp")
        convertedExpression += expressionOperator;
    else
    {
        convertedExpression += expressionOperator;
        convertedExpression += ", ";
        convertedExpression += std::to_string(n);
    }
    convertedExpression += "\n";

    matrix.createMatrix(tmpValues);
    convertedExpression += matrix.convert();
    convertedExpression += "=\n";

    try {
        if (expressionOperator == "Det")
            convertedExpression += std::to_string(determinant(matrix)) += "\n";
        else if (expressionOperator == "Transpose")
            convertedExpression += transpose(matrix).convert();
        else if (expressionOperator == "Inverse") {
            result = inverse(matrix);
            convertedExpression += result.convert();
        } else if (expressionOperator == "Trace")
            convertedExpression += std::to_string(trace(matrix)) += "\n";
        else if (expressionOperator == "Exp") {
            result = matrixExp(matrix, n);
            convertedExpression += result.convert();
        }
        convertedExpression += "$$\n";
    } catch(const std::exception& e) {
        convertedExpression.clear();
    }
    return convertedExpression;
}

std::string binaryOperators(const std::vector<std::string>& parsedString) // +-*==!=
{
    SquareMatrix firstMatrix;
    SquareMatrix secondMatrix;
    std::vector<float> tmpValues;
    std::string convertedExpression = "$$\n";
    std::string expressionOperator;
    float num;

    for (const auto& item : parsedString)
    {
        if (item.find_first_not_of("0123456789"))
            tmpValues.push_back(std::stof(item));
        else if (item.find_first_not_of("+-*==!="))
        {
            if (tmpValues.size() == 1)
                num = tmpValues[0];
            else
                firstMatrix.createMatrix(tmpValues);
            expressionOperator = item;
            tmpValues.clear();
        }
    }
    if (tmpValues.size() == 1)
        num = tmpValues[0];
    else
        secondMatrix.createMatrix(tmpValues);

    if (firstMatrix.getDimension() == 0)
        convertedExpression += std::to_string(num);
    else
        convertedExpression += firstMatrix.convert();

    convertedExpression += expressionOperator;

    if (secondMatrix.getDimension() == 0)
        convertedExpression += std::to_string(num);
    else
        convertedExpression += secondMatrix.convert();

    convertedExpression += "=\n";
    try {
        if (firstMatrix.getDimension() == 0)
            convertedExpression += (num * secondMatrix).convert();
        else if (secondMatrix.getDimension() == 0)
            convertedExpression += (firstMatrix * num).convert();
        else if (expressionOperator == "==")
            firstMatrix == secondMatrix ? convertedExpression += "True\n" : convertedExpression += "False\n";
        else if (expressionOperator == "!=")
            firstMatrix != secondMatrix ? convertedExpression += "True\n" : convertedExpression += "False\n";
        else
            convertedExpression += calculate(firstMatrix, secondMatrix, expressionOperator).convert();
        convertedExpression += "$$\n";
    } catch (std::exception& e) {
        convertedExpression.clear();
    }
    return convertedExpression;
}

void interpreter(const std::string& inputFileName, const std::string& outputFileName)
{
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);
    std::string tmpString;
    std::vector<std::string> parsedString;

    if (!inputFile)
        throw std::invalid_argument("Uh oh, text could not be opened for reading!");

    while (!inputFile.eof())
    {
        getline(inputFile, tmpString);
        parsedString = split(tmpString, " []");
        if (parsedString[0].find_first_not_of("Det Inverse Transpose Trace Exp"))
            outputFile << unaryOperators(parsedString);
        else
            outputFile << binaryOperators(parsedString);
    }
}

//class Factory
//{
//public:
//    virtual SquareMatrix* Create(int size) = 0;
//    virtual ~Factory()= default;
//};
//
//class SquareMatrixFactory : public Factory
//{
//    SquareMatrix* Create(int size) override
//    {
//        if (size > 0)
//            return new SquareMatrix;
//        else
//            throw std::exception();
//    }
//};
//
//SquareMatrix* foo(Factory *value, int size){
//    return value->Create(size);
//}

int main()
{
    /*try
    {
        std::vector<float> vector = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        SquareMatrix vecMatrix;
        vecMatrix.createMatrixV2(vector.begin(), vector.end());
        std::cout << vecMatrix;
        SquareMatrix testMatrix(3);
        SquareMatrix secondMatrix(2);
        std::cin >> testMatrix;
        std::cout << testMatrix << std::endl;
        std::cout << testMatrix.convert();
        std::cout << (testMatrix == secondMatrix) << std::endl;
    }
    catch (std::invalid_argument&)
    {
        std::cout << "Ты что, дурак блять?";
    }*/


    interpreter("/home/ayttekao/CLionProjects/Fundi/Fundi_6/test.txt",
                "/home/ayttekao/CLionProjects/Fundi/Fundi_6/test_out.txt");
    return 0;
}
