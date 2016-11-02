#ifndef BDT_ENGINE_WORKERFLOW_H
#define BDT_ENGINE_WORKERFLOW_H

#include <czmq.h>
#include <string>
#include "WorkerFlowCallback.hpp"

class WorkerFlow
{
	zctx_t * m_context;

	void * m_dealer;

	WorkerFlowCallback * m_callback;

	// TODO: save working state for exit checks.

public:
	WorkerFlow(std::string connect,
	           std::string identity,
	           WorkerFlowCallback * callback);

	virtual ~WorkerFlow();

	WorkerFlowCallback * callback();

	bool work();
};


#endif //BDT_ENGINE_WORKERFLOW_H
