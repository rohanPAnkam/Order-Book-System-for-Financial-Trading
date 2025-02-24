#include "FeedHandler.h"
#include <iomanip>
#include <limits>
#include<iostream>

FeedHandler::FeedHandler()
    : lastTradePrice(0.0), totalQuantityTraded(0), strategy(std::make_unique<FIFOMatchingStrategy>()) {}

void FeedHandler::addOrder(const Order& order) {
    auto& orderBook = (order.side == 'B') ? buyOrders : sellOrders;

    // Find and erase the existing order by matching orderId
    auto it = std::find_if(orderBook[order.price].begin(), orderBook[order.price].end(),
                           [&](const Order& o) { return o.orderId == order.orderId; });
    if (it != orderBook[order.price].end()) {
        orderBook[order.price].erase(it);
    }

    // Update the order in the book
    orderBook[order.price].push_back(order);

    // Update the orderLookup with the new iterator
    orderLookup[order.orderId] = {order.price, std::prev(orderBook[order.price].end())};
}

void FeedHandler::removeOrder(int orderId) {
    auto it = orderLookup.find(orderId);
    if (it != orderLookup.end()) {
        auto orderIt = it->second;
        auto& orderBook = (orderIt.second->side == 'B') ? buyOrders : sellOrders;
        orderBook[orderIt.first].erase(orderIt.second);
        orderLookup.erase(it);
    }
}

void FeedHandler::modifyOrder(int orderId, int newPrice) {
    // Step 1: Locate the order in the orderLookup map
    auto it = orderLookup.find(orderId);
    if (it == orderLookup.end()) {
        // Order not found, log an error or handle appropriately
        std::cout << "Error: Order ID " << orderId << " not found.\n";
        return;
    }

    // Step 2: Extract the order details
    auto &[oldPrice, orderIt] = it->second;
    Order &order = *orderIt;

    // Step 3: Check if the price has changed
    if (newPrice == oldPrice) {
        // No price change, only update quantity (if needed)
        // For now, assume quantity remains the same
        return;
    }

    // Step 4: Remove the order from its current price level
    auto &oldOrderBook = (order.side == 'B') ? buyOrders : sellOrders;
    auto &oldOrderQueue = oldOrderBook[oldPrice];
    oldOrderQueue.erase(orderIt);

    // Step 5: If the price level is now empty, remove it from the order book
    if (oldOrderQueue.empty()) {
        oldOrderBook.erase(oldPrice);
    }

    // Step 6: Update the order's price
    order.price = newPrice;

    // Step 7: Reinsert the order into the new price level
    auto &newOrderBook = (order.side == 'B') ? buyOrders : sellOrders;
    auto &newOrderQueue = newOrderBook[newPrice];
    newOrderQueue.push_back(order);

    // Step 8: Update the orderLookup map with the new iterator
    orderLookup[orderId] = {newPrice, --newOrderQueue.end()};
}

void FeedHandler::processMessage(const std::string& line) {
    Order order = MessageFactory::createOrder(line);
    if (order.action == "A") {
        addOrder(order);
    } else if (order.action == "M") {
        modifyOrder(order.orderId, order.quantity);
    } else if (order.action == "X") {
        removeOrder(order.orderId);
    }

    if (order.side == 'B') {
        strategy->match(order, sellOrders, lastTradePrice, totalQuantityTraded);
    } else {
        strategy->match(order, buyOrders, lastTradePrice, totalQuantityTraded);
    }
}

void FeedHandler::printTotalQuantityTraded(std::ostream& os) const {
    os << totalQuantityTraded << "@" << lastTradePrice << "\n";
}
