#ifndef WORKERFLOW_H
#define WORKERFLOW_H

#include <string>

#define DEFAULT_BUFFER_SIZE 524288

// Forward declarations.
class WorkerFlow;

// Callback is used by the worker to notify events related to his life cycle.
class Callback
{
public:
    // on_start is called when the worker starts, through the ready() method.
    // (see WorkerFlow::ready()). If the flow is used within a stream, then the
    // ready() method will be fired automatically, if not, the ready()
    // method has to be called manually for this method to be called.
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
    void * m_stream_socket;    
    void * m_notif_socket;

    // Callback to notify lifecycle related events.
    Callback * m_cb;
    bool m_callback_owned;

    // Buffer to store incoming data, it will be reused every time work() is
    // called. ~It is allocated with a fixed size~ NOT ANYMORE.
    char *m_buffer;
    size_t m_buffsize;


    // Multiplex channels
    bool recv_stream();
    bool recv_notif();

public:
    // WorkerFlow creates a new Worker Flow, connected to a sender using the 
    // connect parameter. The connect parameter is formatted as ZMQ zmq_connect
    // format (see http://api.zeromq.org/4-2:zmq-connect).
    WorkerFlow(std::string connect, int port, size_t buffsize);

    ~WorkerFlow();

    // Called when the WorkerStream is about to poll each worker. If the flow
    // is not used within a stream, the user must call this method manually.
    void ready();

    // Work tells this worker to receive a workload and process it. Returns
    // true if there's more work to do. A worker should stop working when it
    // returns false.
    bool work();

    // Workflow callback setter
    void set_callback(Callback * cb);

    // Should own callback?
    void own_callback();
};

#endif // WORKERFLOW_H
