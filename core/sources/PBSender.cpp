//
// Created by Rodolfo Castillo Mateluna on 9/27/16.
//

#include  <iostream>
#include <cstdio>
#include "PBSender.h"

void on_buffer_release(void * data, void * hint)
{
	BufferPoolElement * element = static_cast<BufferPoolElement*>(hint);
	assert(element->get_buffer().data() == data);
	element->release(); // Release buffer to be used in cache
}

PBSender::PBSender(const std::string &bind, BufferPool& pool) :
		Sender(bind),
        pool(pool)
{
}

void PBSender::send(const google::protobuf::MessageLite &message)
{
	// Get buffer from pool
	BufferPoolElement * element =
			pool.get_and_retain((size_t) message.ByteSize());

	// Serialize message to buffer
	message.SerializeToArray(element->get_buffer().data(),
	                         (int) element->get_buffer().length());

	assert(message.IsInitialized());

	// Zero copy pool buffer
	zmq_msg_t msg;
	zmq_msg_init_data(&msg,
	                  element->get_buffer().data(),
	                  element->get_buffer().length(),
	                  on_buffer_release,
	                  element);

	Sender::send(&msg);
}
