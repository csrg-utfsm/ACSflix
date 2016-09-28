//
// Created by Rodolfo Castillo Mateluna on 9/27/16.
//

#include "BufferPoolElement.h"

BufferPoolElement::BufferPoolElement(size_t size) :
	buffer(size),
    available(true)
{
}

bool BufferPoolElement::is_available() const
{
	return available;
}

void BufferPoolElement::retain()
{
	available = false;
}

void BufferPoolElement::release()
{
	available = true;
}

Buffer &BufferPoolElement::get_buffer()
{
	return buffer;
}

size_t BufferPoolElement::size() const
{
	return buffer.size();
}
