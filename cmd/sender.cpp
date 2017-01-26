#include "SenderFlow.hpp"

#include <iostream>
#include <string>

int main(int argc, char * argv[]) {
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " bind file" << std::endl;
        return 0;
    }

    // get arguments from console.
    std::string bind(argv[1]);
    std::string file_path(argv[2]);

    // create the Callback and WorkerFlow with the connect argument.
    SenderFlow sf(bind);

    sf.send(NULL, 0);
}
