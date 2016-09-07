cmake_minimum_required(VERSION 2.8)
project(publisher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lzmq -lczmq -lpthread")

set(SOURCE_FILES
        sources/emitter/Emitter.cpp
        sources/receiver/Receiver.cpp
        sources/util/utils.cpp
        sources/util/ProgressBar.cpp)

add_executable(emitter emitter.cpp ${SOURCE_FILES})
add_executable(receiver receiver.cpp ${SOURCE_FILES})
