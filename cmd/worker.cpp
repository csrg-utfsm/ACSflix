#include "WorkerFlow.h"
#include "WorkerStream.h"

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
            m_output = fopen(output.c_str(), "w");
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

    // create the WorkerStream to manage flows.
    WorkerStream ws;

    // create the Callback for the flow.
    WorkerCallback cb(output);

    // create the flow from the stream, here we don't need to save the
    // instance.
    ws.create_flow("flow-1", connect, &cb);

    // call the start method to loop workers.
    ws.start();
    std::cout << "End of transmission" << std::endl;
}
