#include <iostream>

#include "sources/publisher/Publisher.hpp"

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Please call with a file name argument" << std::endl;
        return 1;
    }

    Publisher publisher;

    publisher.set_block_size(1024);

    publisher.start(argv[1], "AAAA");

    return 0;
}
