#include "MatchingStrategy.h"
#include <iostream>

void FIFOMatchingStrategy::match(Order& order, std::map<double, std::list<Order>>& oppositeBook, double& lastTradePrice, int& totalQuantityTraded) {
    auto it = oppositeBook.begin();
    while (order.quantity > 0 && it != oppositeBook.end()) {
        auto& orderList = it->second;

        while (!orderList.empty() && order.quantity > 0) {
            auto& oppositeOrder = orderList.front();
            int tradeQuantity = std::min(order.quantity, oppositeOrder.quantity);

            order.quantity -= tradeQuantity;
            oppositeOrder.quantity -= tradeQuantity;

            lastTradePrice = oppositeOrder.price;
            totalQuantityTraded += tradeQuantity;

            std::cout << "T," << tradeQuantity << "," << oppositeOrder.price << std::endl;

            if (oppositeOrder.quantity == 0) {
                orderList.pop_front();
            }
        }

        if (orderList.empty()) {
            it = oppositeBook.erase(it);
        } else {
            ++it;
        }
    }
}