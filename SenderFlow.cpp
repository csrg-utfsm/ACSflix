#include "SenderFlow.hpp"

#include <zmq.h>
#include <iostream>

SenderFlow::SenderFlow(std::string bind) :
    m_context(zmq_ctx_new()),
    m_socket(zmq_socket(m_context, ZMQ_PUSH))
{
    int rc = zmq_bind(m_socket, bind.c_str());
    if (rc == -1) {
        throw zmq_strerror(zmq_errno());
    }
}

SenderFlow::~SenderFlow()
{
    zmq_close(m_socket);
    zmq_ctx_destroy(m_context);
}

void SenderFlow::send(char * buffer, size_t size)
{
    // TODO: should check for errors.
    int rc = zmq_send(m_socket, buffer, size, 0);
    if (rc == -1) {
        throw zmq_strerror(zmq_errno());
    }
}
