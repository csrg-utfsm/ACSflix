#include "ZMQHeapBuffer.h"

void on_free(void * data, void * hint)
{
	char * buffer = (char *) data;
	delete[] buffer;
}

ZMQHeapBuffer::ZMQHeapBuffer(size_t size) :
	ZMQBuffer(new char[size], size)
{
}

int ZMQHeapBuffer::init_data(zmq_msg_t *msg)
{
	return zmq_msg_init_data(msg,
	                         m_buffer,
	                         m_size,
	                         on_free,
	                         NULL);
}
