#include <iostream>

#include "sources/receiver/Receiver.hpp"
#include "sources/util/utils.h"

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Please call with a file name argument" << std::endl;
        return 1;
    }

    if (argc == 2) {
        std::cerr << "Specify the publisher IP." << std::endl;
        return 1;
    }

    if (argc == 3) {
        std::cerr << "Specify the credits argument." << std::endl;
        return 1;
    }

    Receiver receiver(argv[2]);
    receiver.set_credits((size_t) bdt::str_to_int(argv[3]));

    receiver.start(argv[1], "AAAA");

    return 0;
}
