#include "WorkerFlow.hpp"

#include <zmq.h>
#include <iostream>

WorkerFlow::WorkerFlow(std::string connect, Callback * cb) : 
    m_context(zmq_ctx_new()),
    m_socket(zmq_socket(m_context, ZMQ_PULL)),
    m_cb(cb)
{
    int rc = zmq_connect(m_socket, connect.c_str());
    if (rc == -1) {
        throw zmq_strerror(zmq_errno());
    }

    m_cb->on_start(this);
}

WorkerFlow::~WorkerFlow()
{
    zmq_close(m_socket);
    zmq_ctx_destroy(m_context);
}

bool WorkerFlow::work()
{
    int size = zmq_recv(m_socket, m_buffer, sizeof(m_buffer) - 1, 0);
    if (size == -1) {
        throw zmq_strerror(zmq_errno());
    }

    m_buffer[size] = 0;

    m_cb->on_workload(m_buffer, size);

    // TODO: call on_stop when detected.

    return true;
}
