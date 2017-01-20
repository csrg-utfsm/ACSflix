#include "WorkerFlow.h"
#include <iostream>
#include <cerrno>
#include <cstring>
#include <fstream>

WorkerFlow::WorkerFlow(std::string connect,
		       std::string identity,
		       WorkerFlowCallback * callback) :
    m_context(zmq_ctx_new()),
    m_dealer(zmq_socket(m_context, ZMQ_DEALER)),
    m_callback(callback),
    m_tokens(1),
    m_identity(identity),
    m_eintr_count(0)
{
    zmq_setsockopt(m_dealer, ZMQ_IDENTITY, identity.c_str(), identity.length());

    // Connect socket
    int rc = zmq_connect(m_dealer, connect.c_str());
    if (rc == -1) {
        std::cout << strerror(errno) << std::endl;
        exit(1);
    }

    int timeout = 5000; // 5s
    // zmq_setsockopt(m_dealer, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
}

WorkerFlow::~WorkerFlow()
{
    zmq_ctx_destroy(m_context);
}

WorkerFlowCallback * WorkerFlow::callback()
{
    return m_callback;
}

bool WorkerFlow::work()
{
    // send notifications to router.
    while (m_tokens) {
        zmq_send(m_dealer, "", 0, ZMQ_SNDMORE);
        zmq_send(m_dealer, "!", strlen("!"), 0);
        m_tokens--;
    }

    char buffer[4096]; // 4KB
    int size;

    // tokens always zero in this point
    //std::cout << "Waiting for sender..." << std::endl;
    size = zmq_recv(m_dealer, buffer, sizeof(buffer), 0); // delimiter.
    size = zmq_recv(m_dealer, buffer, sizeof(buffer), 0); // workload.

    std::cout << buffer ;
    m_tokens++;

    if (size == 0) {
        std::cerr << "Total failures: " << m_eintr_count << std::endl;
        return false;
    }


    m_callback->on_workload(buffer, size);


    return true;
}

void WorkerFlow::set_tokens(size_t tokens)
{
    m_tokens = tokens;
}

size_t WorkerFlow::get_tokens()
{
    return m_tokens;
}

std::string WorkerFlow::get_identity()
{
    return m_identity;
}
