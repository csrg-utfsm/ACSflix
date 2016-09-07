#include <iostream>

#include "../receiver/Receiver.hpp"
#include "../util/utils.h"

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

    return 0;
}
