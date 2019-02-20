
/*****************************************/
/** FeedOS C++ Client API			 	**/
/**									 	**/
/** copyright QuantHouse 2005-2009		**/
/**										**/
/*****************************************/

#ifndef FEEDOS_FRAMEWORK_SHAREDMEMORY_FEED_H
#define FEEDOS_FRAMEWORK_SHAREDMEMORY_FEED_H

#ifndef FEEDOS_API_API_H
#  include "../api/api.h"
#endif

#ifndef FEEDOS_FEEDOBJECT_H
#  include "FeedObject.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_DEFINITIONS_H
#	include "../comm/multicast_definitions.h"
#endif

#ifndef TARGET_PLATFORM_WIN32

namespace FeedOS
{

class MsgDispatchingHooksBase;
class PDU_consumer;

class SharedMemoryFeed : public FeedObject, public Network::SharedMemoryReceiver
{
	SharedMemoryFeed & operator=(SharedMemoryFeed const &);
	SharedMemoryFeed(SharedMemoryFeed const &);
public:
	SharedMemoryFeed(PDU_consumer & consumer,	
					 Multicast_definitions::PredefinedServices channel,
					 int server_id);

	virtual void get_counters (uint64 & bytes_recv, uint64 & datagram_recv) const;
	virtual void reset_counters ();
	virtual void set_observer(MsgDispatchingHooksBase *o) { m_observer = o; }

private:
	virtual bool	impl_start_object();
	virtual bool	impl_stop_object();

	// Override Socket::receive_data
	virtual void receive_data(void const * p, unsigned int n);

	PDU_consumer&			m_target;
	MsgDispatchingHooksBase *m_observer;
};
}

#endif

#endif // FEEDOS_FRAMEWORK_SHAREDMEMORY_FEED_H
