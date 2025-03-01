#include "RohanOrderBook_tcp.h"
#include <iostream>
#include <algorithm>

// Comparator to sort orders first by price, then by time priority
bool OrderBook::orderComparator(const Order& a, const Order& b) {
    if (a.price == b.price) {
        return a.timestamp < b.timestamp;  // Time priority (oldest first)
    }
    return a.side == 'B' ? a.price > b.price : a.price < b.price;
}

OrderBook::OrderBook() : timestampCounter(0) {}

void OrderBook::addOrder(int orderid, char side, int quantity, double price) {
    int currentTimestamp = timestampCounter++;  // Use the counter as timestamp
    Order order(orderid, side, quantity, price, currentTimestamp);
    if (side == 'B') {
        buyOrders.push_back(order);
        std::sort(buyOrders.begin(), buyOrders.end(), orderComparator);
    } else {
        sellOrders.push_back(order);
        std::sort(sellOrders.begin(), sellOrders.end(), orderComparator);
    }
    orderMatcher();  // Call orderMatcher after adding an order
}

void OrderBook::removeOrder(int orderid, char side) {
    if (side == 'B') {
        for (auto it = buyOrders.begin(); it != buyOrders.end(); ++it) {
            if (it->orderid == orderid) {
                buyOrders.erase(it);
                break;
            }
        }
    } else {
        for (auto it = sellOrders.begin(); it != sellOrders.end(); ++it) {
            if (it->orderid == orderid) {
                sellOrders.erase(it);
                break;
            }
        }
    }
    orderMatcher();  // Call orderMatcher after removing an order
}

void OrderBook::modifyOrder(int orderid, char side, int quantity) {
    if (side == 'B') {
        for (auto it = buyOrders.begin(); it != buyOrders.end(); ++it) {
            if (it->orderid == orderid) {
                it->quantity = quantity;
                std::sort(buyOrders.begin(), buyOrders.end(), orderComparator);
                break;
            }
        }
    } else {
        for (auto it = sellOrders.begin(); it != sellOrders.end(); ++it) {
            if (it->orderid == orderid) {
                it->quantity = quantity;
                std::sort(sellOrders.begin(), sellOrders.end(), orderComparator);
                break;
            }
        }
    }
    orderMatcher();  // Call orderMatcher after modifying an order
}

void OrderBook::orderMatcher() {
    // Match buy and sell orders based on price and time priority
    while (!buyOrders.empty() && !sellOrders.empty()) {
        Order& buyOrder = buyOrders.front();
        Order& sellOrder = sellOrders.front();

        // Match if the buy price is greater than or equal to the sell price
        if (buyOrder.price >= sellOrder.price) {
            int tradeQuantity = std::min(buyOrder.quantity, sellOrder.quantity);
            std::cout << "T," << tradeQuantity << "," << sellOrder.price << std::endl;

            // Update the quantities after the trade
            buyOrder.quantity -= tradeQuantity;
            sellOrder.quantity -= tradeQuantity;

            // Remove orders that are completely filled
            if (buyOrder.quantity == 0) {
                buyOrders.erase(buyOrders.begin());
            }
            if (sellOrder.quantity == 0) {
                sellOrders.erase(sellOrders.begin());
            }
        } else {
            break;  // No more trades possible
        }
    }
}

void OrderBook::printOrderBook() const {
    std::cout << "Sell Orders:" << std::endl;
    for (const auto& order : sellOrders) {
        std::cout << order.side << " " << order.quantity << " " << order.price << std::endl;
    }
    std::cout << "Buy Orders:" << std::endl;
    for (const auto& order : buyOrders) {
        std::cout << order.side << " " << order.quantity << " " << order.price << std::endl;
    }
}