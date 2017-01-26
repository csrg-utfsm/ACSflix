#include "WorkerFlow.h"

#include <zmq.h>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <cassert>

WorkerFlow::WorkerFlow(std::string connect, Callback * cb) : 
    m_context(zmq_ctx_new()),
    m_stream_socket(zmq_socket(m_context, ZMQ_PULL)),
    m_notif_socket(zmq_socket(m_context, ZMQ_SUB)),
    m_cb(cb)
{
    // connect to the sender socket.
    int rc = zmq_connect(m_stream_socket, connect.c_str());
    assert(zmq_connect(m_notif_socket, "tcp://localhost:9992") != -1);
    assert(zmq_setsockopt(m_notif_socket, ZMQ_SUBSCRIBE, "", 0) != -1);
    if (rc == -1) {
        throw zmq_strerror(zmq_errno());
    }
}

WorkerFlow::~WorkerFlow()
{
    // safely close ZMQ entities.
    zmq_close(m_stream_socket);
    zmq_ctx_destroy(m_context);
}

void WorkerFlow::ready()
{
    // tell the callback that we are ready.
    m_cb->on_start(this);
}

bool WorkerFlow::recv_stream()
{
    // receive a workload into the worker buffer.
    // NOTE: Here the size of the buffer is limited (subtracted one byte) in
    // order to allow space for the null terminating character.
    int size = zmq_recv(m_stream_socket, m_buffer, sizeof(m_buffer), 0);
    if (size == -1) {
        throw std::string(strerror(errno));
    }

    // tell the callback that there's workload to take.
    m_cb->on_workload(m_buffer, size);

    // Keep receiving
    return true;
}

bool WorkerFlow::recv_notif()
{
    // Receive a message from the notification channel
    int size = zmq_recv(m_notif_socket, m_buffer, sizeof(m_buffer) - 1, 0);
    if (size == -1) {
        throw std::string(strerror(errno));
    }

    // set the last byte to 0 to terminate the buffer correctly. This value
    // should be never seen by others.
    m_buffer[size] = 0;

    // For now, we only support __EndOfTransmission__ message
    // This must be extendable and standarized!
    if (strcmp(m_buffer, "__EndOfTransmission__") == 0) {
        return false;
    }

    // Other message is not considered
    return true;
}

bool WorkerFlow::work()
{
    // zmq_pollitem_t.socket  = zmq obscure socket
    // zmq_pollitem_t.fd      = socket fd
    // zmq_pollitem_t.events  = what to poll
    // zmq_pollitem_t.revents = what was catched
    zmq_pollitem_t items[] = {
        { m_stream_socket, 0, ZMQ_POLLIN, 0 },
        { m_notif_socket,  0, ZMQ_POLLIN, 0 }
    };
    // Wait until there is data to read in either channel
    if (zmq_poll(items, 2, -1) == -1) {
        std::string(strerror(errno));
    }

    // Multiplex channels
    // If stream socket has data to read
    if (items[0].revents & ZMQ_POLLIN) {
        return recv_stream();
    }
    // If notification channel has data to read
    if (items[1].revents & ZMQ_POLLIN) {
        return recv_notif();
    }
    
    // Unreachable
    return false;
}
