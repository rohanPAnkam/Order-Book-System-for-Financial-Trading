#ifndef ORDER_H
#define ORDER_H

struct Order {
    int orderid;
    char side;  // 'B' for Buy, 'S' for Sell
    int quantity;
    double price;
    int timestamp;  // Used for time priority (lowest timestamp first)
    
    // Constructor
    Order(int id, char s, int qty, double p, int t);
};

#endif // ORDER_H