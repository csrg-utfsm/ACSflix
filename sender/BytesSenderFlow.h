#ifndef BDT_ENGINE_BYTESSENDER_H
#define BDT_ENGINE_BYTESSENDER_H


#include "SenderFlow.h"

// TODO: test
class BytesSenderFlow : public SenderFlow
{
public:
	BytesSenderFlow(const std::string &bind, int linger);

	void send(char * buffer, size_t size);
};


#endif //BDT_ENGINE_BYTESSENDER_H
