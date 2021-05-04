#include <iostream>
#include <fstream>
#include <string>

bool isEqual(const char *firstFileName, const char *secondFileName)
{
    std::ifstream firstFile(firstFileName, std::ios::binary);
    std::ifstream secondFile(secondFileName, std::ios::binary);

    char ch1, ch2;
    bool result = true;
    while (firstFile.get(ch1) and secondFile.get(ch2))
    {
        if (ch1 != ch2)
        {
            result = false;
            break;
        }
    }

    firstFile.close();
    secondFile.close();
    return result;
}

void compressFile(const char *originalFileName, const char *compressedFileName)
{
    std::ifstream originalFile(originalFileName, std::ios::binary);
    std::ofstream compressFile(compressedFileName, std::ios::binary);

    unsigned char count = 1;
    char symbol;

    while(originalFile.get(symbol))
    {
        if(static_cast<unsigned char>(symbol) != originalFile.peek() or count == 255)
        {
            (compressFile.put(count)).put(symbol);
            count = 0;
        }
        ++count;
    }

    originalFile.close();
    compressFile.close();
}

void decompressFile(const char *compressedFileName, const char *decompressedFileName)
{
    std::ifstream compressToDecompress(compressedFileName, std::ios::binary);
    std::ofstream decompress(decompressedFileName, std::ios::binary);

    char codeTextSym;
    char amount;

    while(compressToDecompress.get(amount))
    {
        compressToDecompress.get(codeTextSym);
        for(unsigned i = 0; i < static_cast<unsigned char>(amount); ++i)
            decompress.put(codeTextSym);
    }

    compressToDecompress.close();
    decompress.close();
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Wrong num param!";
        return -1;
    }
    else
    {
        compressFile(argv[1], argv[2]);
        decompressFile(argv[2], argv[3]);

        if (isEqual(argv[1], argv[3]))
            std::cout << "Equal" << std::endl;
        else
            std::cout << "Unequal" << std::endl;
    }
    return 0;
}