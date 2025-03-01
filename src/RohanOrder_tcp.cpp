#include "RohanOrder_tcp.h"

Order::Order(int id, char s, int qty, double p, int t)
    : orderid(id), side(s), quantity(qty), price(p), timestamp(t) {}