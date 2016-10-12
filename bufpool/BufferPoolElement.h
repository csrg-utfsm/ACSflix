#ifndef PUBLISHER_BUFFERPOOLELEMENT_H
#define PUBLISHER_BUFFERPOOLELEMENT_H


#include "Buffer.h"

class BufferPoolElement
{
	bool available;
	Buffer buffer;

public:
	BufferPoolElement(size_t size);

	Buffer& get_buffer();
	size_t size() const;

	bool is_available() const;

	void retain();
	void release();
};


#endif //PUBLISHER_BUFFERPOOLELEMENT_H
