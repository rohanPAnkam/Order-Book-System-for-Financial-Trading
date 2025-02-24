#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include "Order.h"
#include <string>

class MessageFactory {
public:
    static Order createOrder(const std::string& line);
};

#endif // MESSAGEFACTORY_H