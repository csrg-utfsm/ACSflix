//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#ifndef PUBLISHER_ZMQPOOLEDBUFFERFACTORY_H
#define PUBLISHER_ZMQPOOLEDBUFFERFACTORY_H


#include "ZMQBufferFactory.h"
#include "../../../Downloads/ACSflix-lbimpl/core/sources/util/BufferPool.h"

class ZMQPooledBufferFactory : public ZMQBufferFactory
{
	BufferPool & m_pool;

public:
	ZMQPooledBufferFactory(BufferPool & pool);

	virtual ZMQBuffer *get_zbuffer(size_t size);
};


#endif //PUBLISHER_ZMQPOOLEDBUFFERFACTORY_H