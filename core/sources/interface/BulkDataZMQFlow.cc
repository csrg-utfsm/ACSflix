//
// Created by Rodolfo Castillo Mateluna on 9/7/16.
//

#include "BulkDataZMQFlow.h"

bdr::BulkDataZMQFlow::BulkDataZMQFlow(std::string name) :
	flowName(name)
{
}

bdr::BulkDataZMQFlow::BulkDataZMQFlow(const char *name) :
	flowName(name)
{
}

bdr::BulkDataZMQFlow::BulkDataZMQFlow()
{
}

std::string bdr::BulkDataZMQFlow::getName() const
{
	return flowName;
}



