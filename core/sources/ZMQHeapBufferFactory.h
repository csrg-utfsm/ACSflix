//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#ifndef PUBLISHER_ZMQHEAPBUFFERFACTORY_H
#define PUBLISHER_ZMQHEAPBUFFERFACTORY_H


#include "ZMQBufferFactory.h"
#include "ZMQHeapBuffer.h"


class ZMQHeapBufferFactory : public ZMQBufferFactory
{
public:
	virtual ZMQBuffer * get_zbuffer(size_t size);
};


#endif //PUBLISHER_ZMQHEAPBUFFERFACTORY_H
