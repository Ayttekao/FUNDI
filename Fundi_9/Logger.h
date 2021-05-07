//
// Created by ayttekao on 4/29/21.
//

#ifndef FUNDI_9_LOGGER_H
#define FUNDI_9_LOGGER_H

#define TRACE 0
#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4
#define FATAL 5

#include <fstream>
#include <forward_list>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>
#include <climits>
#include <unistd.h>
#include "nlohmannjson/include/nlohmann/json.hpp"

struct streamInfo
{
    streamInfo(std::ostream* basicOstream_, uint8_t priority_) : basicOstream(basicOstream_), priority(priority_) {}
    std::ostream* basicOstream;
    uint8_t priority;
    bool operator==(const streamInfo& rightInfo) const
    {
        if (priority == rightInfo.priority and basicOstream == rightInfo.basicOstream)
            return true;
        return false;
    }
    bool operator<(const streamInfo& rightInfo) const
    {
        return basicOstream < rightInfo.basicOstream;
    }
    bool operator>(const streamInfo& rightInfo) const
    {
        return basicOstream > rightInfo.basicOstream;
    }
};

std::string substituteStringPriority(uint8_t priority)
{
    std::string tmp;
    switch (priority)
    {
        case 0:
            tmp = "TRACE";
            break;
        case 1:
            tmp = "DEBUG";
            break;
        case 2:
            tmp = "INFORMATION";
            break;
        case 3:
            tmp = "WARNING";
            break;
        case 4:
            tmp = "ERROR";
            break;
        case 5:
            tmp = "FATAL";
            break;
        default:
            tmp = "UNIDENTIFIED";
    }
    return tmp;
}

uint8_t replacePriorityNumber(const std::string& priority)
{
    if (priority == "TRACE")
        return 0;
    else if (priority == "DEBUG")
        return 1;
    else if (priority == "INFORMATION")
        return 2;
    else if (priority == "WARNING")
        return 3;
    else if (priority == "ERROR")
        return 4;
    else if (priority == "FATAL")
        return 5;

    return 255;
}

class Logger
{
private:
    static std::map<std::string, std::pair<std::ostream*, uint8_t>> ostreamMap;
    std::forward_list<std::pair<std::string, streamInfo>> chain;
public:
    Logger() = default;
    explicit Logger(std::forward_list<std::pair<std::string, streamInfo>> infoList) : chain(std::move(infoList))
    {
        for (auto &iter : ostreamMap)
            iter.second.second++;
    }
    ~Logger()
    {
        std::set<std::string> setStreams;
        for (const auto& iter : chain)
            setStreams.insert(iter.first);

        for (auto& iter : setStreams)
        {
            auto requiredItem = ostreamMap.find(iter);
            if (requiredItem != ostreamMap.end())
                requiredItem->second.second--;
            if (requiredItem->second.second == 0)
            {
                if (requiredItem->first != "stdout")
                    delete requiredItem->second.first;
                ostreamMap.erase(requiredItem->first);
            }
        }
    }
    void log(const std::string& event, uint8_t priority)
    {
        for (auto& iter : chain)
            if (iter.second.priority <= priority)
            {
                time_t seconds = time(nullptr);
                tm* timeInfo = localtime(&seconds);
                char* tmpTime = asctime(timeInfo);
                tmpTime[std::strlen(tmpTime) - 1] = '\0';
                *iter.second.basicOstream << "[" << tmpTime << "]" << "[" << substituteStringPriority(priority) <<
                                   "]" << ":" << event << std::endl;
            }
    }
    friend class LogBuilder;
};

std::map<std::string, std::pair<std::ostream*, uint8_t>> Logger::ostreamMap; /* Область темного колдунства */

std::ostream* flowDefinition(const std::string& string)
{
    std::ostream* fp = &std::cout;
    std::ofstream* fOut;
    if (string != "stdout")
    {
        fOut = new std::ofstream(string);
        if (not fOut->is_open())
            throw std::bad_alloc();
        return fOut;
    }
    return fp;
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

std::string checkPath(const std::string& streamName)
{
    if (streamName == "stdout")
        return streamName;

    std::vector<std::string> wordVector = split(streamName, "/");
    if (wordVector.size() == 1)
    {
        char PathName[PATH_MAX];
        getcwd(PathName, PATH_MAX);
        return std::string(PathName) + "/" + streamName;
    }
    else
        return streamName;
}

class LogBuilder
{
private:
    std::forward_list<std::pair<std::string, streamInfo>> infoList;
public:
    LogBuilder() = default;

    void addLogTarget(const std::string& streamName, uint8_t priority = 2)
    {
        // TODO: CHECK PATH
        std::string fullPath = checkPath(streamName);

        auto requiredElement = Logger::ostreamMap.find(fullPath);
        if (requiredElement == Logger::ostreamMap.end())
        {
            std::ostream* flow = flowDefinition(fullPath);
            Logger::ostreamMap.insert({fullPath, {flow, 0}});
            infoList.push_front({fullPath, streamInfo(flow, priority)});
        }
        else
        {
            for (const auto& iter : infoList)
                if (iter.second.basicOstream == requiredElement->second.first and iter.second.priority == priority)
                    throw std::invalid_argument("A thread with the given priority already exists!");

            infoList.push_front({fullPath, streamInfo(requiredElement->second.first, priority)});
        }
    }

    void addTargetFromJson(const std::string& fileName)
    {
        nlohmann::json jsonObject;
        std::fstream fileInput;
        fileInput.open(fileName);
        if (not fileInput.is_open())
            throw std::bad_alloc();
        fileInput >> jsonObject;
        std::string priority;
        std::string jsonStream;
        for (int i = 0; i < jsonObject["streams"].size(); i++)
        {
            jsonStream = jsonObject["streams"][i]["name"];
            priority = jsonObject["streams"][i]["severity"];
            this->addLogTarget(jsonStream, replacePriorityNumber(priority));
        }
    }

    void removeLogTarget(const std::string& streamName, uint8_t priority = 2)
    {
        auto requiredElement = Logger::ostreamMap.find(streamName);
        if (requiredElement == Logger::ostreamMap.end())
            throw std::invalid_argument("Element does not exist!");
        else
        {
            infoList.remove({streamName, streamInfo(requiredElement->second.first, priority)});
            if (requiredElement->second.second == 0)
            {
                if (requiredElement->first != "stdout")
                    delete requiredElement->second.first;
                Logger::ostreamMap.erase(streamName);
            }
            else
                throw std::invalid_argument("Stream in use!");
        }
    }

    Logger* createLogger()
    {
        auto* tmp = new Logger(infoList);
        return tmp;
    }

    ~LogBuilder()
    {
        for (auto iter : Logger::ostreamMap)
        {
            if (iter.first != "stdout")
            {
                iter.second.first->flush();
                delete iter.second.first;
            }
        }
    }
};

#endif //FUNDI_9_LOGGER_H
