#include <iostream>
#include "Worker.h"

Worker::Worker(std::string connect, std::string identity) :
    context(zctx_new()),
    dealer(zsocket_new(context, ZMQ_DEALER))
{
    zsocket_set_identity(dealer, (char *) identity.c_str());
    zsocket_connect(dealer, connect.c_str());
}

Worker::~Worker()
{
    zctx_destroy(&context);
}

void Worker::work()
{
    zstr_send(dealer, "");

    char * workload = zstr_recv(dealer);

    std::cout << workload << std::endl;
}
