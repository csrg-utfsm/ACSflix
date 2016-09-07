#include <iostream>

#include "../emitter/Emitter.hpp"

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Please call with a file name argument" << std::endl;
        return 1;
    }

    return 0;
}
