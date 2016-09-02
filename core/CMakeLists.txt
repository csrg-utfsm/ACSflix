cmake_minimum_required(VERSION 2.8)
project(publisher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lzmq -lczmq -lpthread")

set(SOURCE_FILES
        sources/emitter/Emitter.cpp
        sources/emitter/Emitter.hpp
        sources/receiver/Receiver.cpp
        sources/receiver/Receiver.hpp)

add_executable(emitter emitter.cpp ${SOURCE_FILES} sources/utils.h)
add_executable(receiver receiver.cpp ${SOURCE_FILES})
