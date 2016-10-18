#include "ProtobufWorker.h"

#include <iostream>

ProtobufWorker::ProtobufWorker(std::string connect, std::string identity) :
        context(zctx_new()),
        dealer(zsocket_new(context, ZMQ_DEALER))
{
    zsocket_set_identity(dealer, (char *) identity.c_str());
    zsocket_connect(dealer, connect.c_str());
}


ProtobufWorker::~ProtobufWorker()
{
    zctx_destroy(&context);
}


bool ProtobufWorker::work(google::protobuf::MessageLite & message)
{
    // send notification to router.
    zstr_send(dealer, "");

    zmq_msg_t msg;
    zmq_msg_init(&msg);
    zmq_msg_recv(&msg, dealer, 0);

    if (zmq_msg_size(&msg) == 0) {
        return false;
    }

    message.ParseFromArray(zmq_msg_data(&msg), (int) zmq_msg_size(&msg));

    zmq_msg_close(&msg);

    return true;
}
