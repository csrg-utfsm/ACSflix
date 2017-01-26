#include "SenderStream.hpp"

SenderStream::~SenderStream()
{
    // delete all allocated flows.
    typedef std::map<std::string, SenderFlow*>::iterator it_type;
    for(it_type it = m_flows.begin(); it != m_flows.end(); it++) {
        delete it->second;
    }
}

SenderFlow * SenderStream::create_flow(std::string name, std::string bind)
{
    SenderFlow * flow = new SenderFlow(bind);
    m_flows[name] = flow;
    return flow;
}
