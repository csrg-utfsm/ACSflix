#include <zmq.h>
#include <cstring>
#include "zmq_common.h"

#define STR_BUFSIZE 256

char *zcommon_str_recv(void *zmq_socket)
{
    char *buffer = new char[STR_BUFSIZE];
    int size = zmq_recv(zmq_socket,
			buffer,
			STR_BUFSIZE,
			0);

    if (size == -1) {
	delete[] buffer;
        return NULL;
    }
    if (size > 255) {
        size = 255;
    }
    
    buffer[size] = 0;
    return buffer;
}
