#include <iostream>
#include <WorkerStream.hpp>
#include <stdlib.h>
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
		    //std::cout << accumulated << std::endl;
    }

    virtual void on_stop() override
    {
		    std::cout << "Received: " << accumulated << std::endl;
    }
};


int main(int argc, char * argv[])
{
    if (argc != 4) {
	std::cout << "Usage: " << *argv << " name connect tokens" << std::endl;
	return 1;
    }

    WorkerStream stream;

    size_t tokens = (size_t) strtol(argv[3], NULL, 10); // Assume correct input

    std::string identity(argv[1], strlen(argv[1]));

    SampleWorkerFlowCallback callback;
    stream.create_flow(identity, argv[2], &callback, tokens);
    stream.start();

    return 0;
}
