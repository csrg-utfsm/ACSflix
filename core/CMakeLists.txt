cmake_minimum_required(VERSION 2.8)
project(publisher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lzmq -lczmq -lpthread")

set(SOURCE_FILES
        sources/util/utils.cpp
        sources/Sender.cpp
        sources/Sender.h
        sources/Worker.cpp
        sources/Worker.h
        )

add_executable(sender sources/test_sender.cpp ${SOURCE_FILES})
add_executable(worker sources/test_worker.cpp ${SOURCE_FILES})
