//
// Created by ayttekao on 4/17/21.
//

#ifndef FUNDI_7_STRATEGY_H
#define FUNDI_7_STRATEGY_H

#include <ctime>
#include "PopulationCensus.h"

template <typename T>
class Strategy{
public:
    virtual ~Strategy() = default;
    virtual int compare(const T& left, const T& right) const = 0;
};

class StrategyEnumerationAreaNumber : public Strategy<std::shared_ptr<PopulationCensus>>
{
    int compare(const std::shared_ptr<PopulationCensus>& left, const std::shared_ptr<PopulationCensus>& right) const override
    {
        if (left->enumerationAreaNumber == right->enumerationAreaNumber)
            return 0;
        else if (left->enumerationAreaNumber < right->enumerationAreaNumber)
            return -1;
        return 1;
    }
};

class StrategyFullName : public Strategy<std::shared_ptr<PopulationCensus>>
{
    int compare(const std::shared_ptr<PopulationCensus>& left, const std::shared_ptr<PopulationCensus>& right) const override
    {
        int comparisonResult = left->fullName.compare(right->fullName);
        if (comparisonResult > 0)
            return 1;
        else if (comparisonResult < 0)
            return -1;
        return 0;
    }
};

class StrategyPlaceOfBirth : public Strategy<std::shared_ptr<PopulationCensus>>
{
    int compare(const std::shared_ptr<PopulationCensus>& left, const std::shared_ptr<PopulationCensus>& right) const override
    {
        int comparisonResult = left->placeOfBirth.compare(right->placeOfBirth);
        if (comparisonResult > 0)
            return 1;
        else if (comparisonResult < 0)
            return -1;
        return 0;
    }
};

class StrategyCitizenship : public Strategy<std::shared_ptr<PopulationCensus>>
{
    int compare(const std::shared_ptr<PopulationCensus>& left, const std::shared_ptr<PopulationCensus>& right) const override
    {
        int comparisonResult = strcmp(left->citizenship.c_str(), right->citizenship.c_str());
        if (comparisonResult > 0)
            return 1;
        else if (comparisonResult < 0)
            return -1;
        return 0;
    }
};

class StrategyFormNumber : public Strategy<std::shared_ptr<PopulationCensus>>
{
    int compare(const std::shared_ptr<PopulationCensus>& left, const std::shared_ptr<PopulationCensus>& right) const override
    {
        if (left->formNumber == right->formNumber)
            return 0;
        else if (left->formNumber < right->formNumber)
            return -1;
        return 1;
    }
};


#endif //FUNDI_7_STRATEGY_H
