#ifndef BDT_ENGINE_PROTOBUFSENDER_H
#define BDT_ENGINE_PROTOBUFSENDER_H

#include "czmq.h"
#include "google/protobuf/message_lite.h"
#include "BufferPool.h"
#include "SenderFlow.h"

/**
 * TODO
 */
class ProtobufSenderFlow : public SenderFlow
{
public:
    ProtobufSenderFlow(const std::string & bind, int linger);

    /**
     * Sends a Google Protobuf message to any available worker.
     *
     * @param message google protobuf message.
     */
    void send(const google::protobuf::MessageLite & message);
};


#endif //BDT_ENGINE_PROTOBUFSENDER_H
