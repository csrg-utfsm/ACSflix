#include <iostream>
#include <cassert>
#include "SenderFlow.h"

#include <cerrno>
#include <cstring>

SenderFlow::SenderFlow(std::string bind, int linger) :
		context(zctx_new()),
		router(zsocket_new(context, ZMQ_ROUTER)),
		stopped(false),
		stop_timeout(1000),
		m_buffer_factory(new ZMQHeapBufferFactory),
		m_eintr_count(0)
{
	zsocket_bind(router, bind.c_str());
	zctx_set_linger(context, linger);
	int timeout = 5000; // 5s
	zmq_setsockopt(router, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
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

	//char * identity = zstr_recv(router);
	char identity[256];
	int size;

	while ((size = zmq_recv(router, identity, 256, 0)) == -1) {
	    if (errno == EAGAIN) {
		std::cout << "Halt detected!" << std::endl;
		return;
		
	    } else if (errno != EINTR) {
		std::cout << strerror(errno) << "(" << errno << ")" << std::endl;
		assert(size != -1); // WILL FAIL!
	    }

	  m_eintr_count++;

	  /*if (m_eintr_count++ == 5) {
	    std::cout << "Tried too many times... Aborting!" << std::endl;
	    assert(size != -1);
	    }*/
	  //std::cout << "Trying again..." << std::endl;
	} 

	identity[size] = 0;

	//std::cout << identity << " " << std::endl;
	//std::cout << "size: " << size << std::endl;

#ifdef DEBUG
	std::cout << "Sending " << zmq_msg_size(msg)
              << " bytes to " << identity
              << std::endl;
#endif

	// ignore delimiter.
	char * ignore = zstr_recv(router);
    zstr_free(&ignore);

    // ignore worker content.
    ignore = zstr_recv(router);
    zstr_free(&ignore);

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

	std::cout << "Total failures: " << m_eintr_count << std::endl;

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
