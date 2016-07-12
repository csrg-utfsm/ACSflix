#include <iostream>

#include "sources/subscriber/Subscriber.hpp"

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Please call with a file name argument" << std::endl;
        return 1;
    }

    Subscriber subscriber(argv[2]);
    subscriber.set_credits(10);

    subscriber.start(argv[1], "AAAA");

    return 0;
}
