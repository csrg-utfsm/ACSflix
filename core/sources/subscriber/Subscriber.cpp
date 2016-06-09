#include <iostream>
#include "Subscriber.hpp"

Subscriber::Subscriber(std::string ip) :
        ContextListener(ZMQ_SUB)
{
    zsocket_connect(socket, ("tcp://" + ip + ":5678").c_str());
}

void Subscriber::start(std::string file_path, std::string channel)
{
    zsocket_set_subscribe(socket, channel.c_str());
    std::cout << "Subscribed to " << channel << std::endl;

    auto deleter = [](zmsg_t * message) {
        zmsg_destroy(&message);
    };

    std::unique_ptr<zmsg_t, decltype(deleter)> message(nullptr, deleter);

    while (!zctx_interrupted) {
        message.reset(zmsg_recv(socket));

        if (message.get() == nullptr) {
            continue;
        }

        for (int i = 0; i < zmsg_size(message.get()); ++i) {
            zmsg_pop(message.get());
            zframe_t * content = zmsg_pop(message.get());

            std::unique_ptr<char> content_str(zframe_strdup(content));
            std::cout << content_str.get() << std::endl;
        }

        wait_interval();
    }
}
