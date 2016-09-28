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

    virtual ~Sender();

    void send(unsigned char * data, size_t length);
	void send(zmq_msg_t * msg);

	/**
	* Sets ZMQ_LINGER to -1 (infinite wait before shutting down)
	*/
	void join();

};

#endif //PUBLISHER_SENDER_H
