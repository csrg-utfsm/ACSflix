//
// Created by Rodolfo Castillo Mateluna on 9/27/16.
//

#ifndef PUBLISHER_PBSENDER_HH
#define PUBLISHER_PBSENDER_HH

#include "Sender.h"
#include "util/BufferPool.h"
#include <google/protobuf/message_lite.h>

class PBSender : public Sender
{
	BufferPool& pool;

public:
	PBSender(const std::string &bind, BufferPool& pool);

	void send(const google::protobuf::MessageLite& message);
};


#endif //PUBLISHER_PBSENDER_HH
