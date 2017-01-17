#ifndef BDT_ENGINE_WORKERFLOW_H
#define BDT_ENGINE_WORKERFLOW_H

#include <string>
#include <zmq.h>
#include "WorkerFlowCallback.hpp"

class WorkerFlow
{
    void * m_context;

    void * m_dealer;

    size_t m_tokens;

    int m_eintr_count;
    
    std::string m_identity;
    char m_identity_uuid[37];

    WorkerFlowCallback * m_callback;

public:
    WorkerFlow(std::string connect,
	       std::string identity,
	       WorkerFlowCallback * callback);

    virtual ~WorkerFlow();

    WorkerFlowCallback * callback();

    bool work();

    void set_tokens(size_t tokens);

    size_t get_tokens();

    std::string get_identity();
};


#endif //BDT_ENGINE_WORKERFLOW_H
