#include "WorkerFlow.h"

#include <iostream>
#include <string>
#include <cstdio>

class WorkerCallback : public Callback
{
    FILE * m_output;

public:
    WorkerCallback(std::string output)
    {
        if (output == "stdout") {
            m_output = stdout;
        } else {
            fopen(output.c_str(), "w");
        }
    }

    void on_start(WorkerFlow * flow) 
    {
        std::cout << "Callback initialized" << std::endl;
    }

    void on_workload(char * buffer, size_t size)
    {
        fwrite(buffer, 1, size, m_output);
        fflush(m_output);
    }

    void on_stop()
    {
        fclose(m_output);
    }
};

int main(int argc, char * argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " connect output|stdout" << std::endl;
        return 0;
    }

    // get arguments from console.
    std::string connect(argv[1]);
    std::string output(argv[2]);

    // create the Callback and WorkerFlow with the connect argument.
    WorkerCallback cb(output);
    WorkerFlow wf(connect, &cb);

    // Receive workloads
    while (wf.work());
    std::cout << "End of transmission" << std::endl;
}
