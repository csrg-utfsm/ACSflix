#include "SenderFlow.hpp"

#include <zmq.h>

SenderFlow::SenderFlow(std::string bind) :
    m_context(zmq_ctx_new()),
    m_socket(zmq_socket(m_context, ZMQ_PUSH))
{

}

void SenderFlow::send(char * buffer, size_t size)
{
    
}
