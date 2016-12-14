#ifndef BDT_ENGINE_WORKERFLOW_H
#define BDT_ENGINE_WORKERFLOW_H

#include <czmq.h>
#include <string>
#include "WorkerFlowCallback.hpp"

class WorkerFlow
{
	zctx_t * m_context;

	void * m_dealer;

	size_t m_tokens;

    std::string m_identity;

	WorkerFlowCallback * m_callback;

	int m_eintr_count;

	// TODO: save working state for exit checks.

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
