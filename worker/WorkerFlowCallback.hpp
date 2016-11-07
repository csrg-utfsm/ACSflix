#ifndef BDT_ENGINE_WORKERCALLBACK_HPP
#define BDT_ENGINE_WORKERCALLBACK_HPP


class WorkerFlow;


class WorkerFlowCallback
{
public:
	virtual void on_start(WorkerFlow * flow) = 0;
	virtual void on_workload(const char * buffer, size_t size) = 0;
	virtual void on_stop() = 0;
};


#endif //BDT_ENGINE_WORKERCALLBACK_HPP
