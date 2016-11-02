//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#ifndef PUBLISHER_ZMQBUFFERFACTORY_H
#define PUBLISHER_ZMQBUFFERFACTORY_H


#include "ZMQBuffer.h"

class ZMQBufferFactory
{
public:
	virtual ~ZMQBufferFactory() {};

	virtual ZMQBuffer * get_zbuffer(size_t size) = 0;
};


#endif //PUBLISHER_ZMQBUFFERFACTORY_H
