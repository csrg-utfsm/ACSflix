#include "Buffer.h"

Buffer::Buffer() :
		buffer(NULL),
		bsize(0),
        blength(0)
{
}

Buffer::Buffer(size_t size) :
		buffer(new char[size]),
		bsize(size),
        blength(size)
{
}

Buffer::Buffer(const Buffer &other) :
		//Buffer(other.size()) c++11
		buffer(new char[other.bsize]),
        bsize(other.bsize),
        blength(other.blength)
{
	std::copy(other.buffer, other.buffer + blength, buffer);
}

Buffer::~Buffer()
{
	delete[] buffer;
}

void swap(Buffer& first, Buffer& second)
{
	using std::swap;

	swap(first.buffer, second.buffer);
	swap(first.bsize, second.bsize);
	swap(first.blength, second.blength);
}

Buffer& Buffer::operator=(Buffer other)
{
	swap(*this, other);
	return *this;
}

size_t Buffer::size() const
{
	return bsize;
}

void Buffer::length(size_t len)
{
	blength = len;
}

size_t Buffer::length() const
{
	return blength;
}

char &Buffer::operator[](size_t i)
{
	return buffer[i];
}

Buffer::operator char *()
{
	return buffer;
}

char* Buffer::data() const
{
	return buffer;
}
