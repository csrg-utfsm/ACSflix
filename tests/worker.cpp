#include <iostream>
#include <BdFileBlock.pb.h>

#include "ProtobufWorker.h"

int main()
{
    std::string identity;

    std::cout << "Identity: ";
    std::cin >> identity;

    ProtobufWorker worker("tcp://127.0.0.1:9999", identity);

    BdFileBlock file_block;

    while (worker.work(file_block)) {
        std::cout << file_block.offset() << ": " << file_block.data().length() << std::endl;
    }

    return 0;
}
