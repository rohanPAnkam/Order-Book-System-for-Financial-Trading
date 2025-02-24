cmake_minimum_required(VERSION 3.10)

# Set project name
project(OrderBookSystem)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Specify the include directory
include_directories(include)

# Add source files
set(SOURCES
    src/main.cpp
    src/OrderBook.cpp
    src/Order.cpp
)

# Create the executable
add_executable(OrderBookSystem ${SOURCES})