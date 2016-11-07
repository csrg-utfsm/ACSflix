#include <iostream>
#include <BdBlock.pb.h>
#include <WorkerStream.hpp>

#include "ProtobufWorker.h"


class SampleWorkerFlowCallback : public WorkerFlowCallback
{
private:
    BdBlock file_block;

public:
    virtual void on_start(WorkerFlow * flow) override
    {
        std::cout << "Started flow with " << flow->get_tokens() << " tokens." << std::endl;
    }

    virtual void on_workload(const char * buffer, size_t size) override
    {
        file_block.ParseFromArray(buffer, (int) size);
        std::cout << "Received message of size: " << file_block.message().size() << std::endl;
    }

    virtual void on_stop() override
    {

    }
};


int main(int argc, char * argv[])
{
    WorkerStream stream;

    SampleWorkerFlowCallback callback;
    stream.create_flow(argv[1], "tcp://127.0.0.1:9991", &callback, (size_t) std::stoi(argv[2]));
    stream.start();

    return 0;
}
