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

    bool stopped;

    int stop_timeout;

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

    /**
     * Stops sender and all workers, this is a blocking operation.
     */
    void stop();

    /**
     * Sets the amount of time to wait until all workers are stopped.
     * Refeer to the StopMechanics document to read more about this.
     *
     * @param stop_timeout time until all workers are considered closed.
     */
    void set_stop_timeout(int stop_timeout);
};


#endif //BDT_ENGINE_PROTOBUFSENDER_H
