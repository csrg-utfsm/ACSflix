//
// Created by Rodolfo Castillo Mateluna on 9/29/16.
//

#include "ZMQHeapBufferFactory.h"

ZMQBuffer *ZMQHeapBufferFactory::get_zbuffer(size_t size)
{
	return new ZMQHeapBuffer(size);
}
