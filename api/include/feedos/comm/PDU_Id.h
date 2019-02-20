
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_PDU_ID_H
#define FEEDOS_COMM_PDU_ID_H

#ifndef FEEDOS_BASE_BASE_H
#  include "../base/base.h"
#endif

#include "pdu_tools.h"
#include <string>
#include <iostream>

namespace FeedOS {

	// unique ID for identifying a message within the protocol (SnapshotRequest, LookupResponse, ...)
	class PDU_Id
	{
	public:
		inline PDU_Id () : m_id (0) {}
		inline PDU_Id (unsigned int i) : m_id (i) {}
		inline PDU_Id (PDU_Id const & v) : m_id (v.m_id) {}

		inline PDU_Id const & operator= (PDU_Id const & v) { m_id=v.m_id; return *this; }
		inline bool operator== (PDU_Id const & v) { return m_id==v.m_id; }
		inline bool operator!= (PDU_Id const & v) { return m_id!=v.m_id; }
		inline bool operator<  (PDU_Id const & v) { return m_id< v.m_id; }
		inline operator unsigned int () const { return m_id; }

		static void		register_pdu_name	(PDU_Id id, std::string name);
		std::string		get_name() const;

		inline			PDU_Type		get_type ()		const { return (PDU_Type)GET_PDU_TYPE(m_id); }
		inline			unsigned int	get_service()	const { return GET_PDU_SERVICE(m_id); }
		inline			unsigned int	get_operation()	const { return GET_PDU_OPERATION(m_id); }

		static char const *				get_type_str (PDU_Type value);
		inline char const *				get_type_str () const { return get_type_str(get_type()); }

		static inline PDU_Id	build_pdu_id_response (unsigned int i)				{ return MAKE_PDU_ID_SIBLING(PDU_Type_Response, i); }
		static inline PDU_Id	build_pdu_id_subscribe_response (unsigned int i)	{ return MAKE_PDU_ID_SIBLING(PDU_Type_SubscribeResponse, i); }
		static inline PDU_Id	build_pdu_id_unsubscribe_request (unsigned int i)	{ return MAKE_PDU_ID_SIBLING(PDU_Type_UnsubscribeRequest, i); } 
		static inline PDU_Id	build_pdu_id_unsubscribe_notif (unsigned int i)		{ return MAKE_PDU_ID_SIBLING(PDU_Type_UnsubscribeNotif, i); }

		inline bool is_a_kind_of_request () const
		{
			switch (get_type()) {
			case PDU_Type_Request:
			case PDU_Type_SubscribeRequest:
			case PDU_Type_UnsubscribeRequest:
				return true;
			default:
				return false;
			}
		}

		inline bool is_a_kind_of_response() const { return !is_a_kind_of_request(); }

		inline bool has_a_return_code () const
		{
			switch (get_type()) {
			case PDU_Type_Response:
			case PDU_Type_SubscribeResponse:
			case PDU_Type_UnsubscribeNotif:
				return true;
			default:
				return false;
			}
		}

	private:
		unsigned int	m_id;
	};

}


inline std::ostream & operator<<(std::ostream & os, FeedOS::PDU_Id const & v) { return os << v.get_name(); }


#endif
