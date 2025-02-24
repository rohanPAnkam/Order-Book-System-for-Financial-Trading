#include "MessageFactory.h"
#include <sstream>

Order MessageFactory::createOrder(const std::string& line) {
    std::istringstream iss(line);
    std::string action;
    int orderId;
    char side;
    int quantity;
    double price;

    iss >> action >> orderId >> side >> quantity >> price;
    return Order(action, orderId, side, quantity, price);
}