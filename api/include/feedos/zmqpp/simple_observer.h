
/************************************/
/** FeedOS sample client code      **/
/**                                **/
/** QuantHouse 2005                **/
/************************************/

#ifndef FEEDOS_SAMPLE_SIMPLE_OBSERVER_H
#define FEEDOS_SAMPLE_SIMPLE_OBSERVER_H

#include <feedos/api/ProxyServerObserver.h>

class SimpleObserver: public FeedOS::ProxyServerObserver
{
public:
	SimpleObserver();

	// inherited from FeedOS::ProxyServerObserver
	virtual void proxy_disconnected_hook		(FeedOS::ProxyServer & p);
	virtual void proxy_connected_hook			(FeedOS::ProxyServer & p);
	virtual void proxy_heartbeat_hook			(FeedOS::ProxyServer & p);
	virtual void proxy_normal_disconnect_hook	(FeedOS::ProxyServer & p);
	virtual void proxy_admin_message_hook		(FeedOS::ProxyServer & p);
		
};

#endif
