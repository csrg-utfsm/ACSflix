#include <iostream>
#include "ProtobufSender.h"


void on_buffer_release(void * data, void * hint)
{
    BufferPoolElement * element = static_cast<BufferPoolElement*>(hint);
    assert(element->get_buffer().data() == data);
    element->release(); // Release buffer to be used in cache
}


ProtobufSender::ProtobufSender(std::string bind, BufferPool & pool, int linger) :
        context(zctx_new()),
        router(zsocket_new(context, ZMQ_ROUTER)),
        pool(pool),
        stopped(false),
        stop_timeout(1000)
{
    zsocket_bind(router, bind.c_str());

    // infinite wait before shutting down.
    // TODO: consider a timeout.
    zctx_set_linger(context, linger);
}


ProtobufSender::~ProtobufSender()
{
    zctx_destroy(&context);
}


void ProtobufSender::send(zmq_msg_t * msg)
{
#ifdef DEBUG
    std::cout << "Waiting for worker..." << std::endl;
#endif

    char * identity = zstr_recv(router);

#ifdef DEBUG
    std::cout << "Sending " << zmq_msg_size(msg)
              << " bytes to " << identity
              << std::endl;
#endif

    // ignore content.
    zstr_recv(router);

    // send message with an identity frame and content frame.
    zstr_sendm(router, identity);
    zmq_msg_send(msg, router, 0);
}


void ProtobufSender::send(const google::protobuf::MessageLite & message)
{
    assert(!stopped);

#ifdef DEBUG
    std::cout << "Send invoked" << std::endl;
#endif

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


void ProtobufSender::stop()
{
#ifdef DEBUG
    std::cout << "Stop invoked" << std::endl;
#endif

    stopped = true;

    int timeout = 1000;
    zmq_setsockopt(router, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));

    while (1) {
        char * identity = zstr_recv(router);

        if (identity == NULL) {
            break;
        }

        zstr_sendm(router, identity);
        zstr_send(router, "");

#ifdef DEBUG
        std::cout << "Stopped a worker" << std::endl;
#endif
    }

#ifdef DEBUG
    std::cout << "Done" << std::endl;
#endif
}

void ProtobufSender::set_stop_timeout(int stop_timeout)
{
    this->stop_timeout = stop_timeout;
}
