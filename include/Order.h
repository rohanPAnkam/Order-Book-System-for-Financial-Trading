#ifndef ORDER_H
#define ORDER_H

#include <string>

struct Order {
    std::string action;
    int orderId;
    char side;
    int quantity;
    double price;

    Order(std::string a, int id, char s, int q, double p)
        : action(std::move(a)), orderId(id), side(s), quantity(q), price(p) {}
};

#endif // ORDER_H