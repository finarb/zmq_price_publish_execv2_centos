/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_CONNECTION_GetMetaData_H
#define FEEDOS_generated_PDU_CONNECTION_GetMetaData_H

#include "gen_pdu_CONNECTION_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_CONNECTION_GetMetaData
{
	class Request: public PDU_outbound_Request
	{
	public:
		inline Request () :
			PDU_outbound_Request (IDS::Request_CONNECTION_GetMetaData)
		{
		}
	};

	class Response: public PDU_outbound_Response
	{
	public:
		inline Response (ReturnCode rc) :
			PDU_outbound_Response (IDS::Response_CONNECTION_GetMetaData, rc)
		{}
		inline Response (ListOfTagDeclaration const & a, ListOfEnumTypeDeclaration const & b, ListOfString const & c, Timestamp const & d) :
			PDU_outbound_Response (IDS::Response_CONNECTION_GetMetaData, RC_OK)
		{
			Encode_ListOfTagDeclaration (*this, a);
			Encode_ListOfEnumTypeDeclaration (*this, b);
			Encode_ListOfString (*this, c);
			Encode_Timestamp (*this, d);
		}
	};

}


namespace PDU_inbound_CONNECTION_GetMetaData
{
	class Request: public PDU_inbound_Request
	{
	public:
		inline Request (PDU const & p) :
			PDU_inbound_Request (IDS::Request_CONNECTION_GetMetaData, p)
		{
		}
	private:
	public:
	};

	class Response: public PDU_inbound_Response
	{
	public:
		inline Response (PDU const & p) :
			PDU_inbound_Response (IDS::Response_CONNECTION_GetMetaData, p)
		{
			if (RC_OK != get_rc()) return;
			Decode_ListOfTagDeclaration (*this, m_Tags);
			Decode_ListOfEnumTypeDeclaration (*this, m_Enums);
			Decode_ListOfString (*this, m_Providers);
			Decode_Timestamp (*this, m_LastUpdate);
		}
		inline ListOfTagDeclaration const & getTags() const { return m_Tags; }
		inline ListOfEnumTypeDeclaration const & getEnums() const { return m_Enums; }
		inline ListOfString const & getProviders() const { return m_Providers; }
		inline Timestamp const & getLastUpdate() const { return m_LastUpdate; }
	private:
		ListOfTagDeclaration m_Tags;
		ListOfEnumTypeDeclaration m_Enums;
		ListOfString m_Providers;
		Timestamp m_LastUpdate;
	public:
		inline ListOfTagDeclaration & _refTags() { return m_Tags; }
		inline ListOfEnumTypeDeclaration & _refEnums() { return m_Enums; }
		inline ListOfString & _refProviders() { return m_Providers; }
		inline Timestamp & _refLastUpdate() { return m_LastUpdate; }
	};

}

}
#endif
