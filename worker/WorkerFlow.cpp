#include "WorkerFlow.h"
#include <iostream>
#include <cerrno>
#include <cstring>
#include <uuid/uuid.h>

void gen_uuid(char uuid_str[37])
{
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse_lower(uuid, uuid_str);
    std::cout << "uuid: " << uuid_str << std::endl;
    std::cout.flush();
}

WorkerFlow::WorkerFlow(std::string connect,
		       std::string identity,
		       WorkerFlowCallback * callback) :
    m_context(zmq_ctx_new()),
    m_dealer(zmq_socket(m_context, ZMQ_DEALER)),
    m_callback(callback),
    m_tokens(1),
    m_identity(identity),
    m_eintr_count(0)
{
    gen_uuid(m_identity_uuid);
    zmq_setsockopt(m_dealer,
		   ZMQ_IDENTITY,
		   m_identity_uuid,
		   strlen(m_identity_uuid));

    // Connect socket
    zmq_connect(m_dealer, connect.c_str());

    int timeout = 5000; // 5s
    zmq_setsockopt(m_dealer, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
}

WorkerFlow::~WorkerFlow()
{
    zmq_ctx_destroy(m_context);
}

WorkerFlowCallback * WorkerFlow::callback()
{
    return m_callback;
}

bool WorkerFlow::work()
{
    char id[256];
    size_t id_size = 256;

    //zmq_getsockopt(m_dealer, ZMQ_IDENTITY, id, &id_size);
    //std::cout << "id: " << id_size << std::endl;

    // send notifications to router.
    while (m_tokens) {
	zmq_send(m_dealer, "", 0, ZMQ_SNDMORE);
	zmq_send(m_dealer, "", 0, 0);

        m_tokens--;
    }

    zmq_msg_t msg;
    zmq_msg_init(&msg);
    int sret;

    // tokens always zero in this point
    while ((sret = zmq_msg_recv(&msg, m_dealer, 0)) == -1) {
	if (errno == EAGAIN) {
	
	    //zmq_getsockopt(m_dealer, ZMQ_IDENTITY, id, &id_size);
	    std::cout << "Halt: " << ZMQ_IDENTITY << std::endl;
	    //return false;

	} else if (errno != EINTR) {
            return false;
        }

        m_eintr_count++;
    }

    m_tokens++;

    if (zmq_msg_size(&msg) == 0) {
        std::cout << "Total failures: " << m_eintr_count << std::endl;
        zmq_msg_close(&msg);
        return false;
    }

    m_callback->on_workload(static_cast<const char *>(zmq_msg_data(&msg)), zmq_msg_size(&msg));

    zmq_msg_close(&msg);

    return true;
}

void WorkerFlow::set_tokens(size_t tokens)
{
    m_tokens = tokens;
}

size_t WorkerFlow::get_tokens()
{
    return m_tokens;
}

std::string WorkerFlow::get_identity()
{
    return m_identity;
}
