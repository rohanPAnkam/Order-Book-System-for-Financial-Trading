#ifndef FEEDHANDLER_H
#define FEEDHANDLER_H

#include "Order.h"
#include "MessageFactory.h"
#include "MatchingStrategy.h"
#include <map>
#include <list>
#include <unordered_map>
#include <memory>

class FeedHandler {
private:
    std::map<double, std::list<Order>> buyOrders;
    std::map<double, std::list<Order>> sellOrders;
    std::unordered_map<int, std::pair<double, std::list<Order>::iterator>> orderLookup;
    double lastTradePrice = 0.0;
    int totalQuantityTraded = 0;
    // strategy.match(order, oppositeBook, lastTradePrice, totalQuantityTraded);;

    std::unique_ptr<MatchingStrategy> strategy;

    void addOrder(const Order& order);
    void removeOrder(int orderId);
    void modifyOrder(int orderId, int newQuantity);

public:
    FeedHandler();
    void processMessage(const std::string& line);
    void printCurrentOrderBook(std::ostream& os) const;
    void printMidQuote(std::ostream& os) const;
    void printTotalQuantityTraded(std::ostream& os) const;
};

#endif // FEEDHANDLER_H