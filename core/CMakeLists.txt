cmake_minimum_required(VERSION 2.8)
project(publisher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lzmq -lczmq -lpthread")

set(SOURCE_FILES
        sources/publisher/Publisher.cpp
        sources/publisher/Publisher.hpp
        sources/subscriber/Subscriber.cpp
        sources/subscriber/Subscriber.hpp)


add_executable(publisher pub.cpp ${SOURCE_FILES})
add_executable(subscriber sub.cpp ${SOURCE_FILES})
