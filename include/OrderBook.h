#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "Order.h"
#include <vector>

class OrderBook {
public:
    OrderBook();
    void addOrder(int orderid, char side, int quantity, double price);
    void removeOrder(int orderid, char side);
    void modifyOrder(int orderid, char side, int quantity);
    void orderMatcher();
    void printOrderBook() const;

private:
    std::vector<Order> buyOrders;  // Buy orders sorted by price (descending) and time priority
    std::vector<Order> sellOrders; // Sell orders sorted by price (ascending) and time priority
    int timestampCounter;          // Counter to generate timestamp automatically
    static bool orderComparator(const Order& a, const Order& b);
};

#endif // ORDERBOOK_H