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
#include <cstring>

struct chatMessage
{
    chatMessage() = default;

    struct tm dateTime{};
    std::string userName;
    std::string message;
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

std::forward_list<chatMessage> fromFileToList(const std::string& inputFileName)
{
    std::ifstream inputFile(inputFileName);
    std::string tmpString;
    std::vector<std::string> parsedString;
    std::forward_list<chatMessage> forwardList;
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
        forwardList.push_front(message);
    }
    return forwardList;
}

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

class UsernameCaseSensitiveStrategy : public Strategy<chatMessage>{
    int compare(chatMessage left, chatMessage right) const override {
        int comparisonResult = strcmp(left.userName.c_str(), right.userName.c_str());
        if (comparisonResult > 0)
            return 1;
        else if (comparisonResult < 0)
            return -1;
        return 0;
    }
};

class UsernameCaseInsensitiveStrategy : public Strategy<chatMessage>{
    int compare(chatMessage left, chatMessage right) const override {
        for (auto &c: left.userName) c = (char)std::toupper(c);
        for (auto &c: right.userName) c = (char)std::toupper(c);
        int comparisonResult = strcmp(left.userName.c_str(), right.userName.c_str());
        if (comparisonResult > 0)
            return 1;
        else if (comparisonResult < 0)
            return -1;
        return 0;
    }
};

class PrimaryDateTimeSecondaryUsernameCaseInsensitive : public Strategy<chatMessage>{
    Strategy<chatMessage>* primaryComp = new StrategyDateTime();
    Strategy<chatMessage>* secondaryComp = new UsernameCaseInsensitiveStrategy();
    int compare(chatMessage left, chatMessage right) const override{
        int primaryComparisonResult = primaryComp->compare(left, right);
        if (primaryComparisonResult == 0)
        {
            int secondaryComparisonResult = secondaryComp->compare(left, right);
            if (secondaryComparisonResult == -1)
                return -1;
            else if (secondaryComparisonResult == 1)
                return 1;
            return 0;
        }
        else if (primaryComparisonResult == -1)
            return -1;
        return 1;
    }
};

int main(int argc, char **argv)
{
    std::vector<int> guidVector;
    Relation<chatMessage> relation;
    guidVector.push_back(relation.addIndex(AVL, new StrategyDateTime()));
    relation.addDataList(fromFileToList(argv[1]));
    guidVector.push_back(relation.addIndex(RB, new UsernameCaseSensitiveStrategy()));
    guidVector.push_back(relation.addIndex(AVL, new UsernameCaseInsensitiveStrategy()));
    guidVector.push_back(relation.addIndex(RB, new PrimaryDateTimeSecondaryUsernameCaseInsensitive()));

    return 0;
}
