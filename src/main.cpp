#include "FeedHandler.h"
#include <iostream>

int main() {
    FeedHandler handler;
    std::string line;
    while (std::getline(std::cin, line)) {
        handler.processMessage(line);
    }
    handler.printTotalQuantityTraded(std::cout);
    return 0;
}