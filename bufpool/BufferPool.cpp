#include <iostream>
#include "BufferPool.h"

BufferPool::~BufferPool()
{
	std::vector<BufferPoolElement*>::iterator it;
	for (it = pool.begin(); it != pool.end(); it++) {
		delete *it;
	}
}

BufferPoolElement * BufferPool::get_and_retain(size_t size)
{
	std::vector<BufferPoolElement*>::iterator it;
	for (it = pool.begin(); it != pool.end(); it++) {
		if ((*it)->is_available() && (*it)->size() >= size) {
			(*it)->get_buffer().length(size);
			(*it)->retain(); // method is called get_and_RETAIN!
			return *it;
		}
	}

	// Create new buffer
	pool.push_back(new BufferPoolElement(size));
	pool.back()->retain();

	//std::cout << "NEW" << std::endl;

	return pool.back();
}