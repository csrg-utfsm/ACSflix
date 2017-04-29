#include "SenderFlow.h"

#include <zmq.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>

SenderFlow::SenderFlow(std::string bind, int port) :
    m_context(zmq_ctx_new()),
    m_stream_socket(zmq_socket(m_context, ZMQ_PUSH)),
    m_notif_socket(zmq_socket(m_context, ZMQ_PUB))
{
    // prepare full address
    std::stringstream stream_addr;
    stream_addr << bind << ":" << port;
    std::stringstream notf_addr;
    notf_addr << bind << ":" << (port + 1);
    // bind the port for the stream endpoint
    int rc = zmq_bind(m_stream_socket, stream_addr.str().c_str());
    if (rc == -1) {
        throw SenderFlowEx(strerror(errno));
    }
    // bind the port for the notification channel endpoint
    rc = zmq_bind(m_notif_socket, notf_addr.str().c_str());
    if (rc == -1) {
        throw SenderFlowEx(strerror(errno));
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
    zmq_ctx_term(m_context);
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
    char buffer[] = "#\\";
    zmq_send(m_notif_socket, buffer, strlen(buffer), 0);
}

void SenderFlow::set_name(std::string name)
{
    m_name = name;
}

std::string SenderFlow::name() const
{
    return m_name;
}
