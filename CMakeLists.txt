cmake_minimum_required(VERSION 2.8)
project(bdt-engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(ZMQ REQUIRED)
find_package(czmq REQUIRED)
find_package(Protobuf REQUIRED)

set(EXTERNAL_LIBS
        ${ZMQ_LIBRARIES}
        ${CZMQ_LIBRARIES}
        ${PROTOBUF_LIBRARIES})

include_directories(${ZMQ_INCLUDE_DIR})
include_directories(${CZMQ_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})

include_directories(worker)
include_directories(sender)
include_directories(bufpool)
include_directories(proto)
include_directories(utils)

set(SOURCE_FILES
        sender/BytesSenderFlow.cpp
        sender/ProtobufSenderFlow.cpp
        worker/ProtobufWorker.cpp
        bufpool/BufferPool.cpp
        bufpool/BufferPoolElement.cpp
        bufpool/ZMQBuffer.cpp
        bufpool/ZMQHeapBuffer.cpp
        bufpool/ZMQHeapBufferFactory.cpp
        bufpool/ZMQPooledBuffer.cpp
        bufpool/ZMQPooledBufferFactory.cpp
        bufpool/Buffer.cpp
        sender/SenderStream.cpp
        sender/SenderFlow.cpp
        proto/BdBlock.pb.cc
        worker/WorkerFlow.cpp
        worker/WorkerStream.cpp)

add_executable(sender tests/sender_stream_binary.cpp ${SOURCE_FILES})
add_executable(worker tests/worker_binary.cpp ${SOURCE_FILES})

target_link_libraries(sender ${EXTERNAL_LIBS})
target_link_libraries(worker ${EXTERNAL_LIBS})
