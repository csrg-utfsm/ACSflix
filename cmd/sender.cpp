#include "SenderFlow.h"
#include "SenderStream.h"

#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>

void __raii_file(FILE **file)
{
    if (file) fclose(*file);
}

int main(int argc, char * argv[]) {
    int opt;
    int buffsize = 2048;
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
        std::cerr << "Usage: " << argv[0] << " [-b buffsize] bind file|debug" << std::endl;
        return 1;
    }

    // Assuming options before positional arguments
    argv += opts_consumed;

    // get arguments from console.
    std::string bind(argv[1]);
    std::string file_path(argv[2]);

    // create the stream and a flow.
    SenderStream ss;
    SenderFlow * sf = ss.create_flow("flow-1", bind);

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
        file = fopen(argv[2], "r");
        assert(file);

        char *buffer = new char[buffsize];

        while (!feof(file)) {
            size_t read = fread(buffer, 1, buffsize, file);
            sf->send(buffer, read);
        }

        delete[] buffer;
        std::cout << "EOF" << std::endl;
    }

}
