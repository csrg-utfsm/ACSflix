#include "WorkerFlow.h"

#include <zmq.h>
#include <iostream>

WorkerFlow::WorkerFlow(std::string connect, Callback * cb) : 
    m_context(zmq_ctx_new()),
    m_socket(zmq_socket(m_context, ZMQ_PULL)),
    m_cb(cb)
{
    // connect to the sender socket.
    int rc = zmq_connect(m_socket, connect.c_str());
    if (rc == -1) {
        throw zmq_strerror(zmq_errno());
    }

    // tell the callback that we are ready.
    m_cb->on_start(this);
}

WorkerFlow::~WorkerFlow()
{
    // safely close ZMQ entities.
    zmq_close(m_socket);
    zmq_ctx_destroy(m_context);
}

bool WorkerFlow::work()
{
    // receive a workload into the worker buffer.
    // NOTE: Here the size of the buffer is limited (subtracted one byte) in
    // order to allow space for the null terminating character.
    int size = zmq_recv(m_socket, m_buffer, sizeof(m_buffer) - 1, 0);
    if (size == -1) {
        throw zmq_strerror(zmq_errno());
    }

    // set the last byte to 0 to terminate the buffer correctly. This value
    // should be never seen by others.
    m_buffer[size] = 0;

    // tell the callback that there's workload to take.
    m_cb->on_workload(m_buffer, size);

    // TODO: call on_stop when detected.

    return true;
}
