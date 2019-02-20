
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_PDU_H
#define FEEDOS_COMM_PDU_H

#ifndef FEEDOS_COMM_ENCODING_H
#  include "encoding.h"
#endif
#ifndef FEEDOS_COMM_PDU_ID_H
#  include "PDU_Id.h"
#endif
#ifndef FEEDOS_COMM_ERRORS_H
#  include "errors.h"
#endif
//#include "../base/smart_ptr.h"

namespace FeedOS {

	// modelize a Protocol Data Unit
	class PDU
	{
	protected:
		inline void set_id	(PDU_Id const & id) { m_pdu_id=id; }
	public:
		inline PDU () {}	// dummy, INVALID pdu (id==0)

		inline PDU (PDU const & v) : m_data (v.m_data), m_pdu_id(v.m_pdu_id) {}

		// for inbound PDU
		PDU (DataDecoder & d, std::string & v);
		PDU (PDU_Id const & id, std::string & v) : m_pdu_id(id) { m_data.get_buffer().swap (v); }

		inline virtual ~PDU() {}

		bool is_valid() const { return 0!=m_pdu_id; }

		inline PDU const & operator= (PDU const & v) { m_data = v.m_data; m_pdu_id=v.m_pdu_id; return *this; }

		inline EncodedBuffer const &	get_data () const	{ return m_data; }
		inline EncodedBuffer &			get_data ()			{ return m_data; }

		inline PDU_Id const &			get_id	() const { return m_pdu_id; }
		inline std::string				get_name() const { return m_pdu_id.get_name (); }

		virtual std::string to_str () const;
		virtual void dump (std::ostream & os) const;

		static void protocol_error				(std::string const & what);
		static void protocol_unexpected_notif	(std::string const & what);
		
	protected:
		inline PDU (PDU_Id const & id) : m_pdu_id(id) {}	// for outbound PDU
		void encoding_error(std::string const & what);

		void do_check_type	(PDU_Type t);
		void do_check_id	(PDU_Id expected_id);
#if FEEDOS_ENABLE_PARANOID_CHECKS
		inline void check_type	(PDU_Type t) { do_check_type(t); }
		inline void check_id	(PDU_Id expected_id) { do_check_id(expected_id); }
#else
		inline void check_type	(PDU_Type /*t*/) {}
		inline void check_id	(PDU_Id /*expected_id*/) {}
#endif

	private:
		EncodedBuffer	m_data;
		PDU_Id			m_pdu_id;
	};

//	typedef PDU PtrPDU;	// simulate the old smart_ptr


	//////////////////////////////
	//////////////////////////////  INBOUND (decode an incoming PDU)
	//////////////////////////////
	
	class PDU_inbound: protected DataDecoder, public PDU
	{
	public:
		PDU_inbound (std::string & s);

		PDU_inbound (PDU_Id expected_id, PDU const & p);

		inline PDU_inbound const & operator= (PDU const & v)
		{
			PDU::operator= (v);
			attach_to_buffer (v.get_data());
			return *this;
		}
	};


	class PDU_inbound_Request: public PDU_inbound
	{
	protected:
		inline PDU_inbound_Request (PDU_Id expected_id, PDU const & p) :
			PDU_inbound(expected_id, p)
		{
			check_type (PDU_Type_Request); 
		}
	};


	class PDU_inbound_SubscribeRequest: public PDU_inbound
	{
	protected:
		inline PDU_inbound_SubscribeRequest (PDU_Id expected_id, PDU const & p) :
			PDU_inbound(expected_id, p)
		{
			check_type (PDU_Type_SubscribeRequest); 
		}
	};


	class PDU_inbound_UnsubscribeRequest: public PDU_inbound
	{
	protected:
		inline PDU_inbound_UnsubscribeRequest (PDU_Id expected_id, PDU const & p) :
			PDU_inbound(expected_id, p)
		{
			check_type (PDU_Type_UnsubscribeRequest); 
		}
	};



	// all kinds of response (server=>client)
	class PDU_inbound_KindOfResponse: public PDU_inbound
	{
	public:
		inline PDU_inbound_KindOfResponse (PDU_Id expected_id, PDU const & v) :
			PDU_inbound(expected_id, v)
		{
			init (v); 
		}

		inline PDU_inbound_KindOfResponse const & operator= (PDU const & v)
		{
			PDU_inbound::operator= (v);
			init (v); 
			return *this;
		}

		inline ReturnCode	get_rc () const { return m_rc; }

	private:
		ReturnCode	m_rc;

	private:
		inline void init (PDU const & /*v*/)
		{
#if FEEDOS_ENABLE_PARANOID_CHECKS
			if (!get_id().is_a_kind_of_response()) {
				encoding_error("kind_of_response expected");
			}
#endif
			if (get_id().has_a_return_code()) {
				decode_ReturnCode(m_rc);
				set_reset_offset();	// pass over RC
			} else {
				m_rc = RC_OK;
			}
		}

	};


	class PDU_inbound_Response: public PDU_inbound_KindOfResponse
	{
	public:
		inline PDU_inbound_Response (PDU_Id expected_id, PDU const & p) :
			PDU_inbound_KindOfResponse (expected_id, p)
		{
			check_type (PDU_Type_Response);
		}
	};


	class PDU_inbound_SubscribeResponse: public PDU_inbound_KindOfResponse
	{
	public:
		inline PDU_inbound_SubscribeResponse (PDU_Id expected_id, PDU const & p) :
			PDU_inbound_KindOfResponse (expected_id, p)
		{
			check_type (PDU_Type_SubscribeResponse);
		}
	};


	class PDU_inbound_SubscribeNotif: public PDU_inbound_KindOfResponse
	{
	public:
		inline PDU_inbound_SubscribeNotif (PDU_Id expected_id, PDU const & p) :
			PDU_inbound_KindOfResponse (expected_id, p)
		{
			check_type (PDU_Type_SubscribeNotif);
		}
	};


	class PDU_inbound_UnsubscribeNotif: public PDU_inbound_KindOfResponse
	{
	public:
		inline PDU_inbound_UnsubscribeNotif (PDU_Id expected_id, PDU const & p) :
			PDU_inbound_KindOfResponse (expected_id, p)
		{
			check_type (PDU_Type_UnsubscribeNotif);
		}
	};





	//////////////////////////////
	//////////////////////////////  OUTBOUND (build an outgoing PDU)
	//////////////////////////////

	class PDU_outbound: public PDU, protected DataEncoder
	{
	protected:
		PDU_outbound (PDU_Id id);
	};


	class PDU_outbound_Request: public PDU_outbound
	{
	public:
		inline PDU_outbound_Request (PDU_Id const & id) :
			PDU_outbound(id)
		{
			check_type (PDU_Type_Request); 
		}
	};

	class PDU_outbound_SubscribeRequest: public PDU_outbound
	{
	public:
		inline PDU_outbound_SubscribeRequest (PDU_Id const & id) :	// TODO: add flags about "error handling" (transparent failover allowed, etc)
			PDU_outbound(id)
		{
			check_type (PDU_Type_SubscribeRequest); 
		}
	};

	class PDU_outbound_UnsubscribeRequest: public PDU_outbound
	{
	public:
		inline PDU_outbound_UnsubscribeRequest (PDU_Id const & id) :
			PDU_outbound(id)
		{
			check_type (PDU_Type_UnsubscribeRequest); 
		}
	};

	// all kinds of response (server=>client)
	class PDU_outbound_KindOfResponse: public PDU_outbound
	{
	protected:
		PDU_outbound_KindOfResponse (PDU_Id id, ReturnCode rc);
	};


	class PDU_outbound_Response: public PDU_outbound_KindOfResponse
	{
	public:
		inline PDU_outbound_Response (PDU_Id const & id, ReturnCode rc) :
			PDU_outbound_KindOfResponse(id,rc)
		{
			check_type (PDU_Type_Response);
		}
	};

	class PDU_outbound_SubscribeResponse: public PDU_outbound_KindOfResponse
	{
	public:
		inline PDU_outbound_SubscribeResponse (PDU_Id const & id, ReturnCode rc) :
			PDU_outbound_KindOfResponse(id,rc)
		{
			check_type (PDU_Type_SubscribeResponse);
		}
	};

	class PDU_outbound_SubscribeNotif: public PDU_outbound_KindOfResponse
	{
	public:
		inline PDU_outbound_SubscribeNotif (PDU_Id const & id) :
			PDU_outbound_KindOfResponse(id,RC_OK)
		{
			check_type (PDU_Type_SubscribeNotif);
		}
	};

	class PDU_outbound_UnsubscribeNotif: public PDU_outbound_KindOfResponse
	{
	public:
		inline PDU_outbound_UnsubscribeNotif (PDU_Id const & id, ReturnCode rc) :
			PDU_outbound_KindOfResponse(id,rc)
		{
			check_type (PDU_Type_UnsubscribeNotif);
		}
	};



	inline PDU build_generic_response_pdu				(PDU_Id const & pdu_id_req,		ReturnCode rc)
	{
		return PDU_outbound_Response (PDU_Id::build_pdu_id_response (pdu_id_req), rc);
	}

	inline PDU build_generic_subscribe_response_pdu		(PDU_Id const & pdu_id_req,		ReturnCode rc)
	{
		return PDU_outbound_SubscribeResponse (PDU_Id::build_pdu_id_subscribe_response (pdu_id_req), rc);
	}

	inline PDU build_generic_unsubscribe_notif_pdu		(PDU_Id const & pdu_id_subreq,	ReturnCode rc)
	{
		return PDU_outbound_UnsubscribeNotif (PDU_Id::build_pdu_id_unsubscribe_notif (pdu_id_subreq), rc);
	}

	inline PDU build_generic_unsubscribe_request_pdu	(PDU_Id const & pdu_id_subreq)
	{
		return PDU_outbound_UnsubscribeRequest (PDU_Id::build_pdu_id_unsubscribe_request (pdu_id_subreq));
	}


}


inline std::ostream & operator<<(std::ostream & os, FeedOS::PDU const & v)
{
	return os << v.get_name();
}


#endif
