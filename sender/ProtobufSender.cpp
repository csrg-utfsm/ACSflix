#include <iostream>
#include "ProtobufSender.h"


void on_buffer_release(void * data, void * hint)
{
    BufferPoolElement * element = static_cast<BufferPoolElement*>(hint);
    assert(element->get_buffer().data() == data);
    element->release(); // Release buffer to be used in cache
}


ProtobufSender::ProtobufSender(std::string bind, BufferPool & pool) :
        context(zctx_new()),
        router(zsocket_new(context, ZMQ_ROUTER)),
        pool(pool)
{
    zsocket_bind(router, bind.c_str());

    // infinite wait before shutting down.
    // TODO: consider a timeout.
    zctx_set_linger(context, -1);
}

ProtobufSender::~ProtobufSender()
{
    zctx_destroy(&context);
}


void ProtobufSender::send(zmq_msg_t * msg)
{
    std::cout << "Waiting for worker..." << std::endl;

    char * identity = zstr_recv(router);

    std::cout << "Sending " << zmq_msg_size(msg)
              << " bytes to " << identity
              << std::endl;

    // ignore content.
    zstr_recv(router);

    // send message with an identity frame and content frame.
    zstr_sendm(router, identity);
    zmq_msg_send(msg, router, 0);
}

void ProtobufSender::send(const google::protobuf::MessageLite & message)
{
    std::cout << "Send invoked" << std::endl;

    // Get buffer from pool
    BufferPoolElement * element =
            pool.get_and_retain((size_t) message.ByteSize());

    // Serialize message to buffer
    message.SerializeToArray(element->get_buffer().data(),
                             (int) element->get_buffer().length());

    assert(message.IsInitialized());

    // Zero copy pool buffer
    zmq_msg_t msg;
    zmq_msg_init_data(&msg,
                      element->get_buffer().data(),
                      element->get_buffer().length(),
                      on_buffer_release,
                      element);

    send(&msg);
}
