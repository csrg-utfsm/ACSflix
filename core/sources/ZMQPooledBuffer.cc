//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#include "ZMQPooledBuffer.h"

void on_release(void * data, void * hint)
{
	BufferPoolElement * element = static_cast<BufferPoolElement*>(hint);
	assert(element->get_buffer().data() == data);
	element->release(); // Release buffer to be used in cache
}

ZMQPooledBuffer::ZMQPooledBuffer(BufferPoolElement * element) :
	ZMQBuffer(element->get_buffer().data(),
	          element->get_buffer().length()),
	m_element(element)
{
}

int ZMQPooledBuffer::init_data(zmq_msg_t *msg)
{
	return zmq_msg_init_data(msg,
	                         m_buffer,
	                         m_size,
	                         on_release,
	                         m_element);
}
