cmake_minimum_required(VERSION 2.8)
project(acsflix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(prefix ${CMAKE_SOURCE_DIR})

find_package(ZMQ REQUIRED)

set(EXTERNAL_LIBS
        ${ZMQ_LIBRARIES})

include_directories(${ZMQ_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/jsmnutils)
include_directories(src)

set(SOURCE_FILES
        src/WorkerFlow.cpp
        src/WorkerStream.cpp
        src/SenderFlow.cpp
        src/SenderStream.cpp)

add_executable(worker cmd/worker.cpp ${SOURCE_FILES})
add_executable(sender cmd/sender.cpp ${SOURCE_FILES})
add_executable(jsmnutils_test src/test/jsmnutils_test.cpp)
add_executable(sender3F1S cmd/sender3F1S.cpp ${SOURCE_FILES})
add_executable(worker3F1S cmd/worker3F1S.cpp ${SOURCE_FILES})

add_library(jsmn src/jsmnutils/jsmn.c)
add_library(jsmnutils src/jsmnutils/jsmnutils.cpp)
target_link_libraries(jsmnutils jsmn)

target_link_libraries(worker ${EXTERNAL_LIBS})
target_link_libraries(sender ${EXTERNAL_LIBS})
target_link_libraries(jsmnutils_test jsmnutils)
target_link_libraries(sender3F1S jsmnutils ${EXTERNAL_LIBS})
target_link_libraries(worker3F1S jsmnutils ${EXTERNAL_LIBS})

install(FILES docs/input_test.json DESTINATION ${prefix}/test)
install(TARGETS worker sender DESTINATION ${prefix}/bin)
install(TARGETS jsmnutils_test sender3F1S worker3F1S
    DESTINATION ${prefix}/test)
