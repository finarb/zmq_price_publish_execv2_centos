
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_TCP_PROXY_SERVER_H
#define FEEDOS_API_TCP_PROXY_SERVER_H

#ifndef FEEDOS_API_PROXY_SERVER_H
#	include "ProxyServer.h"
#endif

namespace FeedOS {

	class TCPProxyServer:	public ProxyServer,
							protected Network::InitiatorSocket
	{
	public:
		TCPProxyServer (std::string const & name = "tcp_proxy_server");
		virtual ~TCPProxyServer();

		// blocking connect (with authentication)
		// connect_timeout_in_ms=SYSTEM_DEFAULT_CONNECT_TIMEOUT means "use operating system value"
		ReturnCode sync_connect (	std::string const & server,
									unsigned int		port,
									std::string const & user,
									std::string const & password,
									unsigned int		connect_timeout_in_ms = SYSTEM_DEFAULT_CONNECT_TIMEOUT
								);

		void set_connection_parameters (	std::string const & server,
											unsigned int		port,
											std::string const & user,
											std::string const & password
										);

		// reconnect with previously-used parameters
		ReturnCode sync_reconnect();

		void disconnect (); 

		bool is_connected() const { return ProxyServer::is_connected(); }

	private:
		// from Socket => Proxy implementation
		virtual void disconnected_hook () { cleanup_and_reconnect_after_error ("disconnected", RC_DISCONNECTED); }

		// from Socket => Proxy implementation
		virtual void receive_data (void const * p, unsigned int n) { Proxy::receive_data(p,n); }

		// from Proxy => Socket implementation
		virtual ReturnCode send_data (void const * p, unsigned int n) { return Network::InitiatorSocket::send_data(p,n) ? RC_ERROR:RC_OK; }

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
		std::string	m_last_used_server_ip;
		int			m_last_used_server_port;
		std::string	m_last_used_server_user;
		std::string	m_last_used_server_password;
	};


}

#endif

