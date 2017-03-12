#include "WorkerFlow.h"

#include <zmq.h>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <cassert>

WorkerFlow::WorkerFlow(std::string connect, size_t buffsize) : 
    m_context(zmq_ctx_new()),
    m_stream_socket(zmq_socket(m_context, ZMQ_PULL)),
    m_notif_socket(zmq_socket(m_context, ZMQ_SUB)),
    m_cb(NULL),
    m_buffer(new char[(buffsize) ? buffsize : DEFAULT_BUFFER_SIZE]),
    m_buffsize((buffsize) ? buffsize : DEFAULT_BUFFER_SIZE)
{
    // connect to the stream endpoint
    int rc = zmq_connect(m_stream_socket, connect.c_str());
    if (rc == -1) {
        throw std::string(strerror(errno));
    }
    // connect to to the notification channel endpoint
    rc = zmq_connect(m_notif_socket, "tcp://localhost:9992");
    if (rc == -1) {
        throw std::string(strerror(errno));
    }
    // subscribe to default topic
    zmq_setsockopt(m_notif_socket, ZMQ_SUBSCRIBE, "", 0);
    if (rc == -1) {
        throw std::string(strerror(errno));
    }
}

WorkerFlow::~WorkerFlow()
{
    // safely close ZMQ entities.
    zmq_close(m_stream_socket);
    zmq_close(m_notif_socket);
    zmq_ctx_term(m_context);
    delete[] m_buffer;
}

void WorkerFlow::ready()
{
    // tell the callback that we are ready.
    if (m_cb) {
        m_cb->on_start(this);
    }
}

bool WorkerFlow::recv_stream()
{
    // receive a workload into the worker buffer.
    int size = zmq_recv(m_stream_socket, m_buffer, m_buffsize, 0);
    if (size == -1) {
        throw std::string(strerror(errno));
    }

    // tell the callback that there's workload to take.
    if (m_cb) {
        m_cb->on_workload(m_buffer, size);
    }

    // Keep receiving
    return true;
}

bool WorkerFlow::recv_notif()
{
    // Receive a message from the notification channel
    int size = zmq_recv(m_notif_socket, m_buffer, m_buffsize, 0);
    if (size == -1) {
        throw std::string(strerror(errno));
    }

    // set the last byte to 0 to terminate the buffer correctly. This value
    // should be never seen by others.
    m_buffer[size] = 0;

    // For now, we only support __EndOfTransmission__ message
    // This must be extendable and standarized!
    if (strcmp(m_buffer, "#\\") == 0) {
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
    while (zmq_poll(items, 2, -1) == -1 && errno == EINTR) {
        std::cout << "zmq_poll: retrying" << std::endl;
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
    
    // zmq_poll failed with errno != EINTR
    std::cout << "Panic! > " << strerror(errno) << std::endl;
    return false;
}

void WorkerFlow::set_callback(Callback * cb)
{
    m_cb = cb;
}
