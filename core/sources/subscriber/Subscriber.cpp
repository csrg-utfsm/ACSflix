#include <iostream>
#include "Subscriber.hpp"

Subscriber::Subscriber() :
        context(zctx_new(), [](zctx_t * context) {
            zctx_destroy(&context);
        }),
        socket(zsocket_new(context.get(), ZMQ_SUB))
{
    zsocket_connect(socket, "tcp://127.0.0.1:5678");
    zsocket_set_subscribe(socket, "AAAA");
    std::cout << "Subscribed to AAAA" << std::endl;
}

void Subscriber::mainloop()
{
    auto deleter = [](zmsg_t * message) {
        zmsg_destroy(&message);
    };

    while (!zctx_interrupted) {
        std::unique_ptr<zmsg_t, decltype(deleter)> message(zmsg_recv(socket), deleter);

        for (int i = 0; i < zmsg_size(message.get()); ++i) {
            zmsg_pop(message.get());
            zframe_t * content = zmsg_pop(message.get());

            char * content_str = zframe_strdup(content);

            std::cout << content_str << std::endl;

            free(content_str);
        }

        zclock_sleep(500);
    }
}
