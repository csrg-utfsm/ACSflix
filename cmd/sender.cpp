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

void __raii_file(FILE **file)
{
    if (file) fclose(*file);
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

    if (argc - opts_consumed != 4) {
        std::cerr << "Usage: " << argv[0] << " [-b buffsize] bind port file|debug" << std::endl;
        return 1;
    }

    // Assuming options before positional arguments
    argv += opts_consumed;

    // get arguments from console.
    std::string bind(argv[1]);
    std::string strport(argv[2]);
    std::string file_path(argv[3]);
    // port's numerical value
    int port;
    std::istringstream(strport) >> port;

    // create the stream and a flow.
    SenderStream ss;
    SenderFlow * sf = ss.create_flow("flow-1", bind, port);

    if (file_path == "debug") {
        int msg_counter = 1;
        char message[256];

        while (msg_counter < 11) {
            sprintf(message, "Message #%d\n", msg_counter++);
            sf->send(message, strlen(message));
            std::cout << "Sent: " << message;
            sleep(1);
        }
    } else {
        FILE * file __attribute__((cleanup (__raii_file))) = NULL;
        file = fopen(file_path.c_str(), "r");

	if (file == NULL) {
	  perror("Could not open file");
	  return 1;
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

    printf ("%d,", (int) message_size); // message size
    printf ("%d,", (int) message_count); // message count
    printf ("%d,", (int) throughput); // mean throughput msg/s
    printf ("%.3f\n", (double) megabits); // mean throughput Mbit/s
    }

}
