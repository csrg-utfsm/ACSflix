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
        m_context(zctx_new()),
        m_dealer(zsocket_new(m_context, ZMQ_DEALER)),
        m_callback(callback),
        m_tokens(1),
        m_identity(identity),
        m_eintr_count(0)
{
    gen_uuid(m_identity_uuid);
    //char * identity_cpy = strdup(identity.c_str());
    zsocket_set_identity(m_dealer, m_identity_uuid);
    zsocket_connect(m_dealer, connect.c_str());

    int timeout = 5000; // 5s
    zmq_setsockopt(m_dealer, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
}

WorkerFlow::~WorkerFlow()
{
    zctx_destroy(&m_context);
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
        zstr_sendm(m_dealer, "");
        zstr_send(m_dealer, "T");

        m_tokens--;
    }

    zmq_msg_t msg;
    zmq_msg_init(&msg);
    int sret;

    while ((sret = zmq_msg_recv(&msg, m_dealer, 0)) == -1) {
	if (errno == EAGAIN) {
	    std:cout << "Halt detected!" << std::endl;
	    return;
	    
	} else if (errno != EINTR) {
            return false;
        }

	// Change identity
	gen_uuid(m_identity_uuid);
	zmq_setsockopt(m_dealer, ZMQ_IDENTITY, m_identity_uuid, sizeof(m_identity_uuid));

        m_eintr_count++;

        /*if (m_eintr_count++ == 5) {
          std::cout << "Tried too many times... Aborting!" << std::endl;
          return false;
          }*/
        //std::cout << "Trying again... " << std::endl;
    }

    //assert(sret == zmq_msg_size(&msg));
    //std::cout << "sret: " << sret << std::endl;
    //std::cout << "zmsize: " << zmq_msg_size(&msg) << std::endl;

    m_tokens++;

    if (zmq_msg_size(&msg) == 0) {
        std::cout << "Total failures: " << m_eintr_count << std::endl;
        zmq_msg_close(&msg);
        return false;
    }

    m_callback->on_workload(static_cast<const char *>(zmq_msg_data(&msg)),
            zmq_msg_size(&msg));

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
