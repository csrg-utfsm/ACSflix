//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#include "ZMQPooledBufferFactory.h"
#include "ZMQPooledBuffer.h"

ZMQPooledBufferFactory::ZMQPooledBufferFactory(BufferPool &pool) :
	m_pool(pool)
{
}

ZMQBuffer *ZMQPooledBufferFactory::get_zbuffer(size_t size)
{
	return new ZMQPooledBuffer(m_pool.get_and_retain(size));
}
