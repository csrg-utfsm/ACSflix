#ifndef BDT_ENGINE_PROTOBUFSENDER_H
#define BDT_ENGINE_PROTOBUFSENDER_H

#include "czmq.h"
#include "google/protobuf/message_lite.h"
#include "BufferPool.h"

/**
 * TODO
 */
class ProtobufSender
{
private:
    zctx_t * context;

    void * router;

    BufferPool & pool;

public:
    ProtobufSender(std::string bind, BufferPool & pool);

    ~ProtobufSender();

    /**
     * Sends a ZMQ message as is to any available worker.
     *
     * @param msg message to send.
     */
    void send(zmq_msg_t * msg);

    /**
     * Sends a Google Protobuf message to any available worker.
     *
     * @param message google protobuf message.
     */
    void send(const google::protobuf::MessageLite & message);
};


#endif //BDT_ENGINE_PROTOBUFSENDER_H
