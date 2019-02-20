
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_SIMPLE_PROXY_SERVER_H
#define FEEDOS_API_SIMPLE_PROXY_SERVER_H

#ifndef FEEDOS_API_PROXY_SERVER_H
#	include "ProxyServer.h"
#endif

namespace FeedOS {


	// a simple ProxyServer. It is "passive" regarding the underlying connection.
	// (relies on user to perform socket polling / message dispatching)
	class SimpleProxyServer: public FeedOS::ProxyServer
	{
	public:
		SimpleProxyServer ();
		~SimpleProxyServer ();

		// blocking connect (with authentication)
		// connect_timeout_in_ms=SYSTEM_DEFAULT_CONNECT_TIMEOUT means "use operating system value"
		ReturnCode sync_connect (	std::string const & server,
									unsigned int		port,
									std::string const & user,
									std::string const & password,
									unsigned int        connect_timeout_in_ms = SYSTEM_DEFAULT_CONNECT_TIMEOUT
								);

		// set as a side effect of 
		// - handle_protocol_error     -- called by receive_data()
		// - handle_session_error      -- called by receive_data()
		// - handle_transmission_error -- called by send_data()
		// - socket_disconnected
		bool error_occurred() const { return m_error_occurred; }

		SocketT	get_socket_handle() const { return m_socket; }

		// Calling whole socket polling/events dispatching

		// read and dispatch incoming messages until socket is disconnected
		ReturnCode	read_and_dispatch_events_forever ();



		// Building blocks for custom socket polling/events dispatching

		// blocking read (+timeout) of the socket. 
		// - on success: Calls read_socket, returns the number of messages that were successfully reassembled, possibly 0 if was interrupted
		// - on error: Calls socket_disconnected(), returns -1
		int select_and_read_socket (int read_timeout_millisec);

		// dispatch enqueued messages
		unsigned int	dispatch_pending_events() { return FeedOS::ProxyServer::dispatch_pending_events(); }

		// read data from the socket. 
		// - on success: calls receive_data(), returns the number of messages that were successfully reassembled-enqueued
		// - on error: Calls socket_disconnected(), returns -1
		int read_socket ();

		// call this to signal a network disconnection
		void socket_disconnected();

	protected:
		// in case of success, 0 is returned and "error_occurred" is set to false
		// connect_timeout_in_ms=SYSTEM_DEFAULT_CONNECT_TIMEOUT means "use operating system value"
		int tcp_connect (std::string const & server, unsigned int port, unsigned int connect_timeout_in_ms = SYSTEM_DEFAULT_CONNECT_TIMEOUT);

		// inherited from Proxy
		virtual FeedOS::ReturnCode send_data (void const * p, unsigned int n);
		virtual void handle_protocol_error		(FeedOS::ReturnCode rc);
		virtual void handle_transmission_error	(FeedOS::ReturnCode rc);

		// inherited ProxyServer/Proxy
		virtual void handle_session_error		(FeedOS::ReturnCode rc);

		// close the socket
		void tcp_disconnect ();

		// abort ongoing user requests, close the socket, raise "error_occurred"
		void cleanup_after_error (char const * what, FeedOS::ReturnCode rc);

		// from ProxyServer
		virtual void set_disconnected_state_hook (ReturnCode rc);

		// from ProxyServer
		virtual void	missing_heartbeat_condition ();

	private:
		SocketT						m_socket;
		volatile bool				m_error_occurred;
		volatile FeedOS::ReturnCode m_error_code;

		int 						m_socket_read_buffer_size;
		char						*m_socket_read_buffer;

		void close_socket();
	};


}



#endif
