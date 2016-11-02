//
// Created by Rodolfo Castillo Mateluna on 10/18/16.
//

#include <iostream>
#include <cassert>
#include "SenderFlow.h"


void on_buffer_release(void * data, void * hint)
{
	BufferPoolElement * element = static_cast<BufferPoolElement*>(hint);
	assert(element->get_buffer().data() == data);
	element->release(); // Release buffer to be used in cache
}


SenderFlow::SenderFlow(std::string bind, int linger) :
		context(zctx_new()),
		router(zsocket_new(context, ZMQ_ROUTER)),
		stopped(false),
		stop_timeout(1000),
        m_buffer_factory(new ZMQHeapBufferFactory)
{
	zsocket_bind(router, bind.c_str());

	// infinite wait before shutting down.
	// TODO: consider a timeout.
	zctx_set_linger(context, linger);
}


SenderFlow::~SenderFlow()
{
	zctx_destroy(&context);
	delete m_buffer_factory;
}


void SenderFlow::send(zmq_msg_t * msg)
{
	assert(!stopped);
	
#ifdef DEBUG
	std::cout << "Waiting for worker..." << std::endl;
#endif

	char * identity = zstr_recv(router);

#ifdef DEBUG
	std::cout << "Sending " << zmq_msg_size(msg)
              << " bytes to " << identity
              << std::endl;
#endif

	// ignore content.
	zstr_recv(router);

	// send message with an identity frame and content frame.
	zstr_sendm(router, identity);
	zmq_msg_send(msg, router, 0);
}

void SenderFlow::stop()
{
#ifdef DEBUG
	std::cout << "Stop invoked" << std::endl;
#endif

	stopped = true;

	int timeout = 1000;
	zmq_setsockopt(router, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));

	while (1) {
		char * identity = zstr_recv(router);

		if (identity == NULL) {
			break;
		}

		zstr_sendm(router, identity);
		zstr_send(router, "");

#ifdef DEBUG
		std::cout << "Stopped a worker" << std::endl;
#endif
	}

#ifdef DEBUG
	std::cout << "Done" << std::endl;
#endif
}

void SenderFlow::set_stop_timeout(int stop_timeout)
{
	this->stop_timeout = stop_timeout;
}

void SenderFlow::attach_buffer_pool(BufferPool &pool)
{
	delete m_buffer_factory;
	m_buffer_factory = new ZMQPooledBufferFactory(pool);
}

void SenderFlow::detach_buffer_pool()
{
	delete m_buffer_factory;
	m_buffer_factory = new ZMQHeapBufferFactory();
}

void SenderFlow::detach_buffer_pool()
{

}
