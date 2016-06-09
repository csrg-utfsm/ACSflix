#include <iostream>
#include <fstream>
#include "Publisher.hpp"

Publisher::Publisher() :
        context(zctx_new(), [](zctx_t * context) {
            zctx_destroy(&context);
        }),
        socket(zsocket_new(context.get(), ZMQ_PUB))
{
    zsocket_bind(socket, "tcp://*:5678");
}

void Publisher::mainloop()
{
    std::ifstream in("test.txt", std::ios_base::binary);

    if (!in) {
        std::cout << "File not found" << std::endl;
    }

    std::streamoff offset = 0;
    size_t size = 11;
    char buffer[size];

    while (!zctx_interrupted) {
        memset(buffer, 0, size);

        in.seekg(offset);
        in.read(buffer, size);
        offset += size;

        zstr_sendm(socket, "AAAA");
        zmq_send(socket, buffer, size, 0);

        std::cout << buffer << std::endl;
        std::cout << "Sending message" << std::endl;

        zclock_sleep(500);
    }
}
