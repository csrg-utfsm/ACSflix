#ifndef SENDERFLOW_H
#define SENDERFLOW_H

#include <string>
#include <stdexcept>

class SenderFlowEx : public std::runtime_error
{
public:
    SenderFlowEx(std::string errmsg) :
        std::runtime_error("senderflow error: " + errmsg) {}
};

// SenderFlow implements the sender behavior in the ACSFlix model, using the 
// PUSH/PULL pattern. It creates it's own context and PUSH Socket, workloads
// are sent with the send() method.
class SenderFlow
{
    // ZMQ Context.
    void * m_context;

    // ZMQ Socket.
    void * m_stream_socket;
    void * m_notif_socket;

    // Name
    std::string m_name;

    // End of transmission notification
    void end_transmission();

public:
    // SenderFlow creates a new SenderFlow bound to the bind parameter given. 
    // The bind parameter must be in the zmq_bind format (see 
    // http://api.zeromq.org/4-2:zmq-bind).
    SenderFlow(std::string bind, int port);

    ~SenderFlow();

    // Send a buffer to a worker, in round robin order.
    void send(char * buffer, size_t size);

    void set_name(std::string name);
    std::string name() const;
};

#endif // SENDERFLOW_H
