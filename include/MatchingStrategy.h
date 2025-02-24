#ifndef MATCHINGSTRATEGY_H
#define MATCHINGSTRATEGY_H

#include "Order.h"
#include <map>
#include <list>

class MatchingStrategy {
public:
    virtual void match(Order& order, std::map<double, std::list<Order>>& oppositeBook, double& lastTradePrice, int& totalQuantityTraded) = 0;
    virtual ~MatchingStrategy() = default;
};

class FIFOMatchingStrategy : public MatchingStrategy {
public:
    void match(Order& order, std::map<double, std::list<Order>>& oppositeBook, double& lastTradePrice, int& totalQuantityTraded) override;
};

#endif // MATCHINGSTRATEGY_H