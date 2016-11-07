#include "WorkerStream.hpp"


WorkerStream::~WorkerStream()
{
    typedef std::map<std::string, WorkerData*>::iterator it_type;

    for (it_type it = flows.begin(); it != flows.end(); it++) {
        delete it->second;
    }
}


WorkerFlow * WorkerStream::create_flow(std::string name, std::string connect, WorkerFlowCallback * callback,
        size_t tokens)
{
    WorkerFlow * flow = new WorkerFlow(connect, name, callback);
    flow->set_tokens(tokens);
    flows[name] = new WorkerData(flow);
    return flow;
}


void WorkerStream::start()
{
    prepare_flows();
    work_flows();
    on_stop_flows();
}


void WorkerStream::prepare_flows()
{
    typedef std::map<std::string, WorkerData*>::iterator it_type;

    for (it_type it = flows.begin(); it != flows.end(); it++) {
        it->second->flow->callback()->on_start(it->second->flow);
    }
}


void WorkerStream::work_flows()
{
    typedef std::map<std::string, WorkerData*>::iterator it_type;

    // this flag will tell us if some flow isn't stopped.
    bool not_done = true;

    while (not_done) {
        not_done = false;

        for (it_type it = flows.begin(); it != flows.end(); it++) {
            if (it->second->stopped) {
                continue;
            }

            if (it->second->flow->work()) {
                not_done = true;
            } else {
                it->second->stopped = true;
            }
        }
    }
}

void WorkerStream::on_stop_flows()
{
    typedef std::map<std::string, WorkerData*>::iterator it_type;

    for (it_type it = flows.begin(); it != flows.end(); it++) {
        it->second->flow->callback()->on_stop();
    }
}
