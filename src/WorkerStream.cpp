#include "WorkerStream.h"

WorkerStream::~WorkerStream()
{
    typedef std::map<std::string, WorkerWrapper*>::iterator it_type;

    for (it_type it = m_flows.begin(); it != m_flows.end(); it++) {
        delete it->second->flow;
        delete it->second;
    }
}

WorkerFlow * WorkerStream::create_flow(std::string name, std::string connect,
    size_t buffsize)
{
    // create the flow.
    WorkerFlow * flow = new WorkerFlow(connect, buffsize);

    // wrap the flow with additional meta-data.
    WorkerWrapper * wd = new WorkerWrapper;
    wd->flow = flow;
    wd->stopped = false;

    // register the flow.
    m_flows[name] = wd;

    return flow;
}

void WorkerStream::start() 
{
    typedef std::map<std::string, WorkerWrapper*>::iterator it_type;

    // tell each worker that it is ready to begin working.
    for (it_type it = m_flows.begin(); it != m_flows.end(); it++) {
        it->second->flow->ready();
    }

    // this flag will tell us if some flow isn't stopped, and iterate again.
    bool not_done = true;

    while (not_done) {
        not_done = false;

        // loop each flow.
        for (it_type it = m_flows.begin(); it != m_flows.end(); it++) {
            // if the flow is stopped, skip it.
            if (it->second->stopped) {
                continue;
            }

            // if the flow work() returns true, then there's more work to be
            // done.
            if (it->second->flow->work()) {
                // set the flag to true to iterate again.
                not_done = true;
            } else {
                // set this flow as stopped, in order to skip it.
                it->second->stopped = true;
            }
        }
    }
}