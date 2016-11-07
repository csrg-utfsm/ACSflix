#ifndef BDT_ENGINE_WORKERSTREAM_HPP
#define BDT_ENGINE_WORKERSTREAM_HPP


#include <string>
#include <map>

#include "WorkerFlowCallback.hpp"
#include "WorkerFlow.h"


struct WorkerData
{
    WorkerFlow * flow;
    bool stopped;

    WorkerData(WorkerFlow * flow) :
            flow(flow),
            stopped(false)
    {}

    ~WorkerData()
    {
        delete flow;
    }
};


class WorkerStream
{
private:
    std::map<std::string, WorkerData*> flows;

    void prepare_flows();

    void work_flows();

    void on_stop_flows();

public:
    WorkerFlow * create_flow(std::string name, std::string connect, WorkerFlowCallback * callback,
            size_t tokens = 1);

    ~WorkerStream();

    void start();
};


#endif //BDT_ENGINE_WORKERSTREAM_HPP
