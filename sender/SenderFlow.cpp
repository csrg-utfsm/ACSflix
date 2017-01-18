#include <iostream>
#include <cassert>
#include "SenderFlow.h"

#include <cerrno>
#include <cstring>

SenderFlow::SenderFlow(std::string bind, int linger) :
    context(zmq_ctx_new()),
    router(zmq_socket(context, ZMQ_ROUTER)),
    stopped(false),
    stop_timeout(1000),
    m_buffer_factory(new ZMQHeapBufferFactory),
    m_eintr_count(0)
{
    //zsocket_bind(router, bind.c_str());
    zmq_bind(router, bind.c_str());
    zmq_setsockopt(router, ZMQ_LINGER, &linger, sizeof(linger));
    int timeout = 5000; // 5s
    zmq_setsockopt(router, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
}


SenderFlow::~SenderFlow()
{
    zmq_ctx_destroy(context);
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
    size_t sent;

    while ((size = zmq_recv(router, identity, 256, 0)) == -1) {
	if (errno == EAGAIN) {
	    std::cout << "Halt detected: " << identity << std::endl;
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

//#ifdef DEBUG
    std::cout << "Sending " << zmq_msg_size(msg)  << " bytes to " << identity << std::endl;
    sent += zmq_msg_size(msg);
    printf("Total Sent %zu Bytes \n",sent);

//#endif

    // ignore delimiter.
    char * ignore = zcommon_str_recv(router);
    delete[] ignore;

    // ignore worker content.
    ignore = zcommon_str_recv(router);
    delete[] ignore;

    // send message with an identity frame and content frame.
    int identity_len = size - 1;
    zmq_send(router, identity, identity_len, ZMQ_SNDMORE); // zstr_sendm(router, identity);
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
	//char * identity = zstr_recv(router);
	char * identity = zcommon_str_recv(router);

	if (identity == NULL) {
	    break;
	}

	zmq_send(router, identity, strlen(identity), ZMQ_SNDMORE); //zstr_sendm(router, identity);

	// This is valid (tested)
	zmq_send(router, "", 0, 0); //zstr_send(router, "");

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
