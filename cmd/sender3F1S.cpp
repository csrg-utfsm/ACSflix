#include "SenderFlow.h"
#include "SenderStream.h"

#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <zmq.h>
#include <pthread.h>
#include <exception>

void __raii_file(FILE **file)
{
    if (file) fclose(*file);
}

void *flow_thread( void *threadfile  ){

    std::string filename ;
    pthread_t self_id = pthread_self();

    FILE * file __attribute__((cleanup (__raii_file))) = NULL;
    try{
	filename = *reinterpret_cast<std::string*>(threadfile);
    	file = fopen(filename, "r");
    } catch (const std::exception& e) {
	std::cout << e.what() << "'\n";
	exit (EXIT_FAILURE);
    }

    char *buffer = new char[buffsize];
    watch = zmq_stopwatch_start();

    while (!feof(file)) {
        size_t read = fread(buffer, 1, buffsize, file);
        sf->send(buffer, read);
        message_count++;
    }
    delete[] buffer;

    elapsed = zmq_stopwatch_stop (watch);
    if (elapsed == 0)
        elapsed = 1;

    message_size = buffsize;
    throughput = (unsigned long) ((double) message_count / (double) elapsed * 1000000);
    megabits = (double) (throughput * message_size * 8) / 1000000;

    printf ("Flow id %u. message size: %d [B]\n", self_id, (int) message_size);
    printf ("Flow id %u. message count: %d\n", self_id, (int) message_count);
    printf ("Flow id %u. mean throughput: %d [msg/s]\n", self_id, (int) throughput);
    printf ("Flow id %u. mean throughput: %.3f [Mb/s]\n", self_id, (double) megabits);

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
    pthread_t flow1;
    pthread_t flow2;
    pthread_t flow3;
    int thr_flow1, thr_flow2, thr_flow3;

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
        std::cerr << "Usage: " << argv[0] << " [-b buffsize] bind file" << std::endl;
        return 1;
    }

    // Assuming options before positional arguments
    argv += opts_consumed;

    // get arguments from console.
    std::string bind(argv[1]);
    std::string file_path1(argv[2]);
    std::string file_path2(argv[3]);
    std::string file_path3(argv[4]);

    // create the stream and a flow.
    SenderStream ss;
    SenderFlow * sf1 = ss.create_flow("flow1", bind);
    SenderFlow * sf2 = ss.create_flow("flow2", bind);
    SenderFlow * sf3 = ss.create_flow("flow3", bind);

    // Self reminder: pthread_create(pthread_t threadID, threadAttr, function to be used, parameters of function )
    flow1 = pthread_create(flow1,NULL,flow_thread,&file_path1);
    flow2 = pthread_create(flow1,NULL,flow_thread,&file_path2);
    flow3 = pthread_create(flow1,NULL,flow_thread,&file_path3);

    assert(flow1 == 0)
    assert(flow2 == 0)
    assert(flow3 == 0)

}
