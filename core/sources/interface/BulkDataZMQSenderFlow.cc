//
// Created by Rodolfo Castillo Mateluna on 9/7/16.
//

#include "BulkDataZMQSenderFlow.h"

bdr::BulkDataZMQSenderFlow::BulkDataZMQSenderFlow(std::string name) :
		BulkDataZMQFlow(name),
        flowState(StartState)
{
}

void bdr::BulkDataZMQSenderFlow::startSend(const unsigned char *buffer, size_t len)
{

}

void bdr::BulkDataZMQSenderFlow::sendData(const unsigned char *buffer, size_t len)
{
}

void bdr::BulkDataZMQSenderFlow::stopSend()
{

}

