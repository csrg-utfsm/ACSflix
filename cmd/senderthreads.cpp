#include "SenderFlow.h"
#include "SenderStream.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <zmq.h>
#include <pthread.h>


#define panic(msg)\
    perror(msg); exit(EXIT_FAILURE);

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
    if (file == NULL) {
        char errmsg[32];
        sprintf(errmsg, "fopen(\"%s\")", filename.c_str());
        perror(errmsg);
        return NULL;
    }

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

    printf ("%d,", (int) message_size); // message size
    printf ("%d,", (int) message_count); // message count
    printf ("%d,", (int) throughput); // mean throughput msg/s
    printf ("%.3f\n", (double) megabits); // mean throughput Mbit/s
}


int main(int argc, char * argv[]) {
    int opt;
    int buffsize = 2048;
    int opts_consumed = 0;
    int message_count = 0;
    size_t message_size;
    void *watch;
    unsigned long elapsed;
    unsigned long throughput;
    double megabits;

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

    if (argc - opts_consumed != 5) {
        std::cerr << "Usage: " << argv[0] << " [-b buffsize] bind port file|debug threads" << std::endl;
        return 1;
    }

    // Assuming options before positional arguments
    argv += opts_consumed;

    // get arguments from console.
    std::string bind(argv[1]);
    std::string strport(argv[2]);
    std::string file_path(argv[3]);
    std::string strthreads(argv[4]);
    // port's numerical value
    int port;
    int threads;
    std::istringstream(strport) >> port;
    std::istringstream(strthreads) >> threads;
    struct flow_thread_args args[threads];
    pthread_t flows[threads];

    // create the stream and a flow.
    SenderStream ss;
    for (int i = 0; i < N_THREADS; i++) {
      std::stringstream sstr;
      sstr << "flow-" << i;
      args[i].flow = ss.create_flow(sstr, bind, port);
      args[i].filename = file_path;
      args[i].buffsize = buffsize;
      port++;

      if (pthread_create(flows + i, NULL, flow_thread, args + i) != 0) {
          std::stringstream sstr;
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
}
