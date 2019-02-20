/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_SubscribeAllReferential_H
#define FEEDOS_generated_PDU_REFERENTIAL_SubscribeAllReferential_H

#include "gen_pdu_REFERENTIAL_notifications.h"

namespace FeedOS
{
namespace PDU_outbound_REFERENTIAL_SubscribeAllReferential
{
	class SubscribeRequest: public PDU_outbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest () :
			PDU_outbound_SubscribeRequest (IDS::SubscribeRequest_REFERENTIAL_SubscribeAllReferential)
		{
		}
	};

	class UnsubscribeRequest: public PDU_outbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest () :
			PDU_outbound_UnsubscribeRequest (IDS::UnsubscribeRequest_REFERENTIAL_SubscribeAllReferential)
		{}
	};

	class SubscribeResponse: public PDU_outbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (ReturnCode rc) :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_REFERENTIAL_SubscribeAllReferential, rc)
		{}
		inline SubscribeResponse () :
			PDU_outbound_SubscribeResponse (IDS::SubscribeResponse_REFERENTIAL_SubscribeAllReferential, RC_OK)
		{
		}
	};

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsDeleted SubscribeNotif_InstrumentsDeleted;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsDeletedExt SubscribeNotif_InstrumentsDeletedExt;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsCreated SubscribeNotif_InstrumentsCreated;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_InstrumentsModified SubscribeNotif_InstrumentsModified;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_MarkerTimestamp SubscribeNotif_MarkerTimestamp;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_VariablePriceIncrementTables SubscribeNotif_VariablePriceIncrementTables;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_TradeConditionsDictionary SubscribeNotif_TradeConditionsDictionary;

	typedef PDU_outbound_REFERENTIAL::SubscribeNotif_MetaData SubscribeNotif_MetaData;

	class UnsubscribeNotif: public PDU_outbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (ReturnCode rc) :
			PDU_outbound_UnsubscribeNotif (IDS::UnsubscribeNotif_REFERENTIAL_SubscribeAllReferential, rc)
		{}
	};

}


namespace PDU_inbound_REFERENTIAL_SubscribeAllReferential
{
	class SubscribeRequest: public PDU_inbound_SubscribeRequest
	{
	public:
		inline SubscribeRequest (PDU const & p) :
			PDU_inbound_SubscribeRequest (IDS::SubscribeRequest_REFERENTIAL_SubscribeAllReferential, p)
		{
		}
	private:
	public:
	};

	class UnsubscribeRequest: public PDU_inbound_UnsubscribeRequest
	{
	public:
		inline UnsubscribeRequest (PDU const & p) :
			PDU_inbound_UnsubscribeRequest (IDS::UnsubscribeRequest_REFERENTIAL_SubscribeAllReferential, p)
		{}
	};

	class SubscribeResponse: public PDU_inbound_SubscribeResponse
	{
	public:
		inline SubscribeResponse (PDU const & p) :
			PDU_inbound_SubscribeResponse (IDS::SubscribeResponse_REFERENTIAL_SubscribeAllReferential, p)
		{
			if (RC_OK != get_rc()) return;
		}
	private:
	public:
	};

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsDeleted SubscribeNotif_InstrumentsDeleted;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsDeletedExt SubscribeNotif_InstrumentsDeletedExt;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsCreated SubscribeNotif_InstrumentsCreated;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_InstrumentsModified SubscribeNotif_InstrumentsModified;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_MarkerTimestamp SubscribeNotif_MarkerTimestamp;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_VariablePriceIncrementTables SubscribeNotif_VariablePriceIncrementTables;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_TradeConditionsDictionary SubscribeNotif_TradeConditionsDictionary;

	typedef PDU_inbound_REFERENTIAL::SubscribeNotif_MetaData SubscribeNotif_MetaData;

	class UnsubscribeNotif: public PDU_inbound_UnsubscribeNotif
	{
	public:
		inline UnsubscribeNotif (PDU const & p) :
			PDU_inbound_UnsubscribeNotif (IDS::UnsubscribeNotif_REFERENTIAL_SubscribeAllReferential, p)
		{}
	};

}

}
#endif
