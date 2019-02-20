
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_PROXY_SERVER_OBSERVER_H
#define FEEDOS_API_PROXY_SERVER_OBSERVER_H

#ifndef FEEDOS_API_PROXY_SERVER_H
#  include "ProxyServer.h"
#endif

namespace FeedOS {

	/**
	 * Adaptor class that defines hook on various signals emitted by a ProxyServer
	 */
	class ProxyServerObserver
	{
	public:
		virtual ~ProxyServerObserver() {}

		virtual void proxy_state_changed_hook		(ProxyServer & ) {}
		virtual void proxy_disconnected_hook		(ProxyServer & ) {}
		virtual void proxy_connected_hook			(ProxyServer & ) {}
		virtual void proxy_heartbeat_hook			(ProxyServer & ) {}
		virtual void proxy_normal_disconnect_hook	(ProxyServer & ) {}
		virtual void proxy_admin_message_hook		(ProxyServer & ) {}
		
	};

}

#endif

