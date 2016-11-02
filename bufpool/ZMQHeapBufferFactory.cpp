#include "ZMQHeapBufferFactory.h"

ZMQBuffer *ZMQHeapBufferFactory::get_zbuffer(size_t size)
{
	return new ZMQHeapBuffer(size);
}
