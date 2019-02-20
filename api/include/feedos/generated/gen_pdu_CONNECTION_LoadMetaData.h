/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_CONNECTION_LoadMetaData_H
#define FEEDOS_generated_PDU_CONNECTION_LoadMetaData_H

#include "gen_pdu_CONNECTION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_CONNECTION_LoadMetaData
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request (ListOfTagDeclaration const & a, ListOfEnumTypeDeclaration const & b, String const & c, bool d) :
			PDU_outbound_Request (IDS::Request_CONNECTION_LoadMetaData)
		{
			Encode_ListOfTagDeclaration (*this, a);
			Encode_ListOfEnumTypeDeclaration (*this, b);
			Encode_String (*this, c);
			Encode_bool (*this, d);
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_CONNECTION_LoadMetaData, rc)
		{}
		inline Response () :
			PDU_outbound_Response (IDS::Response_CONNECTION_LoadMetaData, RC_OK)
		{
		}
	};

}


namespace PDU_inbound_CONNECTION_LoadMetaData
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_CONNECTION_LoadMetaData, p)
		{
			Decode_ListOfTagDeclaration (*this, m_Tags);
			Decode_ListOfEnumTypeDeclaration (*this, m_Enums);
			Decode_String (*this, m_ProviderName);
			Decode_bool (*this, m_Merge);
		}
		inline ListOfTagDeclaration const & getTags() const { return m_Tags; }
		inline ListOfEnumTypeDeclaration const & getEnums() const { return m_Enums; }
		inline String const & getProviderName() const { return m_ProviderName; }
		inline bool const & getMerge() const { return m_Merge; }
	private:
		ListOfTagDeclaration m_Tags;
		ListOfEnumTypeDeclaration m_Enums;
		String m_ProviderName;
		bool m_Merge;
	public:
		inline ListOfTagDeclaration & _refTags() { return m_Tags; }
		inline ListOfEnumTypeDeclaration & _refEnums() { return m_Enums; }
		inline String & _refProviderName() { return m_ProviderName; }
		inline bool & _refMerge() { return m_Merge; }
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_CONNECTION_LoadMetaData, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

}

}
#endif
