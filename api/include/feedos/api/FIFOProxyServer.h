
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2009      **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_FIFO_PROXY_SERVER_H
#define FEEDOS_API_FIFO_PROXY_SERVER_H

#ifndef FEEDOS_API_PROXY_SERVER_H
#	include "ProxyServer.h"
#endif

#ifndef TARGET_PLATFORM_WIN32

namespace FeedOS {

	class FIFOProxyServer:	public ProxyServer,
							protected Network::InitiatorFIFO
	{
	public:
		FIFOProxyServer (std::string const & name = "fifo_proxy_server");
		virtual ~FIFOProxyServer();
		// TODO: add "auto-reconnect" mode ?

		// blocking connect (with authentication)
		ReturnCode sync_connect (	std::string const & server_directory,
									std::string const & user,
									std::string const & password
								);

		void disconnect (); 

		bool is_connected() const { return ProxyServer::is_connected(); }

	private:
		// from FIFO => Proxy implementation
		virtual void disconnected_hook () { cleanup_and_reconnect_after_error ("disconnected", RC_DISCONNECTED); }

		// from FIFO => Proxy implementation
		virtual void receive_data (void const * p, unsigned int n) { Proxy::receive_data(p,n); }

		// from Proxy => FIFO implementation
		virtual ReturnCode send_data (void const * p, unsigned int n) { return Network::InitiatorFIFO::send_data(p,n) ? RC_ERROR:RC_OK; }

		// from ProxyServer
		virtual void set_disconnected_state_hook (ReturnCode rc);

		// from ProxyServer/Proxy
		virtual void handle_session_error (ReturnCode rc)		{ if (m_is_last_connection_attempt) cleanup_and_reconnect_after_error("session_error",rc); }
		virtual void handle_protocol_error (ReturnCode rc)		{ cleanup_and_reconnect_after_error("protocol_error",rc); }
		virtual void handle_transmission_error (ReturnCode rc)	{ cleanup_and_reconnect_after_error("transmission_error",rc); }

		// called by disconnected_hook() and handle_XXXX_error()
		virtual void cleanup_and_reconnect_after_error (char const * what, ReturnCode rc);

	private:
		bool	m_warn_if_connection_fails;	// used to issue a warning ONCE in case of connection error
	};


}

#endif

#endif

