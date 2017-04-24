#include <WorkerFlow.h>
#include <WorkerStream.h>

#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <cerrno>
#include <unistd.h>
#include <cstdlib>
#include <zmq.h>
#include <jsmnutils.h>
#include <sstream>

#define panic(msg)\
    perror(msg); exit(EXIT_FAILURE);

#define N_THREADS 3

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

void usage(char *argv[])
{
    std::cerr << "Usage: " << *argv << " config_file" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    size_t buffsize = 2048;

    if (argc != 2) {
        usage(argv);
    }
    std::string config_file(argv[1]);

    // Parse config file (assume it has no errors)
    JSONParser parser;
    parser.load_file(config_file);
    JSONObject config = parser.parse();

    // REQUIRED: default connect
    std::string default_connect = config["bind"];
    JSONArray flows_config = config["flows"];
    try {
        buffsize = (int)config["buffsize"];
    } catch (JSMNUtilsEx &ex) {
        // buffsize stays default
    }
    // Initialize WorkerStream
    WorkerStream ws;

    for (int i = 0; i < N_THREADS; i++) {
        JSONObject flow_config = flows_config[i];
        std::string flow_name = flow_config["name"];
        std::string flow_connect = default_connect;
        int flow_buffsize = buffsize;
        try {
            flow_connect = (std::string)flow_config["bind"];
        } catch (JSMNUtilsEx &ex) {
            // bind stays default
        }
        try {
            flow_buffsize = (int)flow_config["buffsize"];
        } catch (JSMNUtilsEx &ex) {
            // buffsize stays default
        }
        int flow_port = flow_config["port"];
        std::stringstream ss;
        ss << flow_connect << ":" << flow_port;
        flow_connect = ss.str(); // something like "tcp://localhost:5000"
        std::string filename = flow_config["file"];
        // Create flow
        WorkerFlow *flow = ws.create_flow(flow_name, flow_connect,
                flow_buffsize);
        WorkerCallback *cb = new WorkerCallback(filename);
        flow->set_callback(cb);
        flow->own_callback(); // take care of it
        filename = filename;
        buffsize = buffsize;
    }

    // call the start method to loop workers.
    ws.start();
}
