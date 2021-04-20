//
// Created by ayttekao on 4/19/21.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "relation.h"
#include "strategy.h"

struct chatMessage
{
    chatMessage() = default;

    struct tm dateTime;
    std::string userName;
    std::string message;

    chatMessage& operator=(const chatMessage& originalMessage)
    {
        if (this == &originalMessage)
            return *this;

        dateTime = originalMessage.dateTime;
        userName = originalMessage.userName;
        message = originalMessage.message;

        return *this;
    }
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

void interpreter(const std::string& inputFileName, const std::string& outputFileName)
{
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);
    std::string tmpString;
    std::vector<std::string> parsedString;
    chatMessage message;

    if (!inputFile)
        throw std::invalid_argument("Uh oh, text could not be opened for reading!");

    while (!inputFile.eof())
    {
        getline(inputFile, tmpString);
        parsedString = split(tmpString, "<:>");
        message.dateTime.tm_hour = std::stoi(parsedString[0]);
        message.dateTime.tm_min = std::stoi(parsedString[1]);
        message.userName = parsedString[3];
        message.message = parsedString[6];
    }
}

//class StrategyInt : public Strategy<int>{
//    int compare(int left, int right) const override {
//        if (left == right)
//            return 0;
//        else if (left < right)
//            return -1;
//        return 1;
//    }
//};

class StrategyDateTime : public Strategy<chatMessage>{
    int compare(chatMessage left, chatMessage right) const override {
        time_t t1 = mktime(&left.dateTime);
        time_t t2 = mktime(&right.dateTime);
        double diffSecs = difftime(t1, t2); // If positive, then tm1(left) > tm2(right)
        if (t1 == t2)
            return 0;
        else if (diffSecs < 0)
            return -1;
        return 1;
    }
};

int main(int argc, char **argv)
{
    Strategy<chatMessage> *dateTimeStrategy = new StrategyDateTime();
    Strategy<int> *intStrategy = new StrategyInt;

    Relation<int> relation1;
    Relation<chatMessage> relation;
    int firstGuid = relation.addIndex(RB, dateTimeStrategy);
    int secondGuid = relation1.addIndex(RB, intStrategy);
    interpreter(argv[1], argv[2]);
}
