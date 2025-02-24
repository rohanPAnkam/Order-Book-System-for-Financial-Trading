#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>

// Define the Order structure
struct Order {
    int orderid;
    char side;  // 'B' for Buy, 'S' for Sell
    int quantity;
    double price;
    int timestamp;  // Used for time priority (lowest timestamp first)
    
    // Constructor
    Order(int id, char s, int qty, double p, int t) : orderid(id), side(s), quantity(qty), price(p), timestamp(t) {}
};

// Comparator to sort orders first by price, then by time priority
bool orderComparator(const Order& a, const Order& b) {
    if (a.price == b.price) {
        return a.timestamp < b.timestamp;  // Time priority (oldest first)
    }
    return a.side == 'B' ? a.price > b.price : a.price < b.price;
}

// Define the OrderBook class
class OrderBook {
public:
    OrderBook() : timestampCounter(0) {}  // Initialize timestamp counter

    void addOrder(int orderid, char side, int quantity, double price) {
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

    void removeOrder(int orderid, char side) {
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

    void modifyOrder(int orderid, char side, int quantity) {
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

    void orderMatcher() {
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

                // Generate order-related messages (remove or modify orders)
                if (buyOrder.quantity == 0) {
                    std::cout << "Remove Buy Order: " << buyOrder.orderid << std::endl;
                }
                if (sellOrder.quantity == 0) {
                    std::cout << "Remove Sell Order: " << sellOrder.orderid << std::endl;
                }
                if (sellOrder.quantity > 0) {
                    std::cout << "Modify Sell Order: " << sellOrder.orderid << " Quantity: " << sellOrder.quantity << std::endl;
                }
                if (buyOrder.quantity > 0) {
                    std::cout << "Modify Buy Order: " << buyOrder.orderid << " Quantity: " << buyOrder.quantity << std::endl;
                }
            } else {
                break;  // No more trades possible
            }
        }
    }

    void printOrderBook() const {
        std::cout << "Sell Orders:" << std::endl;
        for (const auto& order : sellOrders) {
            std::cout << order.side << " " << order.quantity << " " << order.price << std::endl;
        }
        std::cout << "Buy Orders:" << std::endl;
        for (const auto& order : buyOrders) {
            std::cout << order.side << " " << order.quantity << " " << order.price << std::endl;
        }
    }

private:
    std::vector<Order> buyOrders;  // Buy orders sorted by price (descending) and time priority
    std::vector<Order> sellOrders; // Sell orders sorted by price (ascending) and time priority
    int timestampCounter;          // Counter to generate timestamp automatically
};

// Main function
int main() {
    OrderBook orderBook;

    // Adding orders
    orderBook.addOrder(1000000, 'S', 1, 1075);
    orderBook.addOrder(1000001, 'B', 9, 1000);
    orderBook.addOrder(1000002, 'B', 30, 975);
    orderBook.addOrder(1000003, 'S', 10, 1050);
    orderBook.addOrder(1000004, 'B', 10, 950);
    orderBook.addOrder(1000005, 'S', 2, 1025);
    orderBook.addOrder(1000006, 'B', 1, 1000);

    // Remove order 1000004
    orderBook.removeOrder(1000004, 'B');

    // Adding more orders
    orderBook.addOrder(1000007, 'S', 5, 1025);
    orderBook.addOrder(1000008, 'B', 3, 1050);

    // Perform trades
    orderBook.orderMatcher();

    // Remove orders
    orderBook.removeOrder(1000008, 'B');
    orderBook.removeOrder(1000005, 'S');

    // // Modify order 1000007
    orderBook.modifyOrder(1000007, 'S', 4);

    // Print the final order book state
    orderBook.printOrderBook();

    return 0;
}