#include "SenderFlow.h"

#include <zmq.h>
#include <iostream>
#include <cstring>
#include <cassert>

SenderFlow::SenderFlow(std::string bind) :
    m_context(zmq_ctx_new()),
    m_stream_socket(zmq_socket(m_context, ZMQ_PUSH)),
    m_notif_socket(zmq_socket(m_context, ZMQ_PUB))
{
    // bind the port for the stream endpoint
    int rc = zmq_bind(m_stream_socket, bind.c_str());
    if (rc == -1) {
        throw std::string(strerror(errno));
    }
    // bind the port for the notification channel endpoint
    rc = zmq_bind(m_notif_socket, "tcp://*:9992");
    if (rc == -1) {
        throw std::string(strerror(errno));
    }
    int linger = -1;
    zmq_setsockopt(m_stream_socket, ZMQ_LINGER, &linger, sizeof(linger));
    zmq_setsockopt(m_notif_socket, ZMQ_LINGER, &linger, sizeof(linger));
}

SenderFlow::~SenderFlow()
{
    // Send graceful end of transmission notification
    end_transmission();
    // safely close all ZMQ entities.
    zmq_close(m_stream_socket);
    zmq_close(m_notif_socket);
    zmq_ctx_destroy(m_context);
}

void SenderFlow::send(char * buffer, size_t size)
{
    // send the workload.
    while (zmq_send(m_stream_socket, buffer, size, 0) == -1 && errno == EINTR) {
        std::cout << "zmq_send: retrying" << std::endl;
    }
    /* FIXME: Properly handle this exception */
}

void SenderFlow::end_transmission()
{
    char buffer[] = "__EndOfTransmission__";
    zmq_send(m_notif_socket, buffer, strlen(buffer), 0);
}