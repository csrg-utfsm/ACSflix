#ifndef BDT_ENGINE_FLOW_H
#define BDT_ENGINE_FLOW_H

#include <string>
#include <ZMQBufferFactory.h>
#include <ZMQHeapBufferFactory.h>
#include <ZMQPooledBufferFactory.h>
#include <zmq.h>
#include <zmq_common.h>
#include "google/protobuf/message_lite.h"
#include "BufferPool.h"

class SenderFlow
{
private:
	void * context;

	void * router;

	bool stopped;

	int stop_timeout;

	int m_eintr_count;

protected:
	ZMQBufferFactory * m_buffer_factory;

	/**
	 * Sends a ZMQ message as is to any available worker.
	 *
	 * @param msg message to send.
	 */
	void send(char * buffer, size_t size);

public:
	SenderFlow(std::string bind, int linger = 10000);

	~SenderFlow();

	void attach_buffer_pool(BufferPool & pool);

	void detach_buffer_pool();

	/**
	 * Stops sender and all workers, this is a blocking operation.
	 */
	void stop();

	/**
	 * Sets the amount of time to wait until all workers are stopped.
	 * Refeer to the StopMechanics document to read more about this.
	 *
	 * @param stop_timeout time until all workers are considered closed.
	 */
	void set_stop_timeout(int stop_timeout);
};


#endif //BDT_ENGINE_FLOW_H
