#include <iostream>
#include <WorkerStream.hpp>

#include "ProtobufWorker.h"


class SampleWorkerFlowCallback : public WorkerFlowCallback
{
private:
    WorkerFlow * flow;
    size_t accumulated;

public:
    virtual void on_start(WorkerFlow * flow) override
    {
        this->flow = flow;

		    accumulated = 0;

        std::cout << "Started flow " << flow->get_identity() << " with "
                  << flow->get_tokens() << " tokens." << std::endl;
    }

    virtual void on_workload(const char * buffer, size_t size) override
    {
		    accumulated += size;
    }

    virtual void on_stop() override
    {
		    std::cout << "Received: " << accumulated << std::endl;
    }
};


int main(int argc, char * argv[])
{
    WorkerStream stream;

    SampleWorkerFlowCallback callback;
    stream.create_flow(argv[1], argv[2], &callback, 1);
    stream.start();

    return 0;
}
