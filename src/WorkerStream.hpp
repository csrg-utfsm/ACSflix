#ifndef WORKERSTREAM_H
#define WORKERSTREAM_H

#include "WorkerFlow.hpp"

#include <string>
#include <map>

struct WorkerWrapper
{
    WorkerFlow * flow;
    bool stopped;
};

// Manages a collection of WorkerFlows, the user must create them through this
// class create_flow() method. This class will manage the allocation and
// deallocation of each WorkerFlow.
class WorkerStream
{
private:
    // Stores all flows in this stream.
    std::map<std::string, WorkerWrapper*> m_flows;

public:
    // Creates a new WorkerFlow with the given name, using the connect string
    // and the callback (see WorkerFlow constructor). The returned WorkerFlow
    // must not be destroyed manually, this class will dispose them as 
    // necessary.
    WorkerFlow * create_flow(std::string name, std::string connect, 
        Callback * cb);

    ~WorkerStream();

    // Starts all workers, iterating them in a round robin order.
    void start();
};

#endif // WORKERSTREAM_H