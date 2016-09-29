cmake_minimum_required(VERSION 2.8)
project(publisher)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(ZMQ REQUIRED)
find_package(czmq REQUIRED)
find_package(Protobuf REQUIRED)

set(LIBS
        ${ZMQ_LIBRARIES}
        ${CZMQ_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        )

include_directories(${ZMQ_INCLUDE_DIR})
include_directories(${CZMQ_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(proto)

#PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS proto/Dummy.proto)

#include_directories(/usr/local/include) # macOS does not have /usr/include

set(SOURCE_FILES
        core/sources/util/utils.cpp
        core/sources/Sender.cpp
        core/sources/Sender.h
        core/sources/Worker.cpp
        core/sources/Worker.h
        proto/Dummy.pb.cc
        proto/Dummy.pb.h
        core/sources/PBSender.cpp core/sources/PBSender.h core/sources/StreamSender.cc core/sources/StreamSender.h core/sources/ZMQBuffer.h)

set(BDR_LIB_FILES
        core/sources/interface/BulkDataZMQFlow.cc
        core/sources/interface/BulkDataZMQSenderFlow.cc
        core/sources/interface/BulkDataZMQSenderFlow.h
        core/sources/util/Buffer.cc
        core/sources/util/Buffer.h
        core/sources/util/BufferPool.cc
        core/sources/util/BufferPool.h
        core/sources/util/BufferPoolElement.cc
        core/sources/util/BufferPoolElement.h
        core/sources/util/ScopedRef.hh
        core/sources/SenderExtension.cc
        core/sources/SenderExtension.h
        core/sources/ZMQBufferFactory.h
        core/sources/ZMQHeapBufferFactory.cc
        core/sources/ZMQHeapBufferFactory.h
        core/sources/ZMQHeapBuffer.cc
        core/sources/ZMQHeapBuffer.h
        core/sources/ZMQPooledBufferFactory.cc
        core/sources/ZMQPooledBufferFactory.h
        core/sources/ZMQPooledBuffer.cc
        core/sources/ZMQPooledBuffer.h
        core/sources/ZMQBuffer.cc)

add_library(BulkDataReloaded ${BDR_LIB_FILES})

add_executable(sender core/sources/test_sender.cpp ${SOURCE_FILES})
add_executable(worker core/sources/test_worker.cpp ${SOURCE_FILES})

target_link_libraries(sender ${LIBS} BulkDataReloaded)
target_link_libraries(worker ${LIBS} BulkDataReloaded)