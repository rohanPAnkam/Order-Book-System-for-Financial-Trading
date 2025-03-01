cmake_minimum_required(VERSION 3.10)

# Set project name
project(OrderBookSystem)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Specify the include directory
include_directories(include)

# Add source files
set(SOURCES
    src/RohanMain_tcp.cpp
    src/RohanOrderBook_tcp.cpp
    src/RohanOrder_tcp.cpp
)

# Create the executable
add_executable(OrderBookSystem ${SOURCES})