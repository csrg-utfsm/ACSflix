#include "SenderFlow.h"

#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <unistd.h>

void __raii_file(FILE **file)
{
    if (file) fclose(*file);
}

int main(int argc, char * argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " bind file|debug" << std::endl;
        return 0;
    }

    // get arguments from console.
    std::string bind(argv[1]);
    std::string file_path(argv[2]);

    // create the Callback and WorkerFlow with the connect argument.
    SenderFlow sf(bind);

    if (file_path == "debug") {
        int msg_counter = 1;
        char message[256];

        while (msg_counter < 11) {
            sprintf(message, "Message #%d\n", msg_counter++);
            sf.send(message, strlen(message));
            std::cout << "Sent: " << message;
            sleep(1);
        }
    } else {
        FILE * file __attribute__((cleanup (__raii_file))) = NULL;
        file = fopen(argv[2], "r");
        assert(file);

        char buffer[524288];

        while (!feof(file)) {
            size_t read = fread(buffer, 1, sizeof(buffer), file);
            sf.send(buffer, read);
        }
    }

}
