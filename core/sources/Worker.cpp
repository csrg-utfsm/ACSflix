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
    std::cout << workload << std::endl;
}

void Worker::workMSG()
{
	zstr_send(dealer, "");

	zmq_msg_t msg;
	zmq_msg_init(&msg);
	zmq_msg_recv(&msg, dealer, 0);

	std::string string((char*)zmq_msg_data(&msg), zmq_msg_size(&msg));

	std::cout << "Received " << zmq_msg_size(&msg)
	          << " bytes:" << string << std::endl;

	DummyMessage dummyMessage;
	try {
		dummyMessage.ParseFromArray(zmq_msg_data(&msg),
		                            (int) zmq_msg_size(&msg));

		std::cout << "[" << dummyMessage.id() << "] "
		          << dummyMessage.message() << std::endl;

	} catch (google::protobuf::FatalException& fe) {
		std::cout << "Ignored: " << fe.message() << std::endl;
	}

	zmq_msg_close(&msg);
}

bool Worker::workPieces()
{
	zstr_send(dealer, "");

	zmq_msg_t msg;
	zmq_msg_init(&msg);
	zmq_msg_recv(&msg, dealer, 0);

	std::string piece((char*) zmq_msg_data(&msg), zmq_msg_size(&msg));
	std::cout << "Received " << zmq_msg_size(&msg)
	          << " bytes: " << piece << std::endl;

	zmq_msg_close(&msg);

	return piece != "END_OF_TRANSMISSION";
}
