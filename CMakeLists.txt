cmake_minimum_required(VERSION 3.14)
project(FeedHandler CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include headers
include_directories(include)

# Add executable
add_executable(feed_handler src/main.cpp src/FeedHandler.cpp src/MessageFactory.cpp src/MatchingStrategy.cpp)

# Enable optimizations for release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

# Add warnings for debugging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# Install target (optional)
install(TARGETS feed_handler DESTINATION bin)