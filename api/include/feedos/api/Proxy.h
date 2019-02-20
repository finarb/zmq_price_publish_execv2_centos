
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_PROXY_H
#define FEEDOS_API_PROXY_H

#ifndef FEEDOS_COMM_PDU_H
#  include "../comm/PDU.h"
#endif

#define FEEDOS_PROXY_MEASURE_LATENCY	0

namespace FeedOS {

	class Proxy
	{
	public:
		Proxy (std::string const & name);
		virtual ~Proxy () {}

		std::string	const & get_proxy_name () const { return m_name; }

#if FEEDOS_PROXY_MEASURE_LATENCY
	protected:
		static void final_dump_latency_measures ();	// final report (called when disconnecting)

		static void prepare_latency_measure ();		// data received: early timestamp
		static void validate_latency_measure ();	// data received: (at least) one message has been received

		static void cancel_latency_measure ();		// data processed: cancel current measure

	public:
		// data processed: compute the delay. CALL THIS FROM USER CALLBACKS !
		static void perform_latency_measure (char const * location);
		static void enable_next_latency_measure ();		// data received: user processing finished, allow another measure
#endif

		void get_byte_counters (uint64 & recv, uint64 & sent) const
		{
			recv = m_counters_bytes_received;
			sent = m_counters_bytes_sent;
		}

		void reset_byte_counters ()
		{
			m_counters_bytes_received=0;
			m_counters_bytes_sent=0;
		}

	protected:
		// call this to send a PDU. Calls send_data() (and handle_transmission_error() in case of error)
		void send_pdu  (RequestNumber req_num, PDU const & pdu, unsigned int specific_uid=0, unsigned int specific_gid=0);
	
		// call this to process incoming data
		// - in case of success: Calls receive_pdu()
		// - in case of error: Calls handle_protocol_error()
		// always returns the number of messages that were successfully reassembled
		unsigned int receive_data (void const * p, unsigned int n);

		void reset_receive_data_buffer() {
			SCOPE_AUTO_LOCK (l,m_buffer_lock);
			m_receive_buffer.clear();
		}

	protected:
		// overide this to send raw data
		virtual ReturnCode send_data (void const * p, unsigned int n) = 0;

		// overide this to handle incoming PDUs
		virtual void receive_pdu (RequestNumber req_num, PDU const & pdu, unsigned int specific_uid, unsigned int specific_gid) = 0;
		virtual void receive_session_pdu (PDU const & pdu) = 0;

		// overide this
		virtual void handle_protocol_error (ReturnCode rc) = 0;
		virtual void handle_transmission_error (ReturnCode rc) = 0;

	private:
		void operator=(Proxy const &) {}	// dummy private operator
		std::string		m_receive_buffer;
		std::string		m_name;
		uint64			m_counters_bytes_received;
		uint64			m_counters_bytes_sent;
		ExclusiveLock	m_buffer_lock;
	};


}

#endif

