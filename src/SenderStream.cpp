#include "SenderStream.h"

SenderStream::~SenderStream()
{
    // delete all allocated flows.
    typedef std::map<std::string, SenderFlow*>::iterator it_type;
    for(it_type it = m_flows.begin(); it != m_flows.end(); it++) {
        delete it->second;
    }
}

SenderFlow * SenderStream::create_flow(std::string name, std::string bind, int port)
{
    SenderFlow * flow = new SenderFlow(bind, port);
    flow->set_name(name);
    m_flows[name] = flow;
    return flow;
}
