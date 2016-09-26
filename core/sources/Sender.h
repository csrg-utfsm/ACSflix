#ifndef PUBLISHER_SENDER_H
#define PUBLISHER_SENDER_H

#include <string>
#include <czmq.h>

class Sender
{
private:
    zctx_t * context;
    void * router;

public:
    Sender(std::string bind);

    ~Sender();

    void send(unsigned char * data, size_t length);
};

#endif //PUBLISHER_SENDER_H
