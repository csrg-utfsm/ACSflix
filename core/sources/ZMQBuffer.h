//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#ifndef PUBLISHER_ZMQBUFFER_H
#define PUBLISHER_ZMQBUFFER_H


#include <zmq.h>

class ZMQBuffer
{
protected:
	char * m_buffer;
	size_t m_size;

	ZMQBuffer(char *m_buffer, size_t m_size);

public:
	virtual ~ZMQBuffer();

	virtual int init_data(zmq_msg_t * msg) = 0;

	char * buffer();
	size_t size();
};

#endif //PUBLISHER_ZMQBUFFER_H
