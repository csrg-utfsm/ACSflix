cmake_minimum_required(VERSION 2.8)
project(acsflix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -g")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(ZMQ REQUIRED)

set(EXTERNAL_LIBS
        ${ZMQ_LIBRARIES})

include_directories(${ZMQ_INCLUDE_DIR})

include_directories(src)

set(SOURCE_FILES
        src/WorkerFlow.cpp
        src/WorkerStream.cpp
        src/SenderFlow.cpp
        src/SenderStream.cpp)

add_executable(worker cmd/worker.cpp ${SOURCE_FILES})
add_executable(sender cmd/sender.cpp ${SOURCE_FILES})

target_link_libraries(worker ${EXTERNAL_LIBS})
target_link_libraries(sender ${EXTERNAL_LIBS})
