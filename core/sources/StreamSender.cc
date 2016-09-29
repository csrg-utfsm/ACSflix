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
	delete m_buffer_factory;
	m_buffer_factory = new ZMQPooledBufferFactory(pool);
}

void StreamSender::detach_buffer_pool()
{
	delete m_buffer_factory;
	m_buffer_factory = new ZMQHeapBufferFactory();
}

bool StreamSender::send_chunk()
{
	// Do not allow this call if eof was caught
	if (m_input_stream.eof()) {
		return false;
	}

	// Get ZMQBuffer
	ScopedRef<ZMQBuffer> zmq_buffer =
			m_buffer_factory->get_zbuffer(m_chunk_size);

	// Read chunk
	m_input_stream.read(zmq_buffer->buffer(),
	                    zmq_buffer->size());

	// Set size as actual read size
	zmq_buffer->size((size_t) m_input_stream.gcount());

	// Init zmq_msg
	zmq_msg_t msg;
	zmq_buffer->init_data(&msg);

	// Send zmq_msg with low level call
	m_sender.send(&msg);

	// Return if should keep calling this function
	return m_input_stream.gcount() == m_chunk_size;
}