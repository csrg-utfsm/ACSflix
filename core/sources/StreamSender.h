//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#ifndef PUBLISHER_STREAMSENDER_H
#define PUBLISHER_STREAMSENDER_H

#include <iostream>
#include "Sender.h"
#include "util/BufferPool.h"
#include "ZMQBufferFactory.h"
#include "ZMQHeapBufferFactory.h"
#include "ZMQPooledBufferFactory.h"
#include "util/ScopedRef.hh"

class StreamSender
{
	Sender & m_sender;
	std::istream & m_input_stream;
	size_t m_chunk_size;
	ZMQBufferFactory * m_buffer_factory;

	BufferPool * m_pool;

public:
	StreamSender(Sender & sender, std::istream& input_stream);
	~StreamSender();

	size_t chunk_size() const;
	void chunk_size(size_t chunk_size);

	void attach_buffer_pool(BufferPool& pool);
	void detach_buffer_pool();

	bool send_chunk();
};


#endif //PUBLISHER_STREAMSENDER_H
