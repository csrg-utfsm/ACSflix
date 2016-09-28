//
// Created by Rodolfo Castillo Mateluna on 9/27/16.
//

#ifndef PUBLISHER_BUFFERPOOL_H
#define PUBLISHER_BUFFERPOOL_H

#include <vector> // is it the best option?
#include <zmq.h>
#include <czmq.h>
#include "BufferPoolElement.h"
#include <cstring>
#include <cassert>
#include <google/protobuf/message_lite.h>

class BufferPool
{
	std::vector<BufferPoolElement*> pool;

public:
	~BufferPool();

	BufferPoolElement * get_and_retain(size_t size);
};


#endif //PUBLISHER_BUFFERPOOL_H
