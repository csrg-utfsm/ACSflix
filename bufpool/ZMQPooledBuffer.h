#ifndef PUBLISHER_ZMQPOOLEDBUFFER_H
#define PUBLISHER_ZMQPOOLEDBUFFER_H


#include "ZMQBuffer.h"
#include <cassert>
#include "BufferPoolElement.h"

class ZMQPooledBuffer : public ZMQBuffer
{
	BufferPoolElement * m_element;

public:
	ZMQPooledBuffer(BufferPoolElement * element);

	virtual int init_data(zmq_msg_t *msg);
};


#endif //PUBLISHER_ZMQPOOLEDBUFFER_H
