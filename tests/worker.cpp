#include <iostream>
#include <Simple.pb.h>

#include "ProtobufWorker.h"

int main()
{
    ProtobufWorker worker("tcp://127.0.0.1:9999", "A");

    Simple simple;

    while (worker.work(simple)) {
        std::cout << simple.id() << ": " << simple.message() << std::endl;
    }

    return 0;
}
