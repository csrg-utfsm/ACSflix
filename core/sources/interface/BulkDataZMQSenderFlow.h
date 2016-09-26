//
// Created by Rodolfo Castillo Mateluna on 9/7/16.
//

#ifndef PUBLISHER_BULKDATARSENDERFLOW_H
#define PUBLISHER_BULKDATARSENDERFLOW_H

#include "BulkDataZMQFlow.h"

namespace bdr
{
	class BulkDataZMQSenderFlow : public BulkDataZMQFlow
	{
	public:
		// temporal
		BulkDataZMQSenderFlow(std::string name);

		void startSend(const unsigned char* buffer, size_t len);

		void sendData(const unsigned char* buffer, size_t len);

		void stopSend();

	protected:
		enum SenderFlowState
		{
			StartState,
			DataRcvState,
			StopState,
			IgnoreDataState
		};

		SenderFlowState flowState;
	};
}

#endif //PUBLISHER_BULKDATARSENDERFLOW_H
