#ifndef BDT_ENGINE_BYTESSENDER_H
#define BDT_ENGINE_BYTESSENDER_H


#include "SenderFlow.h"

class BytesSender : public SenderFlow
{
public:
	BytesSender(const std::string &bind, int linger);

	void send(const char * buffer, size_t size);
};


#endif //BDT_ENGINE_BYTESSENDER_H
