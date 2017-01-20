#include <ScopedRef.hpp>
#include <cstring>
#include "BytesSenderFlow.h"

BytesSenderFlow::BytesSenderFlow(const std::string &bind, int linger) :
		SenderFlow(bind, linger)
{
}

void BytesSenderFlow::send(char * buffer, size_t size)
{
	SenderFlow::send(buffer, size);
}
