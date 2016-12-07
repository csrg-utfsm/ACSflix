#include <ScopedRef.hpp>
#include <cstring>
#include "BytesSenderFlow.h"

BytesSenderFlow::BytesSenderFlow(const std::string &bind, int linger) :
		SenderFlow(bind, linger)
{
}

void BytesSenderFlow::send(const char *buffer, size_t size)
{
	ScopedRef<ZMQBuffer> zmq_buffer = m_buffer_factory->get_zbuffer(size);
	std::copy(buffer, buffer + size, zmq_buffer->buffer());

	zmq_msg_t msg;
	zmq_buffer->init_data(&msg);

	SenderFlow::send(&msg);
}
