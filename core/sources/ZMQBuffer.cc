#include "ZMQBuffer.h"

ZMQBuffer::ZMQBuffer(char * buffer, size_t size) :
		m_buffer(buffer),
		m_size(size)
{
}

ZMQBuffer::~ZMQBuffer()
{
}

char * ZMQBuffer::buffer()
{
	return m_buffer;
}

size_t ZMQBuffer::size()
{
	return m_size;
}

void ZMQBuffer::size(size_t size)
{
	m_size = size;
}
