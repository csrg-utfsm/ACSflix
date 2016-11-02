#ifndef PUBLISHER_ZMQHEAPBUFFER_H
#define PUBLISHER_ZMQHEAPBUFFER_H


#include "ZMQBuffer.h"

class ZMQHeapBuffer : public ZMQBuffer
{
public:
	ZMQHeapBuffer(size_t size);

	virtual int init_data(zmq_msg_t *msg);
};


#endif //PUBLISHER_ZMQHEAPBUFFER_H
