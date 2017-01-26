#ifndef SENDERSTREAM_HPP
#define SENDERSTREAM_HPP

#include "SenderFlow.hpp"

#include <map>
#include <string>

// This class wraps many flows and manages their allocation and deallocation.
class SenderStream
{
private:
    std::map<std::string, SenderFlow*> m_flows;

public:
    ~SenderStream();

    // Creates a sender flow with the given name and bound to the bind given.
    // (see SenderFlow constructor). The allocated flow will be managed by this
    // class. The SenderFlow returned must be used manually.
    SenderFlow * create_flow(std::string name, std::string bind);
};

#endif // SENDERSTREAM_HPP
