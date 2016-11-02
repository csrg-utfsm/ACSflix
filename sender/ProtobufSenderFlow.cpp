#include <iostream>

#include "ProtobufSenderFlow.h"

ProtobufSenderFlow::ProtobufSenderFlow(const std::string & bind, int linger) :
        SenderFlow(bind, linger)
{}


void ProtobufSenderFlow::send(const google::protobuf::MessageLite & message)
{
#ifdef DEBUG
    std::cout << "Send invoked" << std::endl;
#endif

    ZMQBuffer * zmq_buffer = m_buffer_factory->get_zbuffer((size_t) message.ByteSize());

    // Serialize message to zmq_buffer
    message.SerializeToArray(zmq_buffer->buffer(), (int) zmq_buffer->size());

    assert(message.IsInitialized());

    // Zero copy pool zmq_buffer
    zmq_msg_t msg;
    zmq_buffer->init_data(&msg);

    SenderFlow::send(&msg);

    delete zmq_buffer;
}
