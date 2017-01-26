#include "WorkerFlow.hpp"

#include <iostream>
#include <string>

class WorkerCallback : public Callback
{
public:
    void on_start(WorkerFlow * flow)
    {

    }

    void on_workload(char * buffer, size_t size)
    {
        std::cout << "Workload received!" << std::endl;
    }

    void on_stop()
    {

    }
};

int main(int argc, char * argv[]) {
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " connect output" << std::endl;
        return 0;
    }

    // get arguments from console.
    std::string connect(argv[1]);
    std::string output(argv[2]);

    // create the Callback and WorkerFlow with the connect argument.
    WorkerCallback cb;
    WorkerFlow wf(connect, &cb);

    while (wf.work());
}
