#ifndef WORKERFLOW_H
#define WORKERFLOW_H

#include <string>

// Forward declarations.
class WorkerFlow;

// Callback is used by the worker to notify events related to his life cycle.
class Callback
{
public:
    // on_start is called when the worker starts, right after it gets created.
    virtual void on_start(WorkerFlow * flow) = 0;

    // on_workload is called when a new workload arrives.
    virtual void on_workload(char * buffer, size_t size) = 0;

    // on_stop is called when the worker will stop it's operations.
    virtual void on_stop() = 0;
};

// WorkerFlow implements the behavior of a Worker in the ACSFlix model, using
// the PUSH/PULL pattern. It creates it's own context and PULL socket, and work
// is done through the work() method.
class WorkerFlow
{
private:
    // ZeroMQ context.
    void * m_context;   

    // ZeroMQ socket.
    void * m_socket;    

    // Callback to notify lifecycle related events.
    Callback * m_cb;

    // Buffer to store incoming data, it will be reused every time work() is
    // called. It is allocated with a fixed size.
    // NOTE: the buffer is created with an extra byte for the null terminating
    // character, it should not be used for anything else.
    char m_buffer[524288 + 1];

public:
    // WorkerFlow creates a new Worker Flow, connected to a sender using the 
    // connect parameter. The connect parameter is formatted as ZMQ zmq_connect
    // format (see http://api.zeromq.org/4-2:zmq-connect).
    WorkerFlow(std::string connect, Callback * cb);

    ~WorkerFlow();

    // Work tells this worker to receive a workload and process it. Returns
    // true if there's more work to do. A worker should stop working when it
    // returns false.
    bool work();
};

#endif // WORKERFLOW_H
