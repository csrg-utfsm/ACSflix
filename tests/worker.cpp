#include <iostream>
#include <BdBlock.pb.h>

#include "ProtobufWorker.h"

int main()
{
    std::string identity;

    std::cout << "Identity: ";
    std::cin >> identity;

    ProtobufWorker worker("tcp://127.0.0.1:9991", identity);

    BdBlock file_block;

    while (worker.work(file_block)) {
        std::cout << file_block.offset() << ": " << file_block.message().length() << std::endl;
    }

    return 0;
}
