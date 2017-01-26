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
    int rc = zmq_send(m_stream_socket, buffer, size, 0);
    if (rc == -1) {
        throw zmq_strerror(zmq_errno());
    }
}

void SenderFlow::end_transmission()
{
    char buffer[] = "__EndOfTransmission__";
    zmq_send(m_notif_socket, buffer, strlen(buffer), 0);
}