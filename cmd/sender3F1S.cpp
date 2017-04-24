#include "SenderFlow.h"
#include "SenderStream.h"

#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <cerrno>
#include <unistd.h>
#include <cstdlib>
#include <zmq.h>
#include <pthread.h>
#include <jsmnutils.h>
#include <sstream>

#define panic(msg)\
    perror(msg); exit(EXIT_FAILURE);

#define N_THREADS 3

void __raii_file(FILE **file)
{
    if (file) fclose(*file);
}

struct flow_thread_args
{
    SenderFlow *flow;
    std::string filename;
    size_t buffsize;
};

void *flow_thread(void *thread_args)
{
    int message_count = 0;
    unsigned long elapsed;
    unsigned long throughput;
    double megabits;

    // Get thread arguments
    struct flow_thread_args *args = (struct flow_thread_args*)thread_args;
    SenderFlow *sf = args->flow;
    std::string filename = args->filename;
    size_t buffsize = args->buffsize;

    FILE *file __attribute__((cleanup (__raii_file))) =
        fopen(filename.c_str(), "r");

    char *buffer = new char[buffsize];
    void *watch = zmq_stopwatch_start();

    while (!feof(file)) {
        size_t read = fread(buffer, 1, buffsize, file);
        sf->send(buffer, read);
        message_count++;
    }
    delete[] buffer;

    elapsed = zmq_stopwatch_stop (watch);
    if (elapsed == 0)
        elapsed = 1;

    size_t message_size = buffsize;
    throughput = (unsigned long) ((double) message_count / (double) elapsed * 1000000);
    megabits = (double) (throughput * message_size * 8) / 1000000;

    printf ("%s. message size: %d [B]\n", sf->name().c_str(), (int) message_size);
    printf ("%s. message count: %d\n", sf->name().c_str(), (int) message_count);
    printf ("%s. mean throughput: %d [msg/s]\n", sf->name().c_str(), (int) throughput);
    printf ("%s. mean throughput: %.3f [Mb/s]\n", sf->name().c_str(), (double) megabits);
}

void usage(char *argv[])
{
    std::cerr << "Usage: " << *argv << " config_file" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]) {
    int opt;
    int buffsize = 2048; // default buffer size
    int opts_consumed = 0;
    pthread_t flows[N_THREADS];
    struct flow_thread_args args[N_THREADS];

    if (argc != 2) {
        usage(argv);
    }
    std::string config_file(argv[1]);
    
    // Parse config file (assume it has no errors)
    JSONParser parser;
    parser.load_file(config_file);
    JSONObject config = parser.parse();

    // REQUIRED: default binding
    std::string default_bind = config["bind"];
    JSONArray flows_config = config["flows"];
    try {
        buffsize = (int)config["buffsize"];
    } catch (JSMNUtilsEx &ex) {
        // buffsize stays default
    }
    // Initialize SenderStream
    SenderStream ss;

    for (int i = 0; i < N_THREADS; i++) {
        JSONObject flow_config = flows_config[i];
        std::string flow_name = flow_config["name"];
        std::string flow_bind = default_bind;
        int flow_buffsize = buffsize;
        try {
            flow_bind = (std::string)flow_config["bind"];
        } catch (JSMNUtilsEx &ex) {
            // bind stays default
        }
        try {
            flow_buffsize = (int)flow_config["buffsize"];
        } catch(JSMNUtilsEx &ex) {
            // buffsize stays default
        }
        int flow_port = flow_config["port"];
        std::stringstream sstr;
        sstr << flow_bind << ":" << flow_port;
        flow_bind = sstr.str(); // something like "tcp://localhost:5000"
        std::string filename = flow_config["file"];
        // Create flow - make arguments for thread
        args[i].flow = ss.create_flow(flow_name, flow_bind);
        args[i].filename = filename;
        args[i].buffsize = flow_buffsize;
        // Create pthread
        if (pthread_create(flows + i, NULL, flow_thread, args + i) != 0) {
            sstr << "pthread_create(flow" << (i + 1);
            panic(sstr.str().c_str());
        }
    }
    // Join all threads
    for (int i = 0; i < N_THREADS; i++) {
        if (pthread_join(flows[i], NULL) != 0) {
            std::stringstream sstr;
            sstr << "pthread_join(flow" << (i + 1);
            panic(sstr.str().c_str());
        }
    }
    // ss goes out of scope and deletes flows!
}
