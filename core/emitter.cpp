#include <iostream>

#include "sources/emitter/Emitter.hpp"

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Please call with a file name argument" << std::endl;
        return 1;
    }

    Emitter emitter;

    emitter.set_block_size(1024);

    emitter.start(argv[1], "AAAA");

    return 0;
}
