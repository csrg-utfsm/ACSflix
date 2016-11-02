#include "SenderStream.hpp"

SenderStream::SenderStream(BufferPool & pool, int linger) :
        pool(pool),
        linger(linger)
{

}

SenderStream::~SenderStream()
{
    // delete all allocated flows.
    typedef std::map<std::string, SenderFlow*>::iterator it_type;
    for(it_type iterator = flows.begin(); iterator != flows.end(); iterator++) {
        delete(flows[iterator->first]);
    }
}

template <class T>
T * SenderStream::create_flow(std::string flow_name, std::string connect)
{
    T * flow = new T(connect, linger);
    flow->attach_buffer_pool(pool);

    flows[flow_name] = flow;

    return flow;
}

SenderFlow * SenderStream::get_flow(std::string name)
{
    if (exist_flow(name)) {
        return flows[name];
    }

    // returns NULL if no flow was found.
    return NULL;
}

bool SenderStream::exist_flow(std::string name)
{
    return flows.find(name) != flows.end();
}
