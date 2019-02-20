
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2009 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_MULTICAST_FEED_H
#define FEEDOS_FRAMEWORK_MULTICAST_FEED_H

#ifndef FEEDOS_API_API_H
#  include "../api/api.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_FRAME_SPLITTER_H
#  include "../comm/MulticastFrameSplitter.h"
#endif

#ifndef FEEDOS_FEEDOBJECT_H
#  include "FeedObject.h"
#endif

namespace FeedOS {

class MulticastFeed : public FeedObject, public Network::MulticastReceiverSocket
{
	// class cannot be copied
	MulticastFeed const & operator=(MulticastFeed const &);
	MulticastFeed(MulticastFeed const &);
public:
	MulticastFeed(Network::SocketListener_ptr const & listener_ptr,	
						PDU_consumer & consumer,	
						std::string const & description,
						std::string const & group_ip, 
						unsigned int group_port, 
						std::string const & iface_local_ip = std::string()); 

	virtual ~MulticastFeed() {}

	virtual void get_counters (uint64 & bytes_recv, uint64 & datagram_recv) const;
	virtual void reset_counters ();
	virtual void set_observer(MsgDispatchingHooksBase *);

private:
	virtual bool	impl_start_object();
	virtual bool	impl_stop_object();

	// Override Socket::receive_data
	virtual void receive_data(void const * p, unsigned int n);

	MulticastFrameSplitter	m_splitter;
	std::string				m_address_ip;
	unsigned int			m_port;
	std::string				m_iface_local_ip;
};
}

#endif // FEEDOS_FRAMEWORK_MULTICAST_FEED_H
