
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_PDU_CONSUMER_H
#define FEEDOS_COMM_PDU_CONSUMER_H

#include <vector>
#include "PDU.h"

namespace FeedOS 
{
	// Interface class describing a bulk PDU consumer 
	class PDU_consumer
	{
	public:
		virtual ~PDU_consumer() {}

		// Consumes a range of PDU described by iterators
		virtual void consume_PDUs (std::vector< PDU >::const_iterator begin, std::vector< PDU >::const_iterator end) = 0;		
	};
}
#endif // FEEDOS_COMM_PDU_CONSUMER_H
