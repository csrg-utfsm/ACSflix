#include "WorkerFlow.h"

WorkerFlow::WorkerFlow(std::string connect,
                       std::string identity,
                       WorkerFlowCallback * callback) :
	m_context(zctx_new()),
    m_dealer(zsocket_new(m_context, ZMQ_DEALER)),
    m_callback(callback),
    m_tokens(1),
    m_identity(identity)
{
  char * identity_cpy = strdup(identity.c_str());
	zsocket_set_identity(m_dealer, identity_cpy);
	zsocket_connect(m_dealer, connect.c_str());
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
	// send notifications to router.
	while (m_tokens) {
		zstr_send(m_dealer, "");
		m_tokens--;
	}

	zmq_msg_t msg;
	zmq_msg_init(&msg);
	zmq_msg_recv(&msg, m_dealer, 0);

    m_tokens++;

	if (zmq_msg_size(&msg) == 0) {
		zmq_msg_close(&msg);
		return false;
	}

	m_callback->on_workload(static_cast<const char*>(zmq_msg_data(&msg)),
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
