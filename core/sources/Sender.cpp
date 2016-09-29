#include <iostream>
#include "Sender.h"

Sender::Sender(std::string bind) :
        context(zctx_new()),
        router(zsocket_new(context, ZMQ_ROUTER))
{
    zsocket_bind(router, bind.c_str());

	// infinite wait before shutting down
	zctx_set_linger(context, -1);
}

Sender::~Sender()
{
	zctx_destroy(&context);
}

void Sender::send(unsigned char * data, size_t length)
{
    char * identity = zstr_recv(router);

    std::cout << "Sending to " << identity << std::endl;

    // ignore content.
    zstr_recv(router);

    // send message with an identity frame and content frame.
    zstr_sendm(router, identity);
    zmq_send(router, data, length, 0);
}

void Sender::send(zmq_msg_t *msg)
{
	char * identity = zstr_recv(router);

	std::cout << "Sending " << zmq_msg_size(msg)
	          << " bytes to " << identity
	          << std::endl;

	// ignore content.
	zstr_recv(router);

	// send message with an identity frame and content frame.
	zstr_sendm(router, identity);
	zmq_msg_send(msg, router, 0);
}
