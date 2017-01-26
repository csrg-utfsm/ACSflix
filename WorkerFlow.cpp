#include "WorkerFlow.hpp"

#include <zmq.h>

WorkerFlow::WorkerFlow(std::string connect, Callback * cb) : 
    m_context(zmq_ctx_new()),
    m_socket(zmq_socket(m_context, ZMQ_PULL)),
    m_cb(cb)
{
    
}

bool WorkerFlow::work()
{
    return false;
}
