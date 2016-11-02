//
// Created by Rodolfo Castillo Mateluna on 10/18/16.
//

#ifndef BDT_ENGINE_FLOW_H
#define BDT_ENGINE_FLOW_H

#include <string>
#include <czmq.h>
#include "google/protobuf/message_lite.h"
#include "BufferPool.h"

class SenderFlow
{
private:
	zctx_t * context;

	void * router;

	BufferPool & pool;

	bool stopped;

	int stop_timeout;

	/**
	 * Sends a ZMQ message as is to any available worker.
	 *
	 * @param msg message to send.
	 */
	void send(zmq_msg_t * msg);

public:
	SenderFlow(std::string bind, BufferPool & pool, int linger = 10000);

	~SenderFlow();

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
