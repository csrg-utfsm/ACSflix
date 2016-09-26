//
// Created by Rodolfo Castillo Mateluna on 9/7/16.
//

#ifndef PUBLISHER_BULKDATAFLOW_H
#define PUBLISHER_BULKDATAFLOW_H

#include <string>

namespace bdr
{
	class BulkDataZMQFlow
	{
	public:
		BulkDataZMQFlow(std::string name);
		BulkDataZMQFlow(const char* name);

		virtual BulkDataZMQFlow();

		std::string getName() const;

	protected:
		std::string flowName;
	};
}



#endif //PUBLISHER_BULKDATAFLOW_H
