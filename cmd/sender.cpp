#include "SenderStream.hpp"
#include "SenderFlow.hpp"

#include <iostream>
#include <string>
#include <cassert>

int main(int argc, char * argv[]) {
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " bind file" << std::endl;
        return 0;
    }

    // get arguments from console.
    std::string bind(argv[1]);
    std::string file_path(argv[2]);

    // create the stream and a flow.
    SenderStream ss;
    SenderFlow * sf = ss.create_flow("flow-1", bind);

    FILE * file = fopen(argv[2], "r");
    assert(file);

    char buffer[524288];

    while (!feof(file)) {
        size_t read = fread(buffer, 1, sizeof(buffer), file);
        sf->send(buffer, read);
    }

    fclose(file);
}
