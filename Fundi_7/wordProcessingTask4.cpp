//
// Created by ayttekao on 4/19/21.
//

#include "relation.h"
#include "strategy.h"
#include <string>
#include <sstream>
#include <ctime>
#include <fstream>
#include <cstring>

struct workerInfo
{
    std::string fullName;
    struct tm contractDuration{};
    int contractPrice = 0;
    int contractId = 0;
};

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

std::forward_list<workerInfo> fromFileToList(const std::string& inputFileName)
{
    std::ifstream inputFile(inputFileName);
    std::string tmpString;
    std::vector<std::string> parsedString;
    std::forward_list<workerInfo> forwardList;
    workerInfo workerInformation;
    std::string str((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    parsedString = split(str, " \n");

    size_t count = 0;
    while (count < parsedString.size())
    {
        if (count == 0 or parsedString[count - 1] == "}")
        {
            workerInformation.fullName = parsedString[count] + " " + parsedString[count + 1] + " " + parsedString[count + 2];
            count++;
        }
        else if (parsedString[count] == "Договор")
        {
            count++;
            workerInformation.contractId = std::stoi(parsedString[count]);
        }
        else if (parsedString[count] == "нач.")
        {
            struct tm tmBuf{};
            struct tm tmBuf2{};
            count++;
            strptime(parsedString[count].c_str(), "%d.%m.%Y", &tmBuf);
            count += 2;
            strptime(parsedString[count].c_str(), "%d.%m.%Y", &tmBuf2);
            workerInformation.contractDuration.tm_yday = std::abs(tmBuf.tm_mday - tmBuf2.tm_mday);
            workerInformation.contractDuration.tm_mon = std::abs(tmBuf.tm_mon - tmBuf2.tm_mon);
            workerInformation.contractDuration.tm_year = tmBuf.tm_year - tmBuf2.tm_year;
        }
        else if (parsedString[count] == "стоимость")
        {
            count++;
            workerInformation.contractPrice = std::stoi(parsedString[count]);
            forwardList.push_front(workerInformation);
        }
        else
            count++;
    }
    return forwardList;
}

class StrategyPrimaryFullNameSecondaryId : public Strategy<workerInfo>{
    int compare(workerInfo left, workerInfo right) const override {
        int comparisonResult = strcmp(left.fullName.c_str(), right.fullName.c_str());
        if (comparisonResult == 0)
        {
            if (left.contractId == right.contractId)
                return 0;
            else if (left.contractId < right.contractId)
                return -1;
            return 1;
        }
        else if (comparisonResult < 0)
            return -1;
        return 1;
    }
};

class StrategyDurationContract : public Strategy<workerInfo>{
    int compare(workerInfo left, workerInfo right) const override {
        time_t t1 = mktime(&left.contractDuration);
        time_t t2 = mktime(&right.contractDuration);
        double diffSecs = difftime(t1, t2); // If positive, then tm1(left) > tm2(right)
        if (t1 == t2)
            return 0;
        else if (diffSecs < 0)
            return -1;
        return 1;
    }
};

class StrategyPrice : public Strategy<workerInfo>{
    int compare(workerInfo left, workerInfo right) const override {
        if (left.contractPrice == right.contractPrice)
            return 0;
        else if (left.contractPrice < right.contractPrice)
            return -1;
        return 1;
    }
};

int main(int argc, char **argv)
{
    Relation<workerInfo> relation(fromFileToList(argv[1]));
    relation.addIndex(RB, new StrategyPrimaryFullNameSecondaryId());
    relation.addIndex(AVL, new StrategyDurationContract());
    relation.addIndex(RB, new StrategyPrice());

    return 0;
}