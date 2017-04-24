#include "WorkerFlow.h"
#include "WorkerStream.h"

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

class WorkerCallback : public Callback
{
    FILE * m_output;

public:
    WorkerCallback(std::string output)
    {
        if (output == "stdout") {
            m_output = stdout;
        } else if (output == "null") {
            m_output = NULL;
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
        if (m_output) {
            fwrite(buffer, 1, size, m_output);
            fflush(m_output);
        }
    }

    void on_stop()
    {
        fclose(m_output);
    }
};

int main(int argc, char * argv[])
{
    int opt;
    size_t buffsize = 2048;
    int opts_consumed = 0;

    while ((opt = getopt(argc, argv, "b:")) != -1) {
        switch (opt) {
        case 'b':
            opt = strtol(optarg, NULL, 10);
            buffsize = (opt > 0) ? opt : buffsize;
            opts_consumed += 2;
            break;
        default:
            return 1;
        }
    }

    if (argc - opts_consumed != 3) {
        std::cerr << "Usage: " << argv[0]
            << " [-b buffsize] connect output|stdout|null"
            << std::endl;
        return 0;
    }

    // Assuming options before positional arguments
    argv += opts_consumed;

    // get arguments from console.
    std::string connect(argv[1]);
    std::string output(argv[2]);

    // create the WorkerStream to manage flows.
    WorkerStream ws;

    // create the Callback for the flow.
    WorkerCallback cb(output);

    // create the flow from the stream, here we don't need to save the
    // instance.
    WorkerFlow *wf = ws.create_flow("flow-1", connect, buffsize);
    wf->set_callback(&cb);

    // call the start method to loop workers.
    ws.start();
    std::cout << "End of transmission" << std::endl;
}
