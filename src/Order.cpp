#include "Order.h"

Order::Order(const std::string& a, int id, char s, int q, double p)
    : action(a), orderId(id), side(s), quantity(q), price(p) {}
