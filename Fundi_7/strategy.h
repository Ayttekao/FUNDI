//
// Created by ayttekao on 4/17/21.
//

#ifndef FUNDI_7_STRATEGY_H
#define FUNDI_7_STRATEGY_H

#include <ctime>


template <typename T>
class Strategy{
public:
    virtual ~Strategy() = default;
    virtual int compare(T left, T right) const = 0;
};

class StrategyInt : public Strategy<int>{
    int compare(int left, int right) const override {
        if (left == right)
            return 0;
        else if (left < right)
            return -1;
        return 1;
    }
};


#endif //FUNDI_7_STRATEGY_H
