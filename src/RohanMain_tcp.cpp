#include "RohanOrderBook_tcp.h"

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

    // Modify order 1000007
    orderBook.modifyOrder(1000007, 'S', 4);

    // Print the final order book state
    orderBook.printOrderBook();

    return 0;
}