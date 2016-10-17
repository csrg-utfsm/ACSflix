#include <iostream>
#include <Simple.pb.h>
#include <BdFileBlock.pb.h>

#include "ProtobufWorker.h"

int main()
{
    ProtobufWorker worker("tcp://127.0.0.1:9999", "A");

    BdFileBlock file_block;

    while (worker.work(file_block)) {
        std::cout << file_block.offset() << ": " << file_block.data().length() << std::endl;
    }

    return 0;
}
