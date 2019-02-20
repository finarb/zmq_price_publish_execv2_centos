
/*****************************************/
/** FeedOS C++ Client API			 	**/
/**									 	**/
/** copyright QuantHouse 2005-2013		**/
/**										**/
/*****************************************/

#ifndef FEEDOS_API_RECOVERY_OBSERVER_H
#define FEEDOS_API_RECOVERY_OBSERVER_H

#include "../comm/multicast_definitions.h"

namespace FeedOS
{

/*! Interface to implement to be notified of recovery events:
 * - missing packets
 * - recovered packets (recovery successful)
 * - lost packets (recovery failed)
 */
class RecoveryObserver
{

public:
	virtual ~RecoveryObserver () { }

	virtual void missingPackets (int source_id,
								 Multicast_definitions::PredefinedServices channel_id,
								 unsigned int seq_num,
								 int nb_packets) = 0;

	virtual void recoveredPackets (int source_id,
								   Multicast_definitions::PredefinedServices channel_id,
								   unsigned int seq_num,
								   int nb_packets) = 0;

	virtual void lostPackets (int source_id,
							  Multicast_definitions::PredefinedServices channel_id,
							  unsigned int seq_num,
							  int nb_packets) = 0;
};

}

#endif
