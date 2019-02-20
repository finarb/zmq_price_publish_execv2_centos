
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_NETWORK_H
#define FEEDOS_BASE_NETWORK_H

#ifndef FEEDOS_BASE_OBJECT_H
#  include "Object.h"
#endif

#ifndef FEEDOS_BASE_SMART_PTR_H
#  include "smart_ptr.h"
#endif

#ifdef TARGET_PLATFORM_WIN32
#  include <Winsock2.h>
#else
#  include <netinet/in.h>
#endif

#include <limits.h>

#define FEEDOS_BASE_NETWORK_ENABLE_COMPLETOR_SOCKETS	0

#ifndef TARGET_PLATFORM_WIN32
#ifndef FEEDOS_IPCSHAREDMEMORY_OPTIONS_H
#  include "IPCSharedMemoryOptions.h"
#endif
#endif

namespace FeedOS {

	static unsigned const SYSTEM_DEFAULT_CONNECT_TIMEOUT = UINT_MAX;

#if defined TARGET_PLATFORM_WIN32
	typedef SOCKET	SocketT;	
#else
	typedef int		SocketT;
	class IPCSharedMemReader;
#endif

#if (__GLIBC__ == 2 && __GLIBC_MINOR__ <= 10)
#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
// https://sourceware.org/bugzilla/show_bug.cgi?id=12194
#define GLIBC_IGNORE_CONV_NTOHS_ERROR
#endif
#endif

#ifdef GLIBC_IGNORE_CONV_NTOHS_ERROR
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

	/** @name byte_ordering
	 *
	 * network<=>host conversion functions for basic types
	 */

	//@{

	inline uint32 ntoh_uint32(uint32 v) { return ntohl(v); }
	inline uint32 hton_uint32(uint32 v) { return htonl(v); }
	inline uint16 ntoh_uint16(uint16 v) { return ntohs(v); }
	inline uint16 hton_uint16(uint16 v) { return htons(v); }
	inline uint8  ntoh_uint8 (uint8  v) { return v; }
	inline uint8  hton_uint8 (uint8  v) { return v; }

	inline int32 ntoh_int32(int32 v) { return ntohl(v); }
	inline int32 hton_int32(int32 v) { return htonl(v); }
	inline int16 ntoh_int16(int16 v) { return ntohs(v); }
	inline int16 hton_int16(int16 v) { return htons(v); }
	inline int8  ntoh_int8 (int8  v) { return v; }
	inline int8  hton_int8 (int8  v) { return v; }
	inline char  ntoh_char (char  v) { return v; }
	inline char  hton_char (char  v) { return v; }

#ifdef GLIBC_IGNORE_CONV_NTOHS_ERROR
#pragma GCC diagnostic pop
#endif

#if FEEDOS_BIG_ENDIAN
	inline uint64 ntoh_uint64(uint64 v) { return v; }
	inline uint64 hton_uint64(uint64 v) { return v; }
	inline int64  ntoh_int64 (int64 v)  { return v; }
	inline int64  hton_int64 (int64 v)  { return v; }
	inline float32 ntoh_float32(float32 v) { return v; }
	inline float32 hton_float32(float32 v) { return v; }
	inline float64 ntoh_float64(float64 v) { return v; }
	inline float64 hton_float64(float64 v) { return v; }

#else

	inline uint64 byte_swap_uint64 (uint64 v)
	{
		return ( ((uint64)ntoh_uint32((uint32)v)) << 32) | (uint64) ntoh_uint32((uint32) (v>>32));
	}

	inline uint64 hton_uint64 (uint64 v) { return byte_swap_uint64(v); }
	inline uint64 ntoh_uint64 (uint64 v) { return byte_swap_uint64(v); }
	inline int64  hton_int64  (int64 v)  { return (int64) byte_swap_uint64((int64)v); }
	inline int64  ntoh_int64  (int64 v)  { return (int64) byte_swap_uint64((int64)v); }
	inline float64 hton_float64 (float64 v)  { uint64 tmp; *((float64*)(&tmp))=v; tmp=byte_swap_uint64(tmp); return *((float64*)(&tmp)); }
	inline float64 ntoh_float64 (float64 v)  { return hton_float64(v); }
	inline float32 hton_float32 (float32 v)  { uint32 tmp; *((float32*)(&tmp))=v; tmp=hton_uint32(tmp); return *((float32*)(&tmp)); }
	inline float32 ntoh_float32 (float32 v)  { return hton_float32(v); }

#endif

	//@}



	/// interface to implement network support
	class Network
	{
		static void init_impl();
		static void shutdown_impl();
	public:

		/** @name called by init() stuff */
		//@{
		static void init ();
		static void shutdown ();
		//@}

		// string versions of return codes
		typedef unsigned int ReturnCode;
		static char const * rc2string (ReturnCode rc);


		/** @return hostname of the machine */
		static std::string gethostname ();


		/// base class acting as a container for implementation-specific data
		class ImplElement
		{
		public:

			class AbstractImplData
			{
			public:
				virtual ~AbstractImplData () {}
			};
			inline ImplElement (AbstractImplData * impl_data) : m_impl_data (impl_data) {}

			/// delete any implementation-specific data previously associated to this object
			virtual ~ImplElement () { if (m_impl_data) delete m_impl_data; }

			inline AbstractImplData *	get_impl_data () const { return m_impl_data; }
			inline void set_impl_data (AbstractImplData * data) { m_impl_data=data; }

		private:
			AbstractImplData * m_impl_data; 
		};


		/// modelise a network socket: derive this and define pure virtual functions
		class Socket : public ImplElement
		{
		public:
			Socket (char const * name, AbstractImplData * impl_data);

			virtual ~Socket () { disconnect(); }

			virtual bool is_connectionless() const =0;

			// "is connected" condition
			bool is_connected() const { return m_is_connected; }

			// read data sent by the remote side
			virtual void receive_data	(void const * /*p*/, unsigned int /*n*/) {}

			char const *			description() const { return m_description.c_str(); }
			std::string const &		socket_name() const { return m_name; }

			// send data to the remote side
		protected:
			ReturnCode	send_data_impl	(void const * p, unsigned int n);

		public:
			/// derived classes use this to send a packet 
			ReturnCode	send_data		(void const * p, unsigned int n)
			{
				return send_data_impl (p,n);
			}

			void set_is_connected (bool is_connected);

			// call this to close the connection
			void disconnect ()
			{
				if (is_connected()) {
					disconnect_impl ();
					set_is_connected (false);
				}
			}

			// called when the remote side terminates the connection
			virtual void disconnected_hook () {}

 			unsigned int   get_local_port()  const { return m_local_port; }
 			unsigned int   get_remote_port() const { return m_remote_port; }
 			const std::string & get_remote_ip()   const { return m_remote_ip; }

			static void safe_setsockopt_bigint_value (std::string const & socket_name, FeedOS::SocketT s, int area, int option, int requested_value, char const * optname);

			typedef struct sockaddr_in	TDataOriginAddr;
			TDataOriginAddr				dataOriginAddr;
		protected:
			void safe_setsockopt_bigint_value (FeedOS::SocketT s, int area, int option, int requested_value, char const * optname) const
			{
				safe_setsockopt_bigint_value (socket_name(), s, area, option, requested_value, optname);
			}

			virtual void disconnect_impl ();

			void set_local_port(unsigned int p) { m_local_port=p; }
			void set_remote_port(unsigned int p) { m_remote_port=p; }
			void set_remote_ip	(std::string const & ip) { m_remote_ip=ip; }


			void perform_disconnect () { Socket::disconnect(); } // TODO remove this when we get rid of VC++ (see NetworkProxyServer)
			bool			m_is_connected;
		
		private:
			void rebuild_description();

			unsigned int	m_local_port;
			unsigned int	m_remote_port;
			std::string		m_remote_ip;
			std::string		m_name;
			std::string		m_description;
		};

		/**
		 * SocketProcessorThread
		 *
		 * Quick and dirty implementation of a thread that handles several sockets
		 */
		class SocketProcessorThread: public StartableObject
		{
			typedef SocketProcessorThread Me;
		public:
			/// CPUMode
			enum CPUMode
			{
				CPUMode_Normal,
				NbCPUModes
			};

		public:
			SocketProcessorThread(	std::string const & class_name, 
									std::string const & name,
									unsigned int thread_priority = 2,
									CPUMode cpu_mode = CPUMode_Normal,
									unsigned int cpu_number = 0);

			~SocketProcessorThread();

			//std::string	description() const;
			// inherited from StartableObject
			virtual bool	impl_start_object();
			virtual bool	impl_stop_object();
			// Inherited from Object
			virtual std::string		get_object_description () const;

			bool	attachSocket(FeedOS::SocketT handle, Socket & socket);
			bool	detachSocket(FeedOS::SocketT handle);

			void	disable_auto_update_description();

		protected:
			/// SocketEntry
			class SocketEntry
			{
			public:
				SocketEntry(FeedOS::SocketT handle, Socket & socket)
					: m_Handle(handle)
					, m_Socket(&socket)
				{
				}

				FeedOS::SocketT		getHandle() const			{ return m_Handle; }
				Socket &	getSocket() const			{ return *m_Socket; }

			private:
				FeedOS::SocketT		m_Handle;
				Socket *	m_Socket;
			};

			std::string const &	getCPUModeString(CPUMode cpu_mode) const;

			void perform_tick() const;

			std::vector<SocketEntry>	m_Sockets;
			ExclusiveLock				m_SocketsLock;

			// m_SocketsLock must be locked to call this method
			void updateSocketsDescription_nolock();

		private:
			virtual void select_and_dispatch_loop_impl (LockedBool const & should_terminate) = 0;

		private:
			CPUMode const				m_CPUMode;
			unsigned int const			m_CPUNumber;

			volatile bool				m_IsRunning;
			bool						m_auto_update_description;

			std::string					m_SocketsDescription;
			ExclusiveLock				m_SocketsDescriptionLock;

			void*		m_thread;
		};

		/**
		 * SocketListener handling a select and dispatch loop in a dedicated thread
		 */
		class SocketListener :	public SocketProcessorThread,
								public reference_counter
		{
			typedef SocketListener Me;
		public:
			SocketListener(	std::string const & instance_name,
							unsigned int thread_priority = 2,
							CPUMode cpu_mode = CPUMode_Normal,
							unsigned int cpu_number = 0);

		private:
			void select_and_dispatch_loop_impl (LockedBool const & should_terminate);

		};
		typedef smart_ptr2<SocketListener>	SocketListener_ptr;


		/// modelise a socket that handles data from a multicast group
		class MulticastSocket: public Socket
		{
		public:
			MulticastSocket (std::string const & description);
			~MulticastSocket ();

			bool is_connectionless() const	{ return true; }

			/*
			std::string const & get_description () const { return m_description; }
			*/
		protected:
			ReturnCode		send_data_impl	(void const * p, unsigned int n);
			virtual void	disconnect_impl	();

			// call this from receive_data() to query the origin of the incoming data
			void get_data_origin (std::string & origin_ip, int & origin_port) const;

		private:
			bool setup_impl(std::string const & description);
			void cleanup_impl();

			/* Duplication of Socket member -> useless
		private:
			std::string	m_description;
			*/
		};
		
		/// A multicast receiver class communicating with an externl listener.
		class MulticastReceiverSocket : public MulticastSocket
		{
			typedef MulticastReceiverSocket Me;
		public:
			MulticastReceiverSocket (std::string const & description, SocketListener_ptr const & listener_ptr);
			~MulticastReceiverSocket ();

			ReturnCode join_group (std::string const & group_ip, unsigned int group_port, std::string const & iface_local_ip = std::string());

			void get_counters (uint64 & bytes_recv, uint64 & datagram_recv) const
			{
				bytes_recv = m_counters_bytes_received;
				datagram_recv = m_counters_datagram_received;
			}

			void reset_counters ()
			{
				m_counters_bytes_received=0;
				m_counters_datagram_received=0;
			}

		protected:
			bool	setListener(SocketListener_ptr const & listener_ptr);
			SocketListener_ptr	getListener() const	{ return m_ListenerPtr; }

			void inc_bytes_received (unsigned int n)
			{
				m_counters_bytes_received += n;
				++m_counters_datagram_received;
			}

		private:
			virtual void	disconnect_impl	();
			ReturnCode		join_group_impl (std::string const & group_ip, unsigned int group_port, std::string const & iface_local_ip);

		private:
			bool				m_is_joined;
			SocketListener_ptr	m_ListenerPtr;
			std::string			m_IfaceLocalIp;
			uint64				m_counters_bytes_received;
			uint64				m_counters_datagram_received;
		};

		/// modelise a socket that initiates connection to a remote server
		class InitiatorSocket : public Socket
		{
			typedef InitiatorSocket Me;
		public:
			InitiatorSocket (char const * name);
			~InitiatorSocket ();

			// connect to a remote server (synchronous, one-attempt version)
			// connect_timeout_in_ms=SYSTEM_DEFAULT_CONNECT_TIMEOUT means "use operating system value"
			ReturnCode connect_to (std::string const & server_ip, unsigned int server_port, unsigned int connect_timeout_in_ms = SYSTEM_DEFAULT_CONNECT_TIMEOUT);

			//  0  means "set default API value"
			//  -1 means "keep default OS value"
			//  anything else: try to apply the given value (may fail due to Operating System configuration)
			static void setsockopt_global_value_RECV_buffer_size_bytes	(int v);
			static void setsockopt_global_value_SEND_buffer_size_bytes	(int v);

			//  default value for TCP_NODELAY is FALSE
			static void setsockopt_global_value_TCP_NODELAY_enabled		(bool v);

			static void setsockopt_initiator_socket (std::string const & socket_name, FeedOS::SocketT s);

			static int connect_socket (SocketT & socket, struct sockaddr_in * ServerAddr, const std::string &  server_ip, unsigned int server_port, unsigned int connect_timeout_in_ms);
		private:
			void setsockopt_initiator_socket (FeedOS::SocketT s) const { setsockopt_initiator_socket (socket_name(), s); }

			// Overriden from Network Socket 
			virtual bool is_connectionless() const	{ return false; }
			virtual void disconnect_impl ();

			ReturnCode connect_to_impl (std::string const &  server_ip, unsigned int server_port, unsigned int connect_timeout_in_ms = SYSTEM_DEFAULT_CONNECT_TIMEOUT);

			void listen_and_dispatch_loop_impl (LockedBool const & should_terminate);
			void listener_thread_wait_until_unblocked ();
			void listener_thread_block ();
			void listener_thread_unblock ();
			void listener_thread_run (LockedBool const & should_terminate);
			void listener_thread_stop ();
			void *						m_listener_thread;
			bool						m_listener_thread_blocked;
			ConditionalVariable			m_listener_thread_lock;

			static int	s_global_socket_RECV_buffer_size_bytes;
			static int	s_global_socket_SEND_buffer_size_bytes;
			static bool	s_global_socket_TCP_NODELAY_enabled;
		public:
			static void get_global_socket_values (int & RECV_buffer_size_bytes, int & SEND_buffer_size_bytes, bool & TCP_NODELAY_enabled)
			{
				RECV_buffer_size_bytes = s_global_socket_RECV_buffer_size_bytes;
				SEND_buffer_size_bytes = s_global_socket_SEND_buffer_size_bytes;
				TCP_NODELAY_enabled = s_global_socket_TCP_NODELAY_enabled;
			}
		};


#ifndef TARGET_PLATFORM_WIN32
		/// modelise a FIFO connection to a local server
		class InitiatorFIFO: public Socket
		{
			typedef InitiatorFIFO Me;
		public:
			InitiatorFIFO (char const * name);
			~InitiatorFIFO ();

			// connect to a remote server (synchronous, one-attempt version)
			ReturnCode connect_to (std::string const & server_directory);

		private:
			// Overriden from Network Socket 
			virtual bool is_connectionless() const	{ return false; }
			virtual void disconnect_impl ();

			ReturnCode connect_to_impl (std::string const & server_directory);

			void listen_and_dispatch_loop_impl (LockedBool const & should_terminate);
			void listener_thread_wait_until_unblocked ();
			void listener_thread_block ();
			void listener_thread_unblock ();
			void listener_thread_run (LockedBool const & should_terminate);
			void listener_thread_stop ();
			void *						m_listener_thread;
			bool						m_listener_thread_blocked;
			ConditionalVariable			m_listener_thread_lock;

		public:
		};


		class SharedMemoryReceiver
		{
			typedef SharedMemoryReceiver Me;

			SharedMemoryReceiver& operator=(const SharedMemoryReceiver&);
			SharedMemoryReceiver(const SharedMemoryReceiver&);
		public:
			/*! channel_name is one of:
			 * - FeedReplay_L1::channel_name
			 * - FeedReplay_L2::channel_name
			 * - FeedReplay_MBO::channel_name
			 */
			SharedMemoryReceiver(char const * channel_name, int server_id);

			virtual ~SharedMemoryReceiver();

			bool	start();
			bool	stop();

			void get_counters (uint64 & bytes_recv, uint64 & datagram_recv) const;
			void reset_counters();

			// Configuration
			void setOptions(const IPCSharedMemoryOptions&);
			IPCSharedMemoryOptions getOptions() const;

			// Statistics
			// Statistics are disabled by default
			// Not thread-safe
			void enableStatistics();
			void disableStatistics();

			/*! Clear the statistics.
			 */
			void resetStatistics();

			/*! Disable, dump the statistics and reenable the statistics.
			 */
			void dumpStatistics(std::ostream&);

		private:
			virtual void select_and_dispatch_loop_impl (LockedBool const & should_terminate);
			// read data sent by the remote side
			virtual void receive_data	(void const * p, unsigned int n) = 0;

		private:
			std::string m_Name;
			IPCSharedMemReader *m_Reader;
			volatile bool				m_IsRunning;
			void*		m_thread;
		};
#endif


	public:
		/// reconnect processing (see retry_connect_to)
		static void start_reconnect_thread();
		static void stop_reconnect_thread ();

		static unsigned int nb_pending_reconnect ();
		//@}
	};

}	// namespace FeedOS


#endif


/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse           **/
/************************************/

