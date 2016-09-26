#include <iostream>
#include "Worker.h"

#include "Dummy.pb.h"
#include <iostream>
#include <cstring>

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

	DummyMessage dummyMessage;
	int len = (int) strlen(workload);

	dummyMessage.ParseFromArray(workload, len);

	std::cout << dummyMessage.id() << std::endl;
	std::cout << dummyMessage.message() << std::endl;

    //std::cout << workload << std::endl;
}
