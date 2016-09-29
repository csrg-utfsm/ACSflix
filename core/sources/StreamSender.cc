//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#include "StreamSender.h"

void simple_deleter(void * data, void * hint)
{
	char * buffer = (char *) data;
	delete[] buffer;
}

StreamSender::StreamSender(Sender & sender, std::istream & input_stream) :
	m_sender(sender),
	m_input_stream(input_stream),
	m_chunk_size(10000),
	m_buffer_factory(new ZMQHeapBufferFactory()),
    m_pool(nullptr)
{
}

StreamSender::~StreamSender()
{
	delete m_buffer_factory;
}

size_t StreamSender::chunk_size() const
{
	return m_chunk_size;
}

void StreamSender::chunk_size(size_t chunk_size)
{
	m_chunk_size = chunk_size;
}

void StreamSender::attach_buffer_pool(BufferPool &pool)
{
	m_buffer_factory = new ZMQPooledBufferFactory(pool);
}

void StreamSender::detach_buffer_pool()
{
	m_buffer_factory = new ZMQHeapBufferFactory();
}

bool StreamSender::send_chunk()
{
	if (m_input_stream.eof()) {
		return false;
	}

	ScopedRef<ZMQBuffer> zmq_buffer =
			m_buffer_factory->get_zbuffer(m_chunk_size);

	m_input_stream.read(zmq_buffer->buffer(),
	                    zmq_buffer->size());

	zmq_msg_t msg;
	zmq_buffer->init_data(&msg);

	m_sender.send(&msg);

	// Return if should keep calling this function
	return m_input_stream.gcount() == m_chunk_size;
}