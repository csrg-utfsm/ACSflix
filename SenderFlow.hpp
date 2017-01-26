#ifndef SENDERFLOW_H
#define SENDERFLOW_H

#include <string>

// SenderFlow implements the sender behavior in the ACSFlix model, using the 
// PUSH/PULL pattern. It creates it's own context and PUSH Socket, workloads
// are sent with the send() method.
class SenderFlow
{
private:
    // ZMQ Context.
    void * m_context;

    // ZMQ Socket.
    void * m_socket;

public:
    // SenderFlow creates a new SenderFlow bound to the bind parameter given. 
    // The bind parameter must be in the zmq_bind format (see 
    // http://api.zeromq.org/4-2:zmq-bind).
    SenderFlow(std::string bind);

    // Send a buffer to a worker, in round robin order.
    void send(char * buffer, size_t size);
};

#endif // SENDERFLOW_H
