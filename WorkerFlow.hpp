#ifndef WORKERFLOW_H
#define WORKERFLOW_H

#include <string>

// WorkerFlow implements the behavior of a Worker in the ACSFlix model, using
// the PUSH/PULL pattern. It creates it's own context and PULL socket, and work
// is done through the work() method.
class WorkerFlow {
private:
    // ZeroMQ context.
    void * m_context;   

    // ZeroMQ socket.
    void * m_socket;    

    // WorkerBuffer to store incoming data, it will be reused every time work()
    // is called. It is allocated with a fixed size.
    char m_buffer[524288];

public:
    // WorkerFlow creates a new Worker Flow, connected to a sender using the 
    // connect parameter. The connect parameter is formatted as ZMQ zmq_connect
    // format (see http://api.zeromq.org/4-2:zmq-connect).
    WorkerFlow(std::string connect);

    // Work tells this worker to receive a workload and process it. Returns
    // true if there's more work to do. A worker should stop working when it
    // returns false.
    bool work();
}

#endif // WORKERFLOW_H
