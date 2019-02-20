/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_ENCODING_H
#define FEEDOS_generated_ENCODING_H

#ifndef FEEDOS_API_ENCODING_FUNCTIONS_H
#  include "../api/encoding_functions.h"
#endif

namespace FeedOS {
	namespace Types {

	inline void Encode_LookupMode	(DataEncoder & e, LookupMode const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_LookupMode	(DataDecoder & d, LookupMode & v) 	{ Decode_Enum (d,v); }

	inline void Encode_OrderModificationReason	(DataEncoder & e, OrderModificationReason const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_OrderModificationReason	(DataDecoder & d, OrderModificationReason & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FIXMarketNewsUrgency	(DataEncoder & e, FIXMarketNewsUrgency const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FIXMarketNewsUrgency	(DataDecoder & d, FIXMarketNewsUrgency & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FIXNewsCategory	(DataEncoder & e, FIXNewsCategory const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FIXNewsCategory	(DataDecoder & d, FIXNewsCategory & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FIXTradSesMethod	(DataEncoder & e, FIXTradSesMethod const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FIXTradSesMethod	(DataDecoder & d, FIXTradSesMethod & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FIXTradSesMode	(DataEncoder & e, FIXTradSesMode const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FIXTradSesMode	(DataDecoder & d, FIXTradSesMode & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FIXTradSesStatus	(DataEncoder & e, FIXTradSesStatus const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FIXTradSesStatus	(DataDecoder & d, FIXTradSesStatus & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FIXSecurityTradingStatus	(DataEncoder & e, FIXSecurityTradingStatus const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FIXSecurityTradingStatus	(DataDecoder & d, FIXSecurityTradingStatus & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FOSRegSHOAction	(DataEncoder & e, FOSRegSHOAction const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FOSRegSHOAction	(DataDecoder & d, FOSRegSHOAction & v) 	{ Decode_Enum (d,v); }

	inline void Encode_QuotationTradeImpactIndicator	(DataEncoder & e, QuotationTradeImpactIndicator const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_QuotationTradeImpactIndicator	(DataDecoder & d, QuotationTradeImpactIndicator & v) 	{ Decode_Enum (d,v); }

	inline void Encode_QuotationUpdateContent	(DataEncoder & e, QuotationUpdateContent const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_QuotationUpdateContent	(DataDecoder & d, QuotationUpdateContent & v) 	{ Decode_Enum (d,v); }

	inline void Encode_OrderBookDeltaAction	(DataEncoder & e, OrderBookDeltaAction const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_OrderBookDeltaAction	(DataDecoder & d, OrderBookDeltaAction & v) 	{ Decode_Enum (d,v); }

	inline void Encode_presencemap_MBLOverlapRefresh	(DataEncoder & e, presencemap_MBLOverlapRefresh const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_presencemap_MBLOverlapRefresh	(DataDecoder & d, presencemap_MBLOverlapRefresh & v) 	{ Decode_Enum (d,v); }

	inline void Encode_presencemap_MBLDeltaRefresh	(DataEncoder & e, presencemap_MBLDeltaRefresh const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_presencemap_MBLDeltaRefresh	(DataDecoder & d, presencemap_MBLDeltaRefresh & v) 	{ Decode_Enum (d,v); }

	inline void Encode_presencemap_MBLLayer	(DataEncoder & e, presencemap_MBLLayer const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_presencemap_MBLLayer	(DataDecoder & d, presencemap_MBLLayer & v) 	{ Decode_Enum (d,v); }

	inline void Encode_NewsCategory	(DataEncoder & e, NewsCategory const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_NewsCategory	(DataDecoder & d, NewsCategory & v) 	{ Decode_Enum (d,v); }

	inline void Encode_NewsType	(DataEncoder & e, NewsType const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_NewsType	(DataDecoder & d, NewsType & v) 	{ Decode_Enum (d,v); }

	inline void Encode_NewsFieldId	(DataEncoder & e, NewsFieldId const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_NewsFieldId	(DataDecoder & d, NewsFieldId & v) 	{ Decode_Enum (d,v); }

	inline void Encode_NewsEventType	(DataEncoder & e, NewsEventType const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_NewsEventType	(DataDecoder & d, NewsEventType & v) 	{ Decode_Enum (d,v); }

	inline void Encode_MulticastDataRecoveryMode	(DataEncoder & e, MulticastDataRecoveryMode const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_MulticastDataRecoveryMode	(DataDecoder & d, MulticastDataRecoveryMode & v) 	{ Decode_Enum (d,v); }

	inline void Encode_AllocateNewInstrumentPolicy	(DataEncoder & e, AllocateNewInstrumentPolicy const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_AllocateNewInstrumentPolicy	(DataDecoder & d, AllocateNewInstrumentPolicy & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FeedState	(DataEncoder & e, FeedState const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FeedState	(DataDecoder & d, FeedState & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FeedHandlerResiliencyRole	(DataEncoder & e, FeedHandlerResiliencyRole const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FeedHandlerResiliencyRole	(DataDecoder & d, FeedHandlerResiliencyRole & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FeedHandlerResiliencyStatus	(DataEncoder & e, FeedHandlerResiliencyStatus const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FeedHandlerResiliencyStatus	(DataDecoder & d, FeedHandlerResiliencyStatus & v) 	{ Decode_Enum (d,v); }

	inline void Encode_FeedAccessMethod	(DataEncoder & e, FeedAccessMethod const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_FeedAccessMethod	(DataDecoder & d, FeedAccessMethod & v) 	{ Decode_Enum (d,v); }

	inline void Encode_OrderRejectReason	(DataEncoder & e, OrderRejectReason const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_OrderRejectReason	(DataDecoder & d, OrderRejectReason & v) 	{ Decode_Enum (d,v); }

	inline void Encode_AdjustmentFactorEventType	(DataEncoder & e, AdjustmentFactorEventType const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_AdjustmentFactorEventType	(DataDecoder & d, AdjustmentFactorEventType & v) 	{ Decode_Enum (d,v); }

	inline void Encode_TradeCancelCorrectionContent	(DataEncoder & e, TradeCancelCorrectionContent const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_TradeCancelCorrectionContent	(DataDecoder & d, TradeCancelCorrectionContent & v) 	{ Decode_Enum (d,v); }

	inline void Encode_DailyExtPointType	(DataEncoder & e, DailyExtPointType const & v) 	{ Encode_Enum (e,v); }
	inline void Decode_DailyExtPointType	(DataDecoder & d, DailyExtPointType & v) 	{ Decode_Enum (d,v); }

	inline void Encode_ListOfPolymorphicInstrumentCode (DataEncoder & e, std::vector<PolymorphicInstrumentCode > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<PolymorphicInstrumentCode >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_PolymorphicInstrumentCode (e,*it);	}
	inline void Decode_ListOfPolymorphicInstrumentCode (DataDecoder & d, std::vector<PolymorphicInstrumentCode > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_PolymorphicInstrumentCode (d,l[i]); }

	inline void Encode_ListOfFOSInstrumentCode (DataEncoder & e, std::vector<FOSInstrumentCode > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<FOSInstrumentCode >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_FOSInstrumentCode (e,*it);	}
	inline void Decode_ListOfFOSInstrumentCode (DataDecoder & d, std::vector<FOSInstrumentCode > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_FOSInstrumentCode (d,l[i]); }

	inline void Encode_ListOfString (DataEncoder & e, std::vector<String > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<String >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_String (e,*it);	}
	inline void Decode_ListOfString (DataDecoder & d, std::vector<String > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_String (d,l[i]); }

	inline void Encode_ListOfFOSMarketId (DataEncoder & e, std::vector<FOSMarketId > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<FOSMarketId >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_FOSMarketId (e,*it);	}
	inline void Decode_ListOfFOSMarketId (DataDecoder & d, std::vector<FOSMarketId > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_FOSMarketId (d,l[i]); }

	inline void Encode_ListOfBinaryBuffer (DataEncoder & e, std::vector<BinaryBuffer > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<BinaryBuffer >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_BinaryBuffer (e,*it);	}
	inline void Decode_ListOfBinaryBuffer (DataDecoder & d, std::vector<BinaryBuffer > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_BinaryBuffer (d,l[i]); }

	inline void Encode_TagNumber	(DataEncoder & e, TagNumber const & v) 	{ Encode_uint16 (e,v); }
	inline void Decode_TagNumber	(DataDecoder & d, TagNumber & v) 	{ Decode_uint16 (d,v); }

	inline void Encode_ReferentialTagNumber	(DataEncoder & e, ReferentialTagNumber const & v) 	{ Encode_TagNumber (e,v); }
	inline void Decode_ReferentialTagNumber	(DataDecoder & d, ReferentialTagNumber & v) 	{ Decode_TagNumber (d,v); }

	inline void Encode_QuotationTagNumber	(DataEncoder & e, QuotationTagNumber const & v) 	{ Encode_TagNumber (e,v); }
	inline void Decode_QuotationTagNumber	(DataDecoder & d, QuotationTagNumber & v) 	{ Decode_TagNumber (d,v); }

	inline void Encode_ListOfTagNumber (DataEncoder & e, std::vector<TagNumber > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<TagNumber >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_TagNumber (e,*it);	}
	inline void Decode_ListOfTagNumber (DataDecoder & d, std::vector<TagNumber > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_TagNumber (d,l[i]); }

	inline void Encode_ListOfReferentialTagNumber (DataEncoder & e, std::vector<ReferentialTagNumber > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<ReferentialTagNumber >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_ReferentialTagNumber (e,*it);	}
	inline void Decode_ListOfReferentialTagNumber (DataDecoder & d, std::vector<ReferentialTagNumber > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_ReferentialTagNumber (d,l[i]); }

	inline void Encode_ListOfQuotationTagNumber (DataEncoder & e, std::vector<QuotationTagNumber > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<QuotationTagNumber >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_QuotationTagNumber (e,*it);	}
	inline void Decode_ListOfQuotationTagNumber (DataDecoder & d, std::vector<QuotationTagNumber > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_QuotationTagNumber (d,l[i]); }

	inline void Encode_TagNumAndValue (DataEncoder & e, TagNumAndValue const & v)
	{
		Encode_TagNumber (e,v.getNum());
		Encode_Any (e,v.getValue());
	}
	inline void Decode_TagNumAndValue (DataDecoder & d, TagNumAndValue & v)
	{
		Decode_TagNumber (d,v.getNum());
		Decode_Any (d,v.getValue());
	}

	inline void Encode_ReferentialAttribute	(DataEncoder & e, ReferentialAttribute const & v) 	{ Encode_TagNumAndValue (e,v); }
	inline void Decode_ReferentialAttribute	(DataDecoder & d, ReferentialAttribute & v) 	{ Decode_TagNumAndValue (d,v); }

	inline void Encode_QuotationVariable	(DataEncoder & e, QuotationVariable const & v) 	{ Encode_TagNumAndValue (e,v); }
	inline void Decode_QuotationVariable	(DataDecoder & d, QuotationVariable & v) 	{ Decode_TagNumAndValue (d,v); }

	inline void Encode_QuotationContextFlag	(DataEncoder & e, QuotationContextFlag const & v) 	{ Encode_TagNumAndValue (e,v); }
	inline void Decode_QuotationContextFlag	(DataDecoder & d, QuotationContextFlag & v) 	{ Decode_TagNumAndValue (d,v); }

	inline void Encode_ListOfReferentialAttribute (DataEncoder & e, std::vector<ReferentialAttribute > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<ReferentialAttribute >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_ReferentialAttribute (e,*it);	}
	inline void Decode_ListOfReferentialAttribute (DataDecoder & d, std::vector<ReferentialAttribute > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_ReferentialAttribute (d,l[i]); }

	inline void Encode_ListOfQuotationVariable (DataEncoder & e, std::vector<QuotationVariable > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<QuotationVariable >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_QuotationVariable (e,*it);	}
	inline void Decode_ListOfQuotationVariable (DataDecoder & d, std::vector<QuotationVariable > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_QuotationVariable (d,l[i]); }

	inline void Encode_ListOfQuotationContextFlag (DataEncoder & e, std::vector<QuotationContextFlag > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<QuotationContextFlag >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_QuotationContextFlag (e,*it);	}
	inline void Decode_ListOfQuotationContextFlag (DataDecoder & d, std::vector<QuotationContextFlag > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_QuotationContextFlag (d,l[i]); }

	inline void Encode_FeedOSCmd	(DataEncoder & e, FeedOSCmd const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_FeedOSCmd	(DataDecoder & d, FeedOSCmd & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_ListOfFeedOSCmd (DataEncoder & e, std::vector<FeedOSCmd > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<FeedOSCmd >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_FeedOSCmd (e,*it);	}
	inline void Decode_ListOfFeedOSCmd (DataDecoder & d, std::vector<FeedOSCmd > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_FeedOSCmd (d,l[i]); }

	inline void Encode_ISOCountryCode	(DataEncoder & e, ISOCountryCode const & v) 	{ Encode_String (e,v); }
	inline void Decode_ISOCountryCode	(DataDecoder & d, ISOCountryCode & v) 	{ Decode_String (d,v); }

	inline void Encode_ISOLanguageCode	(DataEncoder & e, ISOLanguageCode const & v) 	{ Encode_String (e,v); }
	inline void Decode_ISOLanguageCode	(DataDecoder & d, ISOLanguageCode & v) 	{ Decode_String (d,v); }

	inline void Encode_ISOMarketId	(DataEncoder & e, ISOMarketId const & v) 	{ Encode_String (e,v); }
	inline void Decode_ISOMarketId	(DataDecoder & d, ISOMarketId & v) 	{ Decode_String (d,v); }

	inline void Encode_CFICode	(DataEncoder & e, CFICode const & v) 	{ Encode_String (e,v); }
	inline void Decode_CFICode	(DataDecoder & d, CFICode & v) 	{ Decode_String (d,v); }

	inline void Encode_FOSLowLevelVTSTableId	(DataEncoder & e, FOSLowLevelVTSTableId const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_FOSLowLevelVTSTableId	(DataDecoder & d, FOSLowLevelVTSTableId & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_FOSTradingSessionId	(DataEncoder & e, FOSTradingSessionId const & v) 	{ Encode_int8 (e,v); }
	inline void Decode_FOSTradingSessionId	(DataDecoder & d, FOSTradingSessionId & v) 	{ Decode_int8 (d,v); }

	inline void Encode_FOSDictionaryEntryId	(DataEncoder & e, FOSDictionaryEntryId const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_FOSDictionaryEntryId	(DataDecoder & d, FOSDictionaryEntryId & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_FIXNewsUrgency	(DataEncoder & e, FIXNewsUrgency const & v) 	{ Encode_FIXMarketNewsUrgency (e,v); }
	inline void Decode_FIXNewsUrgency	(DataDecoder & d, FIXNewsUrgency & v) 	{ Decode_FIXMarketNewsUrgency (d,v); }

	inline void Encode_FOSUuid (DataEncoder & e, FOSUuid const & v)
	{
		Encode_uint32 (e,v.getWordA());
		Encode_uint32 (e,v.getWordB());
		Encode_uint32 (e,v.getWordC());
		Encode_uint32 (e,v.getWordD());
	}
	inline void Decode_FOSUuid (DataDecoder & d, FOSUuid & v)
	{
		Decode_uint32 (d,v.getWordA());
		Decode_uint32 (d,v.getWordB());
		Decode_uint32 (d,v.getWordC());
		Decode_uint32 (d,v.getWordD());
	}

	inline void Encode_FIXSide	(DataEncoder & e, FIXSide const & v) 	{ Encode_char (e,v); }
	inline void Decode_FIXSide	(DataDecoder & d, FIXSide & v) 	{ Decode_char (d,v); }

	inline void Encode_ImbalanceSide	(DataEncoder & e, ImbalanceSide const & v) 	{ Encode_char (e,v); }
	inline void Decode_ImbalanceSide	(DataDecoder & d, ImbalanceSide & v) 	{ Decode_char (d,v); }

	inline void Encode_FIXScope	(DataEncoder & e, FIXScope const & v) 	{ Encode_char (e,v); }
	inline void Decode_FIXScope	(DataDecoder & d, FIXScope & v) 	{ Decode_char (d,v); }

	inline void Encode_OrderBookEntryExt (DataEncoder & e, OrderBookEntryExt const & v)
	{
		Encode_float64 (e,v.getPrice());
		Encode_float64 (e,v.getQty());
		Encode_int32 (e,v.getNbOrders());
	}
	inline void Decode_OrderBookEntryExt (DataDecoder & d, OrderBookEntryExt & v)
	{
		Decode_float64 (d,v.getPrice());
		Decode_float64 (d,v.getQty());
		Decode_int32 (d,v.getNbOrders());
	}

	inline void Encode_ListOfOrderBookEntryExt (DataEncoder & e, std::vector<OrderBookEntryExt > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<OrderBookEntryExt >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_OrderBookEntryExt (e,*it);	}
	inline void Decode_ListOfOrderBookEntryExt (DataDecoder & d, std::vector<OrderBookEntryExt > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_OrderBookEntryExt (d,l[i]); }

	inline void Encode_OrderBookEntry (DataEncoder & e, OrderBookEntry const & v)
	{
		Encode_float64 (e,v.getPrice());
		Encode_float64 (e,v.getQty());
	}
	inline void Decode_OrderBookEntry (DataDecoder & d, OrderBookEntry & v)
	{
		Decode_float64 (d,v.getPrice());
		Decode_float64 (d,v.getQty());
	}

	inline void Encode_ListOfOrderBookEntry (DataEncoder & e, std::vector<OrderBookEntry > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<OrderBookEntry >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_OrderBookEntry (e,*it);	}
	inline void Decode_ListOfOrderBookEntry (DataDecoder & d, std::vector<OrderBookEntry > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_OrderBookEntry (d,l[i]); }

	inline void Encode_QuotationTradeImpactIndicatorMask	(DataEncoder & e, QuotationTradeImpactIndicatorMask const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_QuotationTradeImpactIndicatorMask	(DataDecoder & d, QuotationTradeImpactIndicatorMask & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_QuotationContentMask	(DataEncoder & e, QuotationContentMask const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_QuotationContentMask	(DataDecoder & d, QuotationContentMask & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_QuotationTradeEvent (DataEncoder & e, QuotationTradeEvent const & v)
	{
		Encode_QuotationContentMask (e,v.getContentMask());
		Encode_FIXSecurityTradingStatus (e,v.getTradingStatus());
		Encode_OrderBookEntry (e,v.getBestBid());
		Encode_OrderBookEntry (e,v.getBestAsk());
		Encode_float64 (e,v.getLastTradeQty());
		Encode_float64 (e,v.getPrice());
	}
	inline void Decode_QuotationTradeEvent (DataDecoder & d, QuotationTradeEvent & v)
	{
		Decode_QuotationContentMask (d,v.getContentMask());
		Decode_FIXSecurityTradingStatus (d,v.getTradingStatus());
		Decode_OrderBookEntry (d,v.getBestBid());
		Decode_OrderBookEntry (d,v.getBestAsk());
		Decode_float64 (d,v.getLastTradeQty());
		Decode_float64 (d,v.getPrice());
	}

	       void Encode_QuotationTradeEventExt (DataEncoder & e, QuotationTradeEventExt const & v);
	inline void Bypassed_Encode_QuotationTradeEventExt (DataEncoder & e, QuotationTradeEventExt const & v)
	{
		Encode_QuotationContentMask (e,v.getContentMask());
		Encode_OrderBookEntryExt (e,v.getBestBid());
		Encode_OrderBookEntryExt (e,v.getBestAsk());
		Encode_float64 (e,v.getLastTradeQty());
		Encode_float64 (e,v.getPrice());
		Encode_ListOfQuotationContextFlag (e,v.getContext());
		Encode_ListOfQuotationVariable (e,v.getValues());
	}
	       void Decode_QuotationTradeEventExt (DataDecoder & d, QuotationTradeEventExt & v);
	inline void Bypassed_Decode_QuotationTradeEventExt (DataDecoder & d, QuotationTradeEventExt & v)
	{
		Decode_QuotationContentMask (d,v.getContentMask());
		Decode_OrderBookEntryExt (d,v.getBestBid());
		Decode_OrderBookEntryExt (d,v.getBestAsk());
		Decode_float64 (d,v.getLastTradeQty());
		Decode_float64 (d,v.getPrice());
		Decode_ListOfQuotationContextFlag (d,v.getContext());
		Decode_ListOfQuotationVariable (d,v.getValues());
	}

	inline void Encode_QuotationValuesUpdate (DataEncoder & e, QuotationValuesUpdate const & v)
	{
		Encode_QuotationContentMask (e,v.getContentMask());
		Encode_ListOfQuotationVariable (e,v.getValues());
	}
	inline void Decode_QuotationValuesUpdate (DataDecoder & d, QuotationValuesUpdate & v)
	{
		Decode_QuotationContentMask (d,v.getContentMask());
		Decode_ListOfQuotationVariable (d,v.getValues());
	}

	inline void Encode_TradingSessionCharacteristics (DataEncoder & e, TradingSessionCharacteristics const & v)
	{
		Encode_FOSTradingSessionId (e,v.getSessionId());
		Encode_String (e,v.getTradingSessionId());
		Encode_String (e,v.getTradingSessionSubId());
		Encode_FIXTradSesMethod (e,v.getTradSesMethod());
		Encode_FIXTradSesMode (e,v.getTradSesMode());
	}
	inline void Decode_TradingSessionCharacteristics (DataDecoder & d, TradingSessionCharacteristics & v)
	{
		Decode_FOSTradingSessionId (d,v.getSessionId());
		Decode_String (d,v.getTradingSessionId());
		Decode_String (d,v.getTradingSessionSubId());
		Decode_FIXTradSesMethod (d,v.getTradSesMethod());
		Decode_FIXTradSesMode (d,v.getTradSesMode());
	}

	inline void Encode_ListOfTradingSessionCharacteristics (DataEncoder & e, std::vector<TradingSessionCharacteristics > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<TradingSessionCharacteristics >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_TradingSessionCharacteristics (e,*it);	}
	inline void Decode_ListOfTradingSessionCharacteristics (DataDecoder & d, std::vector<TradingSessionCharacteristics > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_TradingSessionCharacteristics (d,l[i]); }

	inline void Encode_TradingSessionStatus (DataEncoder & e, TradingSessionStatus const & v)
	{
		Encode_FOSTradingSessionId (e,v.getSessionId());
		Encode_FIXTradSesStatus (e,v.getTradSesStatusEnum());
		Encode_Timestamp (e,v.getTradSesStartTime());
		Encode_Timestamp (e,v.getTradSesOpenTime());
		Encode_Timestamp (e,v.getTradSesPreCloseTime());
		Encode_Timestamp (e,v.getTradSesCloseTime());
		Encode_Timestamp (e,v.getTradSesEndTime());
		Encode_float64 (e,v.getTotalVolumeTraded());
		Encode_Timestamp (e,v.getLastUpdateTimestamp());
	}
	inline void Decode_TradingSessionStatus (DataDecoder & d, TradingSessionStatus & v)
	{
		Decode_FOSTradingSessionId (d,v.getSessionId());
		Decode_FIXTradSesStatus (d,v.getTradSesStatusEnum());
		Decode_Timestamp (d,v.getTradSesStartTime());
		Decode_Timestamp (d,v.getTradSesOpenTime());
		Decode_Timestamp (d,v.getTradSesPreCloseTime());
		Decode_Timestamp (d,v.getTradSesCloseTime());
		Decode_Timestamp (d,v.getTradSesEndTime());
		Decode_float64 (d,v.getTotalVolumeTraded());
		Decode_Timestamp (d,v.getLastUpdateTimestamp());
	}

	inline void Encode_OrderBook (DataEncoder & e, OrderBook const & v)
	{
		Encode_Timestamp (e,v.getServerUTCTimestamp());
		Encode_ListOfOrderBookEntry (e,v.getBidLimits());
		Encode_ListOfOrderBookEntry (e,v.getAskLimits());
	}
	inline void Decode_OrderBook (DataDecoder & d, OrderBook & v)
	{
		Decode_Timestamp (d,v.getServerUTCTimestamp());
		Decode_ListOfOrderBookEntry (d,v.getBidLimits());
		Decode_ListOfOrderBookEntry (d,v.getAskLimits());
	}

	inline void Encode_OrderBookBestLimits (DataEncoder & e, OrderBookBestLimits const & v)
	{
		Encode_OrderBookEntry (e,v.getBestBid());
		Encode_OrderBookEntry (e,v.getBestAsk());
	}
	inline void Decode_OrderBookBestLimits (DataDecoder & d, OrderBookBestLimits & v)
	{
		Decode_OrderBookEntry (d,v.getBestBid());
		Decode_OrderBookEntry (d,v.getBestAsk());
	}

	inline void Encode_OrderBookBestLimitsExt (DataEncoder & e, OrderBookBestLimitsExt const & v)
	{
		Encode_OrderBookEntryExt (e,v.getBestBid());
		Encode_OrderBookEntryExt (e,v.getBestAsk());
	}
	inline void Decode_OrderBookBestLimitsExt (DataDecoder & d, OrderBookBestLimitsExt & v)
	{
		Decode_OrderBookEntryExt (d,v.getBestBid());
		Decode_OrderBookEntryExt (d,v.getBestAsk());
	}

	inline void Encode_OrderBookDeltaRefresh (DataEncoder & e, OrderBookDeltaRefresh const & v)
	{
		Encode_OrderBookDeltaAction (e,v.getAction());
		Encode_int8 (e,v.getLevel());
		Encode_float64 (e,v.getPrice());
		Encode_float64 (e,v.getQty());
	}
	inline void Decode_OrderBookDeltaRefresh (DataDecoder & d, OrderBookDeltaRefresh & v)
	{
		Decode_OrderBookDeltaAction (d,v.getAction());
		Decode_int8 (d,v.getLevel());
		Decode_float64 (d,v.getPrice());
		Decode_float64 (d,v.getQty());
	}

	       void Encode_UTCTimestamps (DataEncoder & e, UTCTimestamps const & v);
	inline void Bypassed_Encode_UTCTimestamps (DataEncoder & e, UTCTimestamps const & v)
	{
		Encode_Timestamp (e,v.getServer());
		Encode_Timestamp (e,v.getMarket());
	}
	       void Decode_UTCTimestamps (DataDecoder & d, UTCTimestamps & v);
	inline void Bypassed_Decode_UTCTimestamps (DataDecoder & d, UTCTimestamps & v)
	{
		Decode_Timestamp (d,v.getServer());
		Decode_Timestamp (d,v.getMarket());
	}

	inline void Encode_FOSOrderBookLevel	(DataEncoder & e, FOSOrderBookLevel const & v) 	{ Encode_FOSInteger (e,v); }
	inline void Decode_FOSOrderBookLevel	(DataDecoder & d, FOSOrderBookLevel & v) 	{ Decode_FOSInteger (d,v); }

	inline void Encode_FOSQty	(DataEncoder & e, FOSQty const & v) 	{ Encode_FOSInteger (e,v); }
	inline void Decode_FOSQty	(DataDecoder & d, FOSQty & v) 	{ Decode_FOSInteger (d,v); }

	inline void Encode_MBLQty (DataEncoder & e, MBLQty const & v)
	{
		Encode_FOSQty (e,v.getCumulatedUnits());
		Encode_FOSQty (e,v.getNbOrders());
	}
	inline void Decode_MBLQty (DataDecoder & d, MBLQty & v)
	{
		Decode_FOSQty (d,v.getCumulatedUnits());
		Decode_FOSQty (d,v.getNbOrders());
	}

	       void Encode_MBLOrderBookEntry (DataEncoder & e, MBLOrderBookEntry const & v);
	inline void Bypassed_Encode_MBLOrderBookEntry (DataEncoder & e, MBLOrderBookEntry const & v)
	{
		Encode_FOSPrice (e,v.getPrice());
		Encode_MBLQty (e,v.getQty());
	}
	       void Decode_MBLOrderBookEntry (DataDecoder & d, MBLOrderBookEntry & v);
	inline void Bypassed_Decode_MBLOrderBookEntry (DataDecoder & d, MBLOrderBookEntry & v)
	{
		Decode_FOSPrice (d,v.getPrice());
		Decode_MBLQty (d,v.getQty());
	}

	inline void Encode_ListOfMBLOrderBookEntry (DataEncoder & e, std::vector<MBLOrderBookEntry > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MBLOrderBookEntry >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MBLOrderBookEntry (e,*it);	}
	inline void Decode_ListOfMBLOrderBookEntry (DataDecoder & d, std::vector<MBLOrderBookEntry > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MBLOrderBookEntry (d,l[i]); }

	inline void Encode_OrderBookLayerId	(DataEncoder & e, OrderBookLayerId const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_OrderBookLayerId	(DataDecoder & d, OrderBookLayerId & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_ListOfOrderBookLayerId (DataEncoder & e, std::vector<OrderBookLayerId > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<OrderBookLayerId >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_OrderBookLayerId (e,*it);	}
	inline void Decode_ListOfOrderBookLayerId (DataDecoder & d, std::vector<OrderBookLayerId > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_OrderBookLayerId (d,l[i]); }

	       void Encode_MBLOverlapRefresh (DataEncoder & e, MBLOverlapRefresh const & v);
	inline void Bypassed_Encode_MBLOverlapRefresh (DataEncoder & e, MBLOverlapRefresh const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_OrderBookLayerId (e,v.getLayerId());
		Encode_UTCTimestamps (e,v.getTimestamps());
		Encode_FOSInteger (e,v.getBidChangeIndicator());
		Encode_FOSInteger (e,v.getAskChangeIndicator());
		Encode_ListOfMBLOrderBookEntry (e,v.getBidLimits());
		Encode_ListOfMBLOrderBookEntry (e,v.getAskLimits());
		Encode_ListOfQuotationVariable (e,v.getOtherValues());
	}
	       void Decode_MBLOverlapRefresh (DataDecoder & d, MBLOverlapRefresh & v);
	inline void Bypassed_Decode_MBLOverlapRefresh (DataDecoder & d, MBLOverlapRefresh & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_OrderBookLayerId (d,v.getLayerId());
		Decode_UTCTimestamps (d,v.getTimestamps());
		Decode_FOSInteger (d,v.getBidChangeIndicator());
		Decode_FOSInteger (d,v.getAskChangeIndicator());
		Decode_ListOfMBLOrderBookEntry (d,v.getBidLimits());
		Decode_ListOfMBLOrderBookEntry (d,v.getAskLimits());
		Decode_ListOfQuotationVariable (d,v.getOtherValues());
	}

	       void Encode_MBLDeltaRefresh (DataEncoder & e, MBLDeltaRefresh const & v);
	inline void Bypassed_Encode_MBLDeltaRefresh (DataEncoder & e, MBLDeltaRefresh const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_OrderBookLayerId (e,v.getLayerId());
		Encode_UTCTimestamps (e,v.getTimestamps());
		Encode_OrderBookDeltaAction (e,v.getAction());
		Encode_FOSOrderBookLevel (e,v.getLevel());
		Encode_FOSPrice (e,v.getPrice());
		Encode_MBLQty (e,v.getQty());
		Encode_bool (e,v.getContinuationFlag());
		Encode_ListOfQuotationVariable (e,v.getOtherValues());
	}
	       void Decode_MBLDeltaRefresh (DataDecoder & d, MBLDeltaRefresh & v);
	inline void Bypassed_Decode_MBLDeltaRefresh (DataDecoder & d, MBLDeltaRefresh & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_OrderBookLayerId (d,v.getLayerId());
		Decode_UTCTimestamps (d,v.getTimestamps());
		Decode_OrderBookDeltaAction (d,v.getAction());
		Decode_FOSOrderBookLevel (d,v.getLevel());
		Decode_FOSPrice (d,v.getPrice());
		Decode_MBLQty (d,v.getQty());
		Decode_bool (d,v.getContinuationFlag());
		Decode_ListOfQuotationVariable (d,v.getOtherValues());
	}

	inline void Encode_MBLMaxVisibleDepth (DataEncoder & e, MBLMaxVisibleDepth const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_OrderBookLayerId (e,v.getLayerId());
		Encode_FOSOrderBookLevel (e,v.getMaxVisibleDepth());
	}
	inline void Decode_MBLMaxVisibleDepth (DataDecoder & d, MBLMaxVisibleDepth & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_OrderBookLayerId (d,v.getLayerId());
		Decode_FOSOrderBookLevel (d,v.getMaxVisibleDepth());
	}

	       void Encode_MBLLayer (DataEncoder & e, MBLLayer const & v);
	inline void Bypassed_Encode_MBLLayer (DataEncoder & e, MBLLayer const & v)
	{
		Encode_OrderBookLayerId (e,v.getLayerId());
		Encode_FOSOrderBookLevel (e,v.getMaxVisibleDepth());
		Encode_UTCTimestamps (e,v.getTimestamps());
		Encode_ListOfMBLOrderBookEntry (e,v.getBidLimits());
		Encode_ListOfMBLOrderBookEntry (e,v.getAskLimits());
		Encode_ListOfQuotationVariable (e,v.getOtherValues());
	}
	       void Decode_MBLLayer (DataDecoder & d, MBLLayer & v);
	inline void Bypassed_Decode_MBLLayer (DataDecoder & d, MBLLayer & v)
	{
		Decode_OrderBookLayerId (d,v.getLayerId());
		Decode_FOSOrderBookLevel (d,v.getMaxVisibleDepth());
		Decode_UTCTimestamps (d,v.getTimestamps());
		Decode_ListOfMBLOrderBookEntry (d,v.getBidLimits());
		Decode_ListOfMBLOrderBookEntry (d,v.getAskLimits());
		Decode_ListOfQuotationVariable (d,v.getOtherValues());
	}

	inline void Encode_ListOfMBLLayer (DataEncoder & e, std::vector<MBLLayer > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MBLLayer >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MBLLayer (e,*it);	}
	inline void Decode_ListOfMBLLayer (DataDecoder & d, std::vector<MBLLayer > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MBLLayer (d,l[i]); }

	inline void Encode_MBLSnapshot (DataEncoder & e, MBLSnapshot const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_ListOfMBLLayer (e,v.getLayers());
	}
	inline void Decode_MBLSnapshot (DataDecoder & d, MBLSnapshot & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_ListOfMBLLayer (d,v.getLayers());
	}

	inline void Encode_ListOfMBLSnapshot (DataEncoder & e, std::vector<MBLSnapshot > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MBLSnapshot >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MBLSnapshot (e,*it);	}
	inline void Decode_ListOfMBLSnapshot (DataDecoder & d, std::vector<MBLSnapshot > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MBLSnapshot (d,l[i]); }

	inline void Encode_TransactionOrPrice (DataEncoder & e, TransactionOrPrice const & v)
	{
		Encode_Timestamp (e,v.getMarketUTCTimestamp());
		Encode_float64 (e,v.getPrice());
		Encode_float64 (e,v.getQty());
	}
	inline void Decode_TransactionOrPrice (DataDecoder & d, TransactionOrPrice & v)
	{
		Decode_Timestamp (d,v.getMarketUTCTimestamp());
		Decode_float64 (d,v.getPrice());
		Decode_float64 (d,v.getQty());
	}

	inline void Encode_OHLCTA (DataEncoder & e, OHLCTA const & v)
	{
		Encode_float64 (e,v.getOpen());
		Encode_float64 (e,v.getHigh());
		Encode_float64 (e,v.getLow());
		Encode_float64 (e,v.getClose());
		Encode_float64 (e,v.getVolumeTraded());
		Encode_float64 (e,v.getAssetTraded());
	}
	inline void Decode_OHLCTA (DataDecoder & d, OHLCTA & v)
	{
		Decode_float64 (d,v.getOpen());
		Decode_float64 (d,v.getHigh());
		Decode_float64 (d,v.getLow());
		Decode_float64 (d,v.getClose());
		Decode_float64 (d,v.getVolumeTraded());
		Decode_float64 (d,v.getAssetTraded());
	}

	inline void Encode_QuotationIntradayBar (DataEncoder & e, QuotationIntradayBar const & v)
	{
		Encode_Timestamp (e,v.getServerUTCTimestamp_begin());
		Encode_uint16 (e,v.getServerDuration_seconds());
		Encode_FOSInstrumentCode (e,v.getInstrCode());
		Encode_float64 (e,v.getOpen());
		Encode_float64 (e,v.getHigh());
		Encode_float64 (e,v.getLow());
		Encode_float64 (e,v.getClose());
		Encode_float64 (e,v.getVolumeTraded());
		Encode_uint32 (e,v.getNbPoints());
		Encode_Timestamp (e,v.getMarketUTCTimestamp_begin());
		Encode_ListOfQuotationVariable (e,v.getOtherValues());
	}
	inline void Decode_QuotationIntradayBar (DataDecoder & d, QuotationIntradayBar & v)
	{
		Decode_Timestamp (d,v.getServerUTCTimestamp_begin());
		Decode_uint16 (d,v.getServerDuration_seconds());
		Decode_FOSInstrumentCode (d,v.getInstrCode());
		Decode_float64 (d,v.getOpen());
		Decode_float64 (d,v.getHigh());
		Decode_float64 (d,v.getLow());
		Decode_float64 (d,v.getClose());
		Decode_float64 (d,v.getVolumeTraded());
		Decode_uint32 (d,v.getNbPoints());
		Decode_Timestamp (d,v.getMarketUTCTimestamp_begin());
		Decode_ListOfQuotationVariable (d,v.getOtherValues());
	}

	inline void Encode_ListOfQuotationIntradayBar (DataEncoder & e, std::vector<QuotationIntradayBar > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<QuotationIntradayBar >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_QuotationIntradayBar (e,*it);	}
	inline void Decode_ListOfQuotationIntradayBar (DataDecoder & d, std::vector<QuotationIntradayBar > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_QuotationIntradayBar (d,l[i]); }

	inline void Encode_DailyValues	(DataEncoder & e, DailyValues const & v) 	{ Encode_OHLCTA (e,v); }
	inline void Decode_DailyValues	(DataDecoder & d, DailyValues & v) 	{ Decode_OHLCTA (d,v); }

	inline void Encode_HMS_Time (DataEncoder & e, HMS_Time const & v)
	{
		Encode_uint8 (e,v.getHour());
		Encode_uint8 (e,v.getMinute());
		Encode_uint8 (e,v.getSecond());
	}
	inline void Decode_HMS_Time (DataDecoder & d, HMS_Time & v)
	{
		Decode_uint8 (d,v.getHour());
		Decode_uint8 (d,v.getMinute());
		Decode_uint8 (d,v.getSecond());
	}

	inline void Encode_YMD_Date (DataEncoder & e, YMD_Date const & v)
	{
		Encode_uint16 (e,v.getYear());
		Encode_uint8 (e,v.getMonth());
		Encode_uint8 (e,v.getDay());
	}
	inline void Decode_YMD_Date (DataDecoder & d, YMD_Date & v)
	{
		Decode_uint16 (d,v.getYear());
		Decode_uint8 (d,v.getMonth());
		Decode_uint8 (d,v.getDay());
	}

	inline void Encode_YMD_Date_packed (DataEncoder & e, YMD_Date_packed const & v)
	{
		Encode_uint16 (e,v.getDaysSinceEpoch());
	}
	inline void Decode_YMD_Date_packed (DataDecoder & d, YMD_Date_packed & v)
	{
		Decode_uint16 (d,v.getDaysSinceEpoch());
	}

	inline void Encode_ListOfYMD_Date_packed (DataEncoder & e, std::vector<YMD_Date_packed > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<YMD_Date_packed >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_YMD_Date_packed (e,*it);	}
	inline void Decode_ListOfYMD_Date_packed (DataDecoder & d, std::vector<YMD_Date_packed > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_YMD_Date_packed (d,l[i]); }

	inline void Encode_MarketCharacteristics (DataEncoder & e, MarketCharacteristics const & v)
	{
		Encode_FOSMarketId (e,v.getMarketId());
		Encode_ISOMarketId (e,v.getMIC());
		Encode_String (e,v.getTimeZone());
		Encode_ISOCountryCode (e,v.getCountry());
		Encode_uint32 (e,v.getNbMaxInstruments());
		Encode_ListOfTradingSessionCharacteristics (e,v.getSessions());
		Encode_ListOfYMD_Date_packed (e,v.getLocalClosedDays());
	}
	inline void Decode_MarketCharacteristics (DataDecoder & d, MarketCharacteristics & v)
	{
		Decode_FOSMarketId (d,v.getMarketId());
		Decode_ISOMarketId (d,v.getMIC());
		Decode_String (d,v.getTimeZone());
		Decode_ISOCountryCode (d,v.getCountry());
		Decode_uint32 (d,v.getNbMaxInstruments());
		Decode_ListOfTradingSessionCharacteristics (d,v.getSessions());
		Decode_ListOfYMD_Date_packed (d,v.getLocalClosedDays());
	}

	inline void Encode_ListOfMarketCharacteristics (DataEncoder & e, std::vector<MarketCharacteristics > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MarketCharacteristics >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MarketCharacteristics (e,*it);	}
	inline void Decode_ListOfMarketCharacteristics (DataDecoder & d, std::vector<MarketCharacteristics > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MarketCharacteristics (d,l[i]); }

	inline void Encode_MarketTimesAndDates (DataEncoder & e, MarketTimesAndDates const & v)
	{
		Encode_int32 (e,v.getMarketUTCTime2MarketLocalTime_minutes());
		Encode_int32 (e,v.getMarketUTCTime2ServerUTCTime_milliseconds());
	}
	inline void Decode_MarketTimesAndDates (DataDecoder & d, MarketTimesAndDates & v)
	{
		Decode_int32 (d,v.getMarketUTCTime2MarketLocalTime_minutes());
		Decode_int32 (d,v.getMarketUTCTime2ServerUTCTime_milliseconds());
	}

	inline void Encode_MarketStatus (DataEncoder & e, MarketStatus const & v)
	{
		Encode_FOSMarketId (e,v.getMarketId());
		Encode_TradingSessionStatus (e,v.getCurrentSessionStatus());
		Encode_MarketTimesAndDates (e,v.getCurrentTimesAndDates());
	}
	inline void Decode_MarketStatus (DataDecoder & d, MarketStatus & v)
	{
		Decode_FOSMarketId (d,v.getMarketId());
		Decode_TradingSessionStatus (d,v.getCurrentSessionStatus());
		Decode_MarketTimesAndDates (d,v.getCurrentTimesAndDates());
	}

	inline void Encode_ListOfMarketStatus (DataEncoder & e, std::vector<MarketStatus > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MarketStatus >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MarketStatus (e,*it);	}
	inline void Decode_ListOfMarketStatus (DataDecoder & d, std::vector<MarketStatus > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MarketStatus (d,l[i]); }

	inline void Encode_MarketNews (DataEncoder & e, MarketNews const & v)
	{
		Encode_FOSMarketId (e,v.getOrigMarketId());
		Encode_Timestamp (e,v.getOrigUTCTime());
		Encode_FIXMarketNewsUrgency (e,v.getUrgency());
		Encode_String (e,v.getHeadline());
		Encode_String (e,v.getURLLink());
		Encode_String (e,v.getContent());
		Encode_ListOfPolymorphicInstrumentCode (e,v.getRelatedInstruments());
	}
	inline void Decode_MarketNews (DataDecoder & d, MarketNews & v)
	{
		Decode_FOSMarketId (d,v.getOrigMarketId());
		Decode_Timestamp (d,v.getOrigUTCTime());
		Decode_FIXMarketNewsUrgency (d,v.getUrgency());
		Decode_String (d,v.getHeadline());
		Decode_String (d,v.getURLLink());
		Decode_String (d,v.getContent());
		Decode_ListOfPolymorphicInstrumentCode (d,v.getRelatedInstruments());
	}

	inline void Encode_MarketBranchId (DataEncoder & e, MarketBranchId const & v)
	{
		Encode_FOSMarketId (e,v.getMarketId());
		Encode_String (e,v.getSecurityType());
		Encode_CFICode (e,v.getCFICode());
	}
	inline void Decode_MarketBranchId (DataDecoder & d, MarketBranchId & v)
	{
		Decode_FOSMarketId (d,v.getMarketId());
		Decode_String (d,v.getSecurityType());
		Decode_CFICode (d,v.getCFICode());
	}

	inline void Encode_ListOfMarketBranchId (DataEncoder & e, std::vector<MarketBranchId > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MarketBranchId >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MarketBranchId (e,*it);	}
	inline void Decode_ListOfMarketBranchId (DataDecoder & d, std::vector<MarketBranchId > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MarketBranchId (d,l[i]); }

	inline void Encode_EntitledMarketBranchId (DataEncoder & e, EntitledMarketBranchId const & v)
	{
		Encode_int32 (e,v.getSourceId());
		Encode_FOSMarketId (e,v.getMarketId());
		Encode_String (e,v.getSecurityType());
		Encode_CFICode (e,v.getCFICode());
		Encode_int32 (e,v.getEntitlementId());
	}
	inline void Decode_EntitledMarketBranchId (DataDecoder & d, EntitledMarketBranchId & v)
	{
		Decode_int32 (d,v.getSourceId());
		Decode_FOSMarketId (d,v.getMarketId());
		Decode_String (d,v.getSecurityType());
		Decode_CFICode (d,v.getCFICode());
		Decode_int32 (d,v.getEntitlementId());
	}

	inline void Encode_ListOfEntitledMarketBranchId (DataEncoder & e, std::vector<EntitledMarketBranchId > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<EntitledMarketBranchId >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_EntitledMarketBranchId (e,*it);	}
	inline void Decode_ListOfEntitledMarketBranchId (DataDecoder & d, std::vector<EntitledMarketBranchId > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_EntitledMarketBranchId (d,l[i]); }

	inline void Encode_MarketBranchIdExtended (DataEncoder & e, MarketBranchIdExtended const & v)
	{
		Encode_FOSMarketId (e,v.getMarketId());
		Encode_String (e,v.getSecurityType());
		Encode_CFICode (e,v.getCFICode());
		Encode_int32 (e,v.getEntitlementId());
	}
	inline void Decode_MarketBranchIdExtended (DataDecoder & d, MarketBranchIdExtended & v)
	{
		Decode_FOSMarketId (d,v.getMarketId());
		Decode_String (d,v.getSecurityType());
		Decode_CFICode (d,v.getCFICode());
		Decode_int32 (d,v.getEntitlementId());
	}

	inline void Encode_ListOfMarketBranchIdExtended (DataEncoder & e, std::vector<MarketBranchIdExtended > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MarketBranchIdExtended >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MarketBranchIdExtended (e,*it);	}
	inline void Decode_ListOfMarketBranchIdExtended (DataDecoder & d, std::vector<MarketBranchIdExtended > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MarketBranchIdExtended (d,l[i]); }

	inline void Encode_BranchAndInstrument (DataEncoder & e, BranchAndInstrument const & v)
	{
		Encode_EntitledMarketBranchId (e,v.getBranch());
		Encode_FOSInstrumentCode (e,v.getCode());
	}
	inline void Decode_BranchAndInstrument (DataDecoder & d, BranchAndInstrument & v)
	{
		Decode_EntitledMarketBranchId (d,v.getBranch());
		Decode_FOSInstrumentCode (d,v.getCode());
	}

	inline void Encode_ListOfBranchAndInstrument (DataEncoder & e, std::vector<BranchAndInstrument > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<BranchAndInstrument >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_BranchAndInstrument (e,*it);	}
	inline void Decode_ListOfBranchAndInstrument (DataDecoder & d, std::vector<BranchAndInstrument > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_BranchAndInstrument (d,l[i]); }

	inline void Encode_MarketBranchContent (DataEncoder & e, MarketBranchContent const & v)
	{
		Encode_MarketBranchId (e,v.getBranchId());
		Encode_uint32 (e,v.getQuantity());
	}
	inline void Decode_MarketBranchContent (DataDecoder & d, MarketBranchContent & v)
	{
		Decode_MarketBranchId (d,v.getBranchId());
		Decode_uint32 (d,v.getQuantity());
	}

	inline void Encode_ListOfMarketBranchContent (DataEncoder & e, std::vector<MarketBranchContent > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MarketBranchContent >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MarketBranchContent (e,*it);	}
	inline void Decode_ListOfMarketBranchContent (DataDecoder & d, std::vector<MarketBranchContent > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MarketBranchContent (d,l[i]); }

	inline void Encode_EntitledMarketBranchContent (DataEncoder & e, EntitledMarketBranchContent const & v)
	{
		Encode_EntitledMarketBranchId (e,v.getBranchId());
		Encode_uint32 (e,v.getQuantity());
	}
	inline void Decode_EntitledMarketBranchContent (DataDecoder & d, EntitledMarketBranchContent & v)
	{
		Decode_EntitledMarketBranchId (d,v.getBranchId());
		Decode_uint32 (d,v.getQuantity());
	}

	inline void Encode_ListOfEntitledMarketBranchContent (DataEncoder & e, std::vector<EntitledMarketBranchContent > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<EntitledMarketBranchContent >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_EntitledMarketBranchContent (e,*it);	}
	inline void Decode_ListOfEntitledMarketBranchContent (DataDecoder & d, std::vector<EntitledMarketBranchContent > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_EntitledMarketBranchContent (d,l[i]); }

	inline void Encode_MarketContent (DataEncoder & e, MarketContent const & v)
	{
		Encode_FOSMarketId (e,v.getMarketId());
		Encode_ListOfMarketBranchContent (e,v.getContent());
	}
	inline void Decode_MarketContent (DataDecoder & d, MarketContent & v)
	{
		Decode_FOSMarketId (d,v.getMarketId());
		Decode_ListOfMarketBranchContent (d,v.getContent());
	}

	inline void Encode_ListOfMarketContent (DataEncoder & e, std::vector<MarketContent > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MarketContent >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MarketContent (e,*it);	}
	inline void Decode_ListOfMarketContent (DataDecoder & d, std::vector<MarketContent > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MarketContent (d,l[i]); }

	inline void Encode_EntitledMarketContent (DataEncoder & e, EntitledMarketContent const & v)
	{
		Encode_FOSMarketId (e,v.getMarketId());
		Encode_ListOfEntitledMarketBranchContent (e,v.getContent());
	}
	inline void Decode_EntitledMarketContent (DataDecoder & d, EntitledMarketContent & v)
	{
		Decode_FOSMarketId (d,v.getMarketId());
		Decode_ListOfEntitledMarketBranchContent (d,v.getContent());
	}

	inline void Encode_ListOfEntitledMarketContent (DataEncoder & e, std::vector<EntitledMarketContent > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<EntitledMarketContent >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_EntitledMarketContent (e,*it);	}
	inline void Decode_ListOfEntitledMarketContent (DataDecoder & d, std::vector<EntitledMarketContent > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_EntitledMarketContent (d,l[i]); }

	inline void Encode_InstrumentCharacteristics (DataEncoder & e, InstrumentCharacteristics const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_ListOfReferentialAttribute (e,v.getAttributes());
	}
	inline void Decode_InstrumentCharacteristics (DataDecoder & d, InstrumentCharacteristics & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_ListOfReferentialAttribute (d,v.getAttributes());
	}

	inline void Encode_ListOfInstrumentCharacteristics (DataEncoder & e, std::vector<InstrumentCharacteristics > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<InstrumentCharacteristics >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_InstrumentCharacteristics (e,*it);	}
	inline void Decode_ListOfInstrumentCharacteristics (DataDecoder & d, std::vector<InstrumentCharacteristics > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_InstrumentCharacteristics (d,l[i]); }

	inline void Encode_InstrumentStatus (DataEncoder & e, InstrumentStatus const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_ListOfQuotationVariable (e,v.getValues());
		Encode_OrderBook (e,v.getOrderBook());
	}
	inline void Decode_InstrumentStatus (DataDecoder & d, InstrumentStatus & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_ListOfQuotationVariable (d,v.getValues());
		Decode_OrderBook (d,v.getOrderBook());
	}

	inline void Encode_ListOfInstrumentStatus (DataEncoder & e, std::vector<InstrumentStatus > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<InstrumentStatus >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_InstrumentStatus (e,*it);	}
	inline void Decode_ListOfInstrumentStatus (DataDecoder & d, std::vector<InstrumentStatus > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_InstrumentStatus (d,l[i]); }

	inline void Encode_InstrumentStatusL1 (DataEncoder & e, InstrumentStatusL1 const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_ListOfQuotationVariable (e,v.getValues());
		Encode_OrderBookBestLimitsExt (e,v.getBestLimits());
	}
	inline void Decode_InstrumentStatusL1 (DataDecoder & d, InstrumentStatusL1 & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_ListOfQuotationVariable (d,v.getValues());
		Decode_OrderBookBestLimitsExt (d,v.getBestLimits());
	}

	inline void Encode_ListOfInstrumentStatusL1 (DataEncoder & e, std::vector<InstrumentStatusL1 > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<InstrumentStatusL1 >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_InstrumentStatusL1 (e,*it);	}
	inline void Decode_ListOfInstrumentStatusL1 (DataDecoder & d, std::vector<InstrumentStatusL1 > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_InstrumentStatusL1 (d,l[i]); }

	inline void Encode_InstrumentStatusL2 (DataEncoder & e, InstrumentStatusL2 const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_OrderBook (e,v.getOrderBook());
	}
	inline void Decode_InstrumentStatusL2 (DataDecoder & d, InstrumentStatusL2 & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_OrderBook (d,v.getOrderBook());
	}

	inline void Encode_ListOfInstrumentStatusL2 (DataEncoder & e, std::vector<InstrumentStatusL2 > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<InstrumentStatusL2 >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_InstrumentStatusL2 (e,*it);	}
	inline void Decode_ListOfInstrumentStatusL2 (DataDecoder & d, std::vector<InstrumentStatusL2 > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_InstrumentStatusL2 (d,l[i]); }

	inline void Encode_InstrumentData (DataEncoder & e, InstrumentData const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_ListOfReferentialAttribute (e,v.getAttributes());
		Encode_ListOfQuotationVariable (e,v.getValues());
		Encode_OrderBook (e,v.getOrderBook());
	}
	inline void Decode_InstrumentData (DataDecoder & d, InstrumentData & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_ListOfReferentialAttribute (d,v.getAttributes());
		Decode_ListOfQuotationVariable (d,v.getValues());
		Decode_OrderBook (d,v.getOrderBook());
	}

	inline void Encode_ListOfInstrumentData (DataEncoder & e, std::vector<InstrumentData > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<InstrumentData >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_InstrumentData (e,*it);	}
	inline void Decode_ListOfInstrumentData (DataDecoder & d, std::vector<InstrumentData > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_InstrumentData (d,l[i]); }

	inline void Encode_IntradayHistoryPoint (DataEncoder & e, IntradayHistoryPoint const & v)
	{
		Encode_FOSTradingSessionId (e,v.getSessionId());
		Encode_TransactionOrPrice (e,v.getTrade());
	}
	inline void Decode_IntradayHistoryPoint (DataDecoder & d, IntradayHistoryPoint & v)
	{
		Decode_FOSTradingSessionId (d,v.getSessionId());
		Decode_TransactionOrPrice (d,v.getTrade());
	}

	inline void Encode_ListOfIntradayHistoryPoint (DataEncoder & e, std::vector<IntradayHistoryPoint > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<IntradayHistoryPoint >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_IntradayHistoryPoint (e,*it);	}
	inline void Decode_ListOfIntradayHistoryPoint (DataDecoder & d, std::vector<IntradayHistoryPoint > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_IntradayHistoryPoint (d,l[i]); }

	inline void Encode_IntradayHistoryPoint2 (DataEncoder & e, IntradayHistoryPoint2 const & v)
	{
		Encode_float64 (e,v.getPrice());
		Encode_float64 (e,v.getLastTradeQty());
		Encode_Timestamp (e,v.getMarketUTCTime());
		Encode_Timestamp (e,v.getServerUTCTime());
		Encode_QuotationContentMask (e,v.getContentMask());
		Encode_uint32 (e,v.getTradeConditionIndex());
	}
	inline void Decode_IntradayHistoryPoint2 (DataDecoder & d, IntradayHistoryPoint2 & v)
	{
		Decode_float64 (d,v.getPrice());
		Decode_float64 (d,v.getLastTradeQty());
		Decode_Timestamp (d,v.getMarketUTCTime());
		Decode_Timestamp (d,v.getServerUTCTime());
		Decode_QuotationContentMask (d,v.getContentMask());
		Decode_uint32 (d,v.getTradeConditionIndex());
	}

	inline void Encode_ListOfIntradayHistoryPoint2 (DataEncoder & e, std::vector<IntradayHistoryPoint2 > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<IntradayHistoryPoint2 >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_IntradayHistoryPoint2 (e,*it);	}
	inline void Decode_ListOfIntradayHistoryPoint2 (DataDecoder & d, std::vector<IntradayHistoryPoint2 > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_IntradayHistoryPoint2 (d,l[i]); }

	inline void Encode_IntradayHistoryPointExtended (DataEncoder & e, IntradayHistoryPointExtended const & v)
	{
		Encode_float64 (e,v.getPrice());
		Encode_float64 (e,v.getLastTradeQty());
		Encode_Timestamp (e,v.getMarketUTCTimestamp());
		Encode_Timestamp (e,v.getServerUTCTimestamp());
		Encode_QuotationContentMask (e,v.getContentMask());
		Encode_uint32 (e,v.getTradeConditionIndex());
		Encode_ListOfQuotationVariable (e,v.getProperties());
	}
	inline void Decode_IntradayHistoryPointExtended (DataDecoder & d, IntradayHistoryPointExtended & v)
	{
		Decode_float64 (d,v.getPrice());
		Decode_float64 (d,v.getLastTradeQty());
		Decode_Timestamp (d,v.getMarketUTCTimestamp());
		Decode_Timestamp (d,v.getServerUTCTimestamp());
		Decode_QuotationContentMask (d,v.getContentMask());
		Decode_uint32 (d,v.getTradeConditionIndex());
		Decode_ListOfQuotationVariable (d,v.getProperties());
	}

	inline void Encode_ListOfIntradayHistoryPointExtended (DataEncoder & e, std::vector<IntradayHistoryPointExtended > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<IntradayHistoryPointExtended >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_IntradayHistoryPointExtended (e,*it);	}
	inline void Decode_ListOfIntradayHistoryPointExtended (DataDecoder & d, std::vector<IntradayHistoryPointExtended > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_IntradayHistoryPointExtended (d,l[i]); }

	inline void Encode_DailyHistoryPoint (DataEncoder & e, DailyHistoryPoint const & v)
	{
		Encode_YMD_Date_packed (e,v.getLocalDate());
		Encode_DailyValues (e,v.getValues());
	}
	inline void Decode_DailyHistoryPoint (DataDecoder & d, DailyHistoryPoint & v)
	{
		Decode_YMD_Date_packed (d,v.getLocalDate());
		Decode_DailyValues (d,v.getValues());
	}

	inline void Encode_ListOfDailyHistoryPoint (DataEncoder & e, std::vector<DailyHistoryPoint > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<DailyHistoryPoint >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_DailyHistoryPoint (e,*it);	}
	inline void Decode_ListOfDailyHistoryPoint (DataDecoder & d, std::vector<DailyHistoryPoint > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_DailyHistoryPoint (d,l[i]); }

	inline void Encode_DailyHistoryPointExt (DataEncoder & e, DailyHistoryPointExt const & v)
	{
		Encode_YMD_Date_packed (e,v.getDate());
		Encode_FOSTradingSessionId (e,v.getTradingSessionId());
		Encode_float64 (e,v.getOpen());
		Encode_float64 (e,v.getHigh());
		Encode_float64 (e,v.getLow());
		Encode_float64 (e,v.getClose());
		Encode_float64 (e,v.getVolumeTraded());
		Encode_float64 (e,v.getAssetTraded());
		Encode_ListOfQuotationVariable (e,v.getOtherValues());
	}
	inline void Decode_DailyHistoryPointExt (DataDecoder & d, DailyHistoryPointExt & v)
	{
		Decode_YMD_Date_packed (d,v.getDate());
		Decode_FOSTradingSessionId (d,v.getTradingSessionId());
		Decode_float64 (d,v.getOpen());
		Decode_float64 (d,v.getHigh());
		Decode_float64 (d,v.getLow());
		Decode_float64 (d,v.getClose());
		Decode_float64 (d,v.getVolumeTraded());
		Decode_float64 (d,v.getAssetTraded());
		Decode_ListOfQuotationVariable (d,v.getOtherValues());
	}

	inline void Encode_ListOfDailyHistoryPointExt (DataEncoder & e, std::vector<DailyHistoryPointExt > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<DailyHistoryPointExt >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_DailyHistoryPointExt (e,*it);	}
	inline void Decode_ListOfDailyHistoryPointExt (DataDecoder & d, std::vector<DailyHistoryPointExt > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_DailyHistoryPointExt (d,l[i]); }

	inline void Encode_TradeConditionsDictionaryEntry (DataEncoder & e, TradeConditionsDictionaryEntry const & v)
	{
		Encode_uint32 (e,v.getIndex());
		Encode_ListOfQuotationContextFlag (e,v.getValue());
	}
	inline void Decode_TradeConditionsDictionaryEntry (DataDecoder & d, TradeConditionsDictionaryEntry & v)
	{
		Decode_uint32 (d,v.getIndex());
		Decode_ListOfQuotationContextFlag (d,v.getValue());
	}

	inline void Encode_ListOfTradeConditionsDictionaryEntry (DataEncoder & e, std::vector<TradeConditionsDictionaryEntry > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<TradeConditionsDictionaryEntry >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_TradeConditionsDictionaryEntry (e,*it);	}
	inline void Decode_ListOfTradeConditionsDictionaryEntry (DataDecoder & d, std::vector<TradeConditionsDictionaryEntry > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_TradeConditionsDictionaryEntry (d,l[i]); }

	inline void Encode_VariableIncrementPriceBand (DataEncoder & e, VariableIncrementPriceBand const & v)
	{
		Encode_bool (e,v.getInclusive());
		Encode_float64 (e,v.getLowerBoundary());
		Encode_float64 (e,v.getPriceIncrement());
	}
	inline void Decode_VariableIncrementPriceBand (DataDecoder & d, VariableIncrementPriceBand & v)
	{
		Decode_bool (d,v.getInclusive());
		Decode_float64 (d,v.getLowerBoundary());
		Decode_float64 (d,v.getPriceIncrement());
	}

	inline void Encode_ListOfVariableIncrementPriceBand (DataEncoder & e, std::vector<VariableIncrementPriceBand > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<VariableIncrementPriceBand >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_VariableIncrementPriceBand (e,*it);	}
	inline void Decode_ListOfVariableIncrementPriceBand (DataDecoder & d, std::vector<VariableIncrementPriceBand > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_VariableIncrementPriceBand (d,l[i]); }

	inline void Encode_VariableIncrementPriceBandTable (DataEncoder & e, VariableIncrementPriceBandTable const & v)
	{
		Encode_uint32 (e,v.getTableId());
		Encode_String (e,v.getDescription());
		Encode_ListOfVariableIncrementPriceBand (e,v.getPriceBands());
	}
	inline void Decode_VariableIncrementPriceBandTable (DataDecoder & d, VariableIncrementPriceBandTable & v)
	{
		Decode_uint32 (d,v.getTableId());
		Decode_String (d,v.getDescription());
		Decode_ListOfVariableIncrementPriceBand (d,v.getPriceBands());
	}

	inline void Encode_ListOfVariableIncrementPriceBandTable (DataEncoder & e, std::vector<VariableIncrementPriceBandTable > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<VariableIncrementPriceBandTable >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_VariableIncrementPriceBandTable (e,*it);	}
	inline void Decode_ListOfVariableIncrementPriceBandTable (DataDecoder & d, std::vector<VariableIncrementPriceBandTable > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_VariableIncrementPriceBandTable (d,l[i]); }

	inline void Encode_NewsHeadline	(DataEncoder & e, NewsHeadline const & v) 	{ Encode_String (e,v); }
	inline void Decode_NewsHeadline	(DataDecoder & d, NewsHeadline & v) 	{ Decode_String (d,v); }

	inline void Encode_NewsKeyword	(DataEncoder & e, NewsKeyword const & v) 	{ Encode_String (e,v); }
	inline void Decode_NewsKeyword	(DataDecoder & d, NewsKeyword & v) 	{ Decode_String (d,v); }

	inline void Encode_NewsSubmitter	(DataEncoder & e, NewsSubmitter const & v) 	{ Encode_String (e,v); }
	inline void Decode_NewsSubmitter	(DataDecoder & d, NewsSubmitter & v) 	{ Decode_String (d,v); }

	inline void Encode_ListOfNewsKeyword (DataEncoder & e, std::vector<NewsKeyword > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<NewsKeyword >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_NewsKeyword (e,*it);	}
	inline void Decode_ListOfNewsKeyword (DataDecoder & d, std::vector<NewsKeyword > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_NewsKeyword (d,l[i]); }

	inline void Encode_CompanyId	(DataEncoder & e, CompanyId const & v) 	{ Encode_String (e,v); }
	inline void Decode_CompanyId	(DataDecoder & d, CompanyId & v) 	{ Decode_String (d,v); }

	inline void Encode_ListOfCompanyId (DataEncoder & e, std::vector<CompanyId > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<CompanyId >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_CompanyId (e,*it);	}
	inline void Decode_ListOfCompanyId (DataDecoder & d, std::vector<CompanyId > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_CompanyId (d,l[i]); }

	inline void Encode_NewsBody	(DataEncoder & e, NewsBody const & v) 	{ Encode_String (e,v); }
	inline void Decode_NewsBody	(DataDecoder & d, NewsBody & v) 	{ Decode_String (d,v); }

	inline void Encode_NewsURL	(DataEncoder & e, NewsURL const & v) 	{ Encode_String (e,v); }
	inline void Decode_NewsURL	(DataDecoder & d, NewsURL & v) 	{ Decode_String (d,v); }

	inline void Encode_NewsId	(DataEncoder & e, NewsId const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_NewsId	(DataDecoder & d, NewsId & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_ListOfNewsId (DataEncoder & e, std::vector<NewsId > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<NewsId >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_NewsId (e,*it);	}
	inline void Decode_ListOfNewsId (DataDecoder & d, std::vector<NewsId > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_NewsId (d,l[i]); }

	inline void Encode_NewsContent (DataEncoder & e, NewsContent const & v)
	{
		Encode_NewsCategory (e,v.getCategory());
		Encode_NewsType (e,v.getType());
		Encode_NewsSubmitter (e,v.getSubmitter());
		Encode_ISOLanguageCode (e,v.getLanguage());
		Encode_Timestamp (e,v.getSubmitDate());
		Encode_Timestamp (e,v.getModifyDate());
		Encode_Timestamp (e,v.getExpirationDate());
		Encode_NewsHeadline (e,v.getHeadline());
		Encode_ListOfNewsKeyword (e,v.getKeywords());
		Encode_FOSMarketId (e,v.getRelatedMarket());
		Encode_ListOfCompanyId (e,v.getRelatedCompanies());
		Encode_ListOfFOSInstrumentCode (e,v.getRelatedInstruments());
		Encode_NewsBody (e,v.getBody());
		Encode_NewsURL (e,v.getURL());
	}
	inline void Decode_NewsContent (DataDecoder & d, NewsContent & v)
	{
		Decode_NewsCategory (d,v.getCategory());
		Decode_NewsType (d,v.getType());
		Decode_NewsSubmitter (d,v.getSubmitter());
		Decode_ISOLanguageCode (d,v.getLanguage());
		Decode_Timestamp (d,v.getSubmitDate());
		Decode_Timestamp (d,v.getModifyDate());
		Decode_Timestamp (d,v.getExpirationDate());
		Decode_NewsHeadline (d,v.getHeadline());
		Decode_ListOfNewsKeyword (d,v.getKeywords());
		Decode_FOSMarketId (d,v.getRelatedMarket());
		Decode_ListOfCompanyId (d,v.getRelatedCompanies());
		Decode_ListOfFOSInstrumentCode (d,v.getRelatedInstruments());
		Decode_NewsBody (d,v.getBody());
		Decode_NewsURL (d,v.getURL());
	}

	inline void Encode_NewsFieldValue	(DataEncoder & e, NewsFieldValue const & v) 	{ Encode_Any (e,v); }
	inline void Decode_NewsFieldValue	(DataDecoder & d, NewsFieldValue & v) 	{ Decode_Any (d,v); }

	inline void Encode_NewsField (DataEncoder & e, NewsField const & v)
	{
		Encode_NewsFieldId (e,v.getFieldId());
		Encode_NewsFieldValue (e,v.getFieldValue());
	}
	inline void Decode_NewsField (DataDecoder & d, NewsField & v)
	{
		Decode_NewsFieldId (d,v.getFieldId());
		Decode_NewsFieldValue (d,v.getFieldValue());
	}

	inline void Encode_ListOfNewsField (DataEncoder & e, std::vector<NewsField > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<NewsField >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_NewsField (e,*it);	}
	inline void Decode_ListOfNewsField (DataDecoder & d, std::vector<NewsField > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_NewsField (d,l[i]); }

	inline void Encode_News (DataEncoder & e, News const & v)
	{
		Encode_NewsId (e,v.getId());
		Encode_NewsContent (e,v.getContent());
	}
	inline void Decode_News (DataDecoder & d, News & v)
	{
		Decode_NewsId (d,v.getId());
		Decode_NewsContent (d,v.getContent());
	}

	inline void Encode_ListOfNews (DataEncoder & e, std::vector<News > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<News >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_News (e,*it);	}
	inline void Decode_ListOfNews (DataDecoder & d, std::vector<News > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_News (d,l[i]); }

	inline void Encode_NewsItemId	(DataEncoder & e, NewsItemId const & v) 	{ Encode_TagNumber (e,v); }
	inline void Decode_NewsItemId	(DataDecoder & d, NewsItemId & v) 	{ Decode_TagNumber (d,v); }

	inline void Encode_ListOfNewsItemId (DataEncoder & e, std::vector<NewsItemId > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<NewsItemId >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_NewsItemId (e,*it);	}
	inline void Decode_ListOfNewsItemId (DataDecoder & d, std::vector<NewsItemId > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_NewsItemId (d,l[i]); }

	inline void Encode_NewsItem	(DataEncoder & e, NewsItem const & v) 	{ Encode_TagNumAndValue (e,v); }
	inline void Decode_NewsItem	(DataDecoder & d, NewsItem & v) 	{ Decode_TagNumAndValue (d,v); }

	inline void Encode_ListOfNewsItem (DataEncoder & e, std::vector<NewsItem > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<NewsItem >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_NewsItem (e,*it);	}
	inline void Decode_ListOfNewsItem (DataDecoder & d, std::vector<NewsItem > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_NewsItem (d,l[i]); }

	inline void Encode_NewsUuid	(DataEncoder & e, NewsUuid const & v) 	{ Encode_FOSUuid (e,v); }
	inline void Decode_NewsUuid	(DataDecoder & d, NewsUuid & v) 	{ Decode_FOSUuid (d,v); }

	inline void Encode_ListOfNewsUuid (DataEncoder & e, std::vector<NewsUuid > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<NewsUuid >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_NewsUuid (e,*it);	}
	inline void Decode_ListOfNewsUuid (DataDecoder & d, std::vector<NewsUuid > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_NewsUuid (d,l[i]); }

	inline void Encode_NewsDetails (DataEncoder & e, NewsDetails const & v)
	{
		Encode_Timestamp (e,v.getServerUTCTime());
		Encode_ListOfNewsItem (e,v.getItems());
	}
	inline void Decode_NewsDetails (DataDecoder & d, NewsDetails & v)
	{
		Decode_Timestamp (d,v.getServerUTCTime());
		Decode_ListOfNewsItem (d,v.getItems());
	}

	inline void Encode_NewsData (DataEncoder & e, NewsData const & v)
	{
		Encode_NewsEventType (e,v.getType());
		Encode_NewsUuid (e,v.getId());
		Encode_Timestamp (e,v.getServerUTCTime());
		Encode_ListOfNewsItem (e,v.getItems());
	}
	inline void Decode_NewsData (DataDecoder & d, NewsData & v)
	{
		Decode_NewsEventType (d,v.getType());
		Decode_NewsUuid (d,v.getId());
		Decode_Timestamp (d,v.getServerUTCTime());
		Decode_ListOfNewsItem (d,v.getItems());
	}

	inline void Encode_ListOfNewsData (DataEncoder & e, std::vector<NewsData > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<NewsData >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_NewsData (e,*it);	}
	inline void Decode_ListOfNewsData (DataDecoder & d, std::vector<NewsData > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_NewsData (d,l[i]); }

	inline void Encode_UserGroupId	(DataEncoder & e, UserGroupId const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_UserGroupId	(DataDecoder & d, UserGroupId & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_UserId	(DataEncoder & e, UserId const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_UserId	(DataDecoder & d, UserId & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_ListOfUserId (DataEncoder & e, std::vector<UserId > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<UserId >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_UserId (e,*it);	}
	inline void Decode_ListOfUserId (DataDecoder & d, std::vector<UserId > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_UserId (d,l[i]); }

	inline void Encode_UserGroupCharacteristics (DataEncoder & e, UserGroupCharacteristics const & v)
	{
		Encode_UserGroupId (e,v.getId());
		Encode_String (e,v.getName());
		Encode_ListOfFeedOSCmd (e,v.getAllowedRequests());
	}
	inline void Decode_UserGroupCharacteristics (DataDecoder & d, UserGroupCharacteristics & v)
	{
		Decode_UserGroupId (d,v.getId());
		Decode_String (d,v.getName());
		Decode_ListOfFeedOSCmd (d,v.getAllowedRequests());
	}

	inline void Encode_ListOfUserGroupCharacteristics (DataEncoder & e, std::vector<UserGroupCharacteristics > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<UserGroupCharacteristics >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_UserGroupCharacteristics (e,*it);	}
	inline void Decode_ListOfUserGroupCharacteristics (DataDecoder & d, std::vector<UserGroupCharacteristics > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_UserGroupCharacteristics (d,l[i]); }

	inline void Encode_MarketAccessFeature (DataEncoder & e, MarketAccessFeature const & v)
	{
		Encode_String (e,v.getName());
		Encode_Any (e,v.getValue());
	}
	inline void Decode_MarketAccessFeature (DataDecoder & d, MarketAccessFeature & v)
	{
		Decode_String (d,v.getName());
		Decode_Any (d,v.getValue());
	}

	inline void Encode_ListOfMarketAccessFeature (DataEncoder & e, std::vector<MarketAccessFeature > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MarketAccessFeature >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MarketAccessFeature (e,*it);	}
	inline void Decode_ListOfMarketAccessFeature (DataDecoder & d, std::vector<MarketAccessFeature > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MarketAccessFeature (d,l[i]); }

	inline void Encode_MarketAccessPermissions (DataEncoder & e, MarketAccessPermissions const & v)
	{
		Encode_int32 (e,v.getInternalSourceId());
		Encode_MarketBranchId (e,v.getBranchIdPattern());
		Encode_ListOfMarketAccessFeature (e,v.getFeatures());
	}
	inline void Decode_MarketAccessPermissions (DataDecoder & d, MarketAccessPermissions & v)
	{
		Decode_int32 (d,v.getInternalSourceId());
		Decode_MarketBranchId (d,v.getBranchIdPattern());
		Decode_ListOfMarketAccessFeature (d,v.getFeatures());
	}

	inline void Encode_ListOfMarketAccessPermissions (DataEncoder & e, std::vector<MarketAccessPermissions > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MarketAccessPermissions >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MarketAccessPermissions (e,*it);	}
	inline void Decode_ListOfMarketAccessPermissions (DataDecoder & d, std::vector<MarketAccessPermissions > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MarketAccessPermissions (d,l[i]); }

	inline void Encode_UserCharacteristics (DataEncoder & e, UserCharacteristics const & v)
	{
		Encode_UserId (e,v.getId());
		Encode_UserGroupId (e,v.getGID());
		Encode_String (e,v.getName());
		Encode_String (e,v.getPassword());
		Encode_String (e,v.getLocation());
		Encode_uint16 (e,v.getMaxConnections());
		Encode_Timestamp (e,v.getExpirationDate());
		Encode_ListOfMarketAccessPermissions (e,v.getMarketAccess());
	}
	inline void Decode_UserCharacteristics (DataDecoder & d, UserCharacteristics & v)
	{
		Decode_UserId (d,v.getId());
		Decode_UserGroupId (d,v.getGID());
		Decode_String (d,v.getName());
		Decode_String (d,v.getPassword());
		Decode_String (d,v.getLocation());
		Decode_uint16 (d,v.getMaxConnections());
		Decode_Timestamp (d,v.getExpirationDate());
		Decode_ListOfMarketAccessPermissions (d,v.getMarketAccess());
	}

	inline void Encode_ListOfUserCharacteristics (DataEncoder & e, std::vector<UserCharacteristics > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<UserCharacteristics >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_UserCharacteristics (e,*it);	}
	inline void Decode_ListOfUserCharacteristics (DataDecoder & d, std::vector<UserCharacteristics > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_UserCharacteristics (d,l[i]); }

	inline void Encode_UserStat (DataEncoder & e, UserStat const & v)
	{
		Encode_UserId (e,v.getId());
		Encode_String (e,v.getName());
		Encode_uint16 (e,v.getNbConnections());
	}
	inline void Decode_UserStat (DataDecoder & d, UserStat & v)
	{
		Decode_UserId (d,v.getId());
		Decode_String (d,v.getName());
		Decode_uint16 (d,v.getNbConnections());
	}

	inline void Encode_MarketSheetLevel	(DataEncoder & e, MarketSheetLevel const & v) 	{ Encode_uint16 (e,v); }
	inline void Decode_MarketSheetLevel	(DataDecoder & d, MarketSheetLevel & v) 	{ Decode_uint16 (d,v); }

	inline void Encode_MarketSheetEntry (DataEncoder & e, MarketSheetEntry const & v)
	{
		Encode_String (e,v.getOrderID());
		Encode_float64 (e,v.getPrice());
		Encode_float64 (e,v.getQty());
	}
	inline void Decode_MarketSheetEntry (DataDecoder & d, MarketSheetEntry & v)
	{
		Decode_String (d,v.getOrderID());
		Decode_float64 (d,v.getPrice());
		Decode_float64 (d,v.getQty());
	}

	inline void Encode_MarketSheetEntryAndContext (DataEncoder & e, MarketSheetEntryAndContext const & v)
	{
		Encode_MarketSheetEntry (e,v.getOrder());
		Encode_ListOfQuotationContextFlag (e,v.getContext());
	}
	inline void Decode_MarketSheetEntryAndContext (DataDecoder & d, MarketSheetEntryAndContext & v)
	{
		Decode_MarketSheetEntry (d,v.getOrder());
		Decode_ListOfQuotationContextFlag (d,v.getContext());
	}

	inline void Encode_ListOfMarketSheetEntryAndContext (DataEncoder & e, std::vector<MarketSheetEntryAndContext > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<MarketSheetEntryAndContext >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_MarketSheetEntryAndContext (e,*it);	}
	inline void Decode_ListOfMarketSheetEntryAndContext (DataDecoder & d, std::vector<MarketSheetEntryAndContext > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_MarketSheetEntryAndContext (d,l[i]); }

	inline void Encode_MarketSheet (DataEncoder & e, MarketSheet const & v)
	{
		Encode_ListOfMarketSheetEntryAndContext (e,v.getBidSide());
		Encode_ListOfMarketSheetEntryAndContext (e,v.getAskSide());
	}
	inline void Decode_MarketSheet (DataDecoder & d, MarketSheet & v)
	{
		Decode_ListOfMarketSheetEntryAndContext (d,v.getBidSide());
		Decode_ListOfMarketSheetEntryAndContext (d,v.getAskSide());
	}

	inline void Encode_InstrumentStatusMarketSheet (DataEncoder & e, InstrumentStatusMarketSheet const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_Timestamp (e,v.getServerUTCTimestamp());
		Encode_Timestamp (e,v.getMarketUTCTimestamp());
		Encode_MarketSheet (e,v.getMarketSheet());
		Encode_ListOfQuotationVariable (e,v.getValues());
	}
	inline void Decode_InstrumentStatusMarketSheet (DataDecoder & d, InstrumentStatusMarketSheet & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_Timestamp (d,v.getServerUTCTimestamp());
		Decode_Timestamp (d,v.getMarketUTCTimestamp());
		Decode_MarketSheet (d,v.getMarketSheet());
		Decode_ListOfQuotationVariable (d,v.getValues());
	}

	inline void Encode_ListOfInstrumentStatusMarketSheet (DataEncoder & e, std::vector<InstrumentStatusMarketSheet > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<InstrumentStatusMarketSheet >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_InstrumentStatusMarketSheet (e,*it);	}
	inline void Decode_ListOfInstrumentStatusMarketSheet (DataDecoder & d, std::vector<InstrumentStatusMarketSheet > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_InstrumentStatusMarketSheet (d,l[i]); }

	inline void Encode_MulticastFrameHeaderStruct (DataEncoder & e, MulticastFrameHeaderStruct const & v)
	{
		Encode_uint32 (e,v.getFrameSequenceNumber());
		Encode_uint32 (e,v.getFrameServerDate_seconds());
		Encode_uint16 (e,v.getFrameServerDate_millisec());
		Encode_uint16 (e,v.getFrameServerDate_microsec());
		Encode_uint32 (e,v.getFrameDuration_microsec());
		Encode_uint16 (e,v.getNbMessagesInFrame());
	}
	inline void Decode_MulticastFrameHeaderStruct (DataDecoder & d, MulticastFrameHeaderStruct & v)
	{
		Decode_uint32 (d,v.getFrameSequenceNumber());
		Decode_uint32 (d,v.getFrameServerDate_seconds());
		Decode_uint16 (d,v.getFrameServerDate_millisec());
		Decode_uint16 (d,v.getFrameServerDate_microsec());
		Decode_uint32 (d,v.getFrameDuration_microsec());
		Decode_uint16 (d,v.getNbMessagesInFrame());
	}

	inline void Encode_QuotationReplaySubject (DataEncoder & e, QuotationReplaySubject const & v)
	{
		Encode_uint16 (e,v.getInternalSourceId());
		Encode_Timestamp (e,v.getRangeBeginServerDate());
		Encode_Timestamp (e,v.getRangeEndServerDate());
		Encode_bool (e,v.getSendMulticastFrameHeader());
		Encode_ListOfPolymorphicInstrumentCode (e,v.getFilterInstrumentCodes());
		Encode_ListOfFOSMarketId (e,v.getFilterMICs());
		Encode_bool (e,v.getIgnoreInvalidCodes());
		Encode_float64 (e,v.getAccelerationFactor());
	}
	inline void Decode_QuotationReplaySubject (DataDecoder & d, QuotationReplaySubject & v)
	{
		Decode_uint16 (d,v.getInternalSourceId());
		Decode_Timestamp (d,v.getRangeBeginServerDate());
		Decode_Timestamp (d,v.getRangeEndServerDate());
		Decode_bool (d,v.getSendMulticastFrameHeader());
		Decode_ListOfPolymorphicInstrumentCode (d,v.getFilterInstrumentCodes());
		Decode_ListOfFOSMarketId (d,v.getFilterMICs());
		Decode_bool (d,v.getIgnoreInvalidCodes());
		Decode_float64 (d,v.getAccelerationFactor());
	}

	inline void Encode_QuotationReplayL1Filter (DataEncoder & e, QuotationReplayL1Filter const & v)
	{
		Encode_ListOfQuotationTagNumber (e,v.getOtherValuesToLookFor());
		Encode_QuotationContentMask (e,v.getContentMask());
	}
	inline void Decode_QuotationReplayL1Filter (DataDecoder & d, QuotationReplayL1Filter & v)
	{
		Decode_ListOfQuotationTagNumber (d,v.getOtherValuesToLookFor());
		Decode_QuotationContentMask (d,v.getContentMask());
	}

	inline void Encode_QuotationReplayL2Filter (DataEncoder & e, QuotationReplayL2Filter const & v)
	{
		Encode_int8 (e,v.getOrderBookDepth());
	}
	inline void Decode_QuotationReplayL2Filter (DataDecoder & d, QuotationReplayL2Filter & v)
	{
		Decode_int8 (d,v.getOrderBookDepth());
	}

	inline void Encode_ServerProperty (DataEncoder & e, ServerProperty const & v)
	{
		Encode_String (e,v.getKey());
		Encode_BinaryBuffer (e,v.getValue());
	}
	inline void Decode_ServerProperty (DataDecoder & d, ServerProperty & v)
	{
		Decode_String (d,v.getKey());
		Decode_BinaryBuffer (d,v.getValue());
	}

	inline void Encode_ListOfServerProperty (DataEncoder & e, std::vector<ServerProperty > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<ServerProperty >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_ServerProperty (e,*it);	}
	inline void Decode_ListOfServerProperty (DataDecoder & d, std::vector<ServerProperty > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_ServerProperty (d,l[i]); }

	inline void Encode_FeedInternalSourceID	(DataEncoder & e, FeedInternalSourceID const & v) 	{ Encode_uint16 (e,v); }
	inline void Decode_FeedInternalSourceID	(DataDecoder & d, FeedInternalSourceID & v) 	{ Decode_uint16 (d,v); }

	inline void Encode_ListOfFeedInternalSourceID (DataEncoder & e, std::vector<FeedInternalSourceID > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<FeedInternalSourceID >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_FeedInternalSourceID (e,*it);	}
	inline void Decode_ListOfFeedInternalSourceID (DataDecoder & d, std::vector<FeedInternalSourceID > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_FeedInternalSourceID (d,l[i]); }

	inline void Encode_FeedUsability (DataEncoder & e, FeedUsability const & v)
	{
		Encode_FeedState (e,v.getState());
		Encode_bool (e,v.getLatencyPenalty());
		Encode_bool (e,v.getOutOfDateValues());
		Encode_bool (e,v.getBadDataQuality());
	}
	inline void Decode_FeedUsability (DataDecoder & d, FeedUsability & v)
	{
		Decode_FeedState (d,v.getState());
		Decode_bool (d,v.getLatencyPenalty());
		Decode_bool (d,v.getOutOfDateValues());
		Decode_bool (d,v.getBadDataQuality());
	}

	inline void Encode_FeedDescription (DataEncoder & e, FeedDescription const & v)
	{
		Encode_String (e,v.getFeedName());
		Encode_ListOfFeedInternalSourceID (e,v.getInternalSourceIDs());
	}
	inline void Decode_FeedDescription (DataDecoder & d, FeedDescription & v)
	{
		Decode_String (d,v.getFeedName());
		Decode_ListOfFeedInternalSourceID (d,v.getInternalSourceIDs());
	}

	inline void Encode_ListOfFeedDescription (DataEncoder & e, std::vector<FeedDescription > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<FeedDescription >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_FeedDescription (e,*it);	}
	inline void Decode_ListOfFeedDescription (DataDecoder & d, std::vector<FeedDescription > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_FeedDescription (d,l[i]); }

	inline void Encode_FeedServiceStatus (DataEncoder & e, FeedServiceStatus const & v)
	{
		Encode_String (e,v.getServiceName());
		Encode_FeedUsability (e,v.getUsability());
	}
	inline void Decode_FeedServiceStatus (DataDecoder & d, FeedServiceStatus & v)
	{
		Decode_String (d,v.getServiceName());
		Decode_FeedUsability (d,v.getUsability());
	}

	inline void Encode_ListOfFeedServiceStatus (DataEncoder & e, std::vector<FeedServiceStatus > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<FeedServiceStatus >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_FeedServiceStatus (e,*it);	}
	inline void Decode_ListOfFeedServiceStatus (DataDecoder & d, std::vector<FeedServiceStatus > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_FeedServiceStatus (d,l[i]); }

	inline void Encode_FeedStatus (DataEncoder & e, FeedStatus const & v)
	{
		Encode_FeedDescription (e,v.getFeed());
		Encode_FeedUsability (e,v.getOverallUsability());
		Encode_ListOfFeedServiceStatus (e,v.getServices());
	}
	inline void Decode_FeedStatus (DataDecoder & d, FeedStatus & v)
	{
		Decode_FeedDescription (d,v.getFeed());
		Decode_FeedUsability (d,v.getOverallUsability());
		Decode_ListOfFeedServiceStatus (d,v.getServices());
	}

	inline void Encode_ListOfFeedStatus (DataEncoder & e, std::vector<FeedStatus > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<FeedStatus >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_FeedStatus (e,*it);	}
	inline void Decode_ListOfFeedStatus (DataDecoder & d, std::vector<FeedStatus > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_FeedStatus (d,l[i]); }

	inline void Encode_FeedStatusEvent (DataEncoder & e, FeedStatusEvent const & v)
	{
		Encode_FeedDescription (e,v.getFeed());
		Encode_String (e,v.getEventType());
		Encode_ListOfString (e,v.getEventDetails());
	}
	inline void Decode_FeedStatusEvent (DataDecoder & d, FeedStatusEvent & v)
	{
		Decode_FeedDescription (d,v.getFeed());
		Decode_String (d,v.getEventType());
		Decode_ListOfString (d,v.getEventDetails());
	}

	inline void Encode_FeedHandlerConfiguration (DataEncoder & e, FeedHandlerConfiguration const & v)
	{
		Encode_FeedDescription (e,v.getFeed());
		Encode_FeedHandlerResiliencyRole (e,v.getRole());
		Encode_String (e,v.getOwnServerName());
		Encode_String (e,v.getPeerServerName());
		Encode_float64 (e,v.getDataRateMeasureHz());
	}
	inline void Decode_FeedHandlerConfiguration (DataDecoder & d, FeedHandlerConfiguration & v)
	{
		Decode_FeedDescription (d,v.getFeed());
		Decode_FeedHandlerResiliencyRole (d,v.getRole());
		Decode_String (d,v.getOwnServerName());
		Decode_String (d,v.getPeerServerName());
		Decode_float64 (d,v.getDataRateMeasureHz());
	}

	inline void Encode_FeedHandlerDataRate (DataEncoder & e, FeedHandlerDataRate const & v)
	{
		Encode_String (e,v.getDataName());
		Encode_float64 (e,v.getInstantRateHz());
	}
	inline void Decode_FeedHandlerDataRate (DataDecoder & d, FeedHandlerDataRate & v)
	{
		Decode_String (d,v.getDataName());
		Decode_float64 (d,v.getInstantRateHz());
	}

	inline void Encode_ListOfFeedHandlerDataRate (DataEncoder & e, std::vector<FeedHandlerDataRate > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<FeedHandlerDataRate >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_FeedHandlerDataRate (e,*it);	}
	inline void Decode_ListOfFeedHandlerDataRate (DataDecoder & d, std::vector<FeedHandlerDataRate > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_FeedHandlerDataRate (d,l[i]); }

	inline void Encode_FeedHandlerState (DataEncoder & e, FeedHandlerState const & v)
	{
		Encode_FeedHandlerResiliencyStatus (e,v.getResiliencyStatus());
		Encode_ListOfFeedHandlerDataRate (e,v.getInputRate());
		Encode_ListOfFeedHandlerDataRate (e,v.getOutputRate());
	}
	inline void Decode_FeedHandlerState (DataDecoder & d, FeedHandlerState & v)
	{
		Decode_FeedHandlerResiliencyStatus (d,v.getResiliencyStatus());
		Decode_ListOfFeedHandlerDataRate (d,v.getInputRate());
		Decode_ListOfFeedHandlerDataRate (d,v.getOutputRate());
	}

	inline void Encode_ProxyStatus (DataEncoder & e, ProxyStatus const & v)
	{
		Encode_String (e,v.getName());
		Encode_String (e,v.getRemoteAddress());
		Encode_String (e,v.getDescription());
		Encode_bool (e,v.getIsAvailable());
	}
	inline void Decode_ProxyStatus (DataDecoder & d, ProxyStatus & v)
	{
		Decode_String (d,v.getName());
		Decode_String (d,v.getRemoteAddress());
		Decode_String (d,v.getDescription());
		Decode_bool (d,v.getIsAvailable());
	}

	inline void Encode_ListOfProxyStatus (DataEncoder & e, std::vector<ProxyStatus > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<ProxyStatus >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_ProxyStatus (e,*it);	}
	inline void Decode_ListOfProxyStatus (DataDecoder & d, std::vector<ProxyStatus > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_ProxyStatus (d,l[i]); }

	inline void Encode_TagDeclaration (DataEncoder & e, TagDeclaration const & v)
	{
		Encode_String (e,v.getTagUsage());
		Encode_Enum (e,v.getTagSyntax());
		Encode_TagNumber (e,v.getTagNumericId());
		Encode_String (e,v.getTagName());
		Encode_String (e,v.getTagDescription());
	}
	inline void Decode_TagDeclaration (DataDecoder & d, TagDeclaration & v)
	{
		Decode_String (d,v.getTagUsage());
		Decode_Enum (d,v.getTagSyntax());
		Decode_TagNumber (d,v.getTagNumericId());
		Decode_String (d,v.getTagName());
		Decode_String (d,v.getTagDescription());
	}

	inline void Encode_ListOfTagDeclaration (DataEncoder & e, std::vector<TagDeclaration > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<TagDeclaration >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_TagDeclaration (e,*it);	}
	inline void Decode_ListOfTagDeclaration (DataDecoder & d, std::vector<TagDeclaration > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_TagDeclaration (d,l[i]); }

	inline void Encode_EnumValueDeclaration (DataEncoder & e, EnumValueDeclaration const & v)
	{
		Encode_Any (e,v.getValue());
		Encode_String (e,v.getValueName());
		Encode_String (e,v.getValueDescription());
	}
	inline void Decode_EnumValueDeclaration (DataDecoder & d, EnumValueDeclaration & v)
	{
		Decode_Any (d,v.getValue());
		Decode_String (d,v.getValueName());
		Decode_String (d,v.getValueDescription());
	}

	inline void Encode_ListOfEnumValueDeclaration (DataEncoder & e, std::vector<EnumValueDeclaration > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<EnumValueDeclaration >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_EnumValueDeclaration (e,*it);	}
	inline void Decode_ListOfEnumValueDeclaration (DataDecoder & d, std::vector<EnumValueDeclaration > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_EnumValueDeclaration (d,l[i]); }

	inline void Encode_EnumTypeDeclaration (DataEncoder & e, EnumTypeDeclaration const & v)
	{
		Encode_String (e,v.getEnumName());
		Encode_String (e,v.getEnumDescription());
		Encode_ListOfTagNumber (e,v.getRelatedTags());
		Encode_ListOfEnumValueDeclaration (e,v.getEnumValues());
	}
	inline void Decode_EnumTypeDeclaration (DataDecoder & d, EnumTypeDeclaration & v)
	{
		Decode_String (d,v.getEnumName());
		Decode_String (d,v.getEnumDescription());
		Decode_ListOfTagNumber (d,v.getRelatedTags());
		Decode_ListOfEnumValueDeclaration (d,v.getEnumValues());
	}

	inline void Encode_ListOfEnumTypeDeclaration (DataEncoder & e, std::vector<EnumTypeDeclaration > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<EnumTypeDeclaration >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_EnumTypeDeclaration (e,*it);	}
	inline void Decode_ListOfEnumTypeDeclaration (DataDecoder & d, std::vector<EnumTypeDeclaration > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_EnumTypeDeclaration (d,l[i]); }

	inline void Encode_UserConnectionInfo (DataEncoder & e, UserConnectionInfo const & v)
	{
		Encode_UserId (e,v.getUserId());
		Encode_String (e,v.getUserName());
		Encode_uint32 (e,v.getClientId());
		Encode_String (e,v.getConnectionId());
		Encode_Timestamp (e,v.getTimestamp());
	}
	inline void Decode_UserConnectionInfo (DataDecoder & d, UserConnectionInfo & v)
	{
		Decode_UserId (d,v.getUserId());
		Decode_String (d,v.getUserName());
		Decode_uint32 (d,v.getClientId());
		Decode_String (d,v.getConnectionId());
		Decode_Timestamp (d,v.getTimestamp());
	}

	inline void Encode_ListOfUserConnectionInfo (DataEncoder & e, std::vector<UserConnectionInfo > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<UserConnectionInfo >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_UserConnectionInfo (e,*it);	}
	inline void Decode_ListOfUserConnectionInfo (DataDecoder & d, std::vector<UserConnectionInfo > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_UserConnectionInfo (d,l[i]); }

	inline void Encode_ListOfAdjustmentFactorEventType (DataEncoder & e, std::vector<AdjustmentFactorEventType > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<AdjustmentFactorEventType >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_AdjustmentFactorEventType (e,*it);	}
	inline void Decode_ListOfAdjustmentFactorEventType (DataDecoder & d, std::vector<AdjustmentFactorEventType > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_AdjustmentFactorEventType (d,l[i]); }

	inline void Encode_AdjustmentFactorEvent (DataEncoder & e, AdjustmentFactorEvent const & v)
	{
		Encode_FOSInstrumentCode (e,v.getCode());
		Encode_Timestamp (e,v.getEventDay());
		Encode_AdjustmentFactorEventType (e,v.getEventType());
		Encode_uint16 (e,v.getKeySuffix());
		Encode_float64 (e,v.getFactor());
		Encode_bool (e,v.getCanceled());
		Encode_String (e,v.getMIC());
		Encode_String (e,v.getTicker());
		Encode_String (e,v.getDetails());
	}
	inline void Decode_AdjustmentFactorEvent (DataDecoder & d, AdjustmentFactorEvent & v)
	{
		Decode_FOSInstrumentCode (d,v.getCode());
		Decode_Timestamp (d,v.getEventDay());
		Decode_AdjustmentFactorEventType (d,v.getEventType());
		Decode_uint16 (d,v.getKeySuffix());
		Decode_float64 (d,v.getFactor());
		Decode_bool (d,v.getCanceled());
		Decode_String (d,v.getMIC());
		Decode_String (d,v.getTicker());
		Decode_String (d,v.getDetails());
	}

	inline void Encode_ListOfAdjustmentFactorEvent (DataEncoder & e, std::vector<AdjustmentFactorEvent > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<AdjustmentFactorEvent >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_AdjustmentFactorEvent (e,*it);	}
	inline void Decode_ListOfAdjustmentFactorEvent (DataDecoder & d, std::vector<AdjustmentFactorEvent > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_AdjustmentFactorEvent (d,l[i]); }

	inline void Encode_AdjustmentFactorEventTypeMask	(DataEncoder & e, AdjustmentFactorEventTypeMask const & v) 	{ Encode_uint32 (e,v); }
	inline void Decode_AdjustmentFactorEventTypeMask	(DataDecoder & d, AdjustmentFactorEventTypeMask & v) 	{ Decode_uint32 (d,v); }

	inline void Encode_TradeCancelCorrectionContentMask	(DataEncoder & e, TradeCancelCorrectionContentMask const & v) 	{ Encode_uint8 (e,v); }
	inline void Decode_TradeCancelCorrectionContentMask	(DataDecoder & d, TradeCancelCorrectionContentMask & v) 	{ Decode_uint8 (d,v); }

	inline void Encode_TradeData (DataEncoder & e, TradeData const & v)
	{
		Encode_float64 (e,v.getPrice());
		Encode_float64 (e,v.getQuantity());
		Encode_QuotationTradeImpactIndicatorMask (e,v.getTradeImpactIndicator());
		Encode_Timestamp (e,v.getMarketTimestamp());
		Encode_Any (e,v.getTradeId());
		Encode_ListOfQuotationVariable (e,v.getTradeProperties());
	}
	inline void Decode_TradeData (DataDecoder & d, TradeData & v)
	{
		Decode_float64 (d,v.getPrice());
		Decode_float64 (d,v.getQuantity());
		Decode_QuotationTradeImpactIndicatorMask (d,v.getTradeImpactIndicator());
		Decode_Timestamp (d,v.getMarketTimestamp());
		Decode_Any (d,v.getTradeId());
		Decode_ListOfQuotationVariable (d,v.getTradeProperties());
	}

	inline void Encode_QuotationTradeCancelCorrection (DataEncoder & e, QuotationTradeCancelCorrection const & v)
	{
		Encode_TradeCancelCorrectionContentMask (e,v.getContentMask());
		Encode_TradeData (e,v.getOriginalTrade());
		Encode_FOSTradingSessionId (e,v.getTradingSessionId());
		Encode_TradeData (e,v.getCorrectedTrade());
		Encode_ListOfQuotationVariable (e,v.getCorrectedValues());
	}
	inline void Decode_QuotationTradeCancelCorrection (DataDecoder & d, QuotationTradeCancelCorrection & v)
	{
		Decode_TradeCancelCorrectionContentMask (d,v.getContentMask());
		Decode_TradeData (d,v.getOriginalTrade());
		Decode_FOSTradingSessionId (d,v.getTradingSessionId());
		Decode_TradeData (d,v.getCorrectedTrade());
		Decode_ListOfQuotationVariable (d,v.getCorrectedValues());
	}

	inline void Encode_IntradayHistoryDataExtended (DataEncoder & e, IntradayHistoryDataExtended const & v)
	{
		Encode_FOSInstrumentCode (e,v.getInstrCode());
		Encode_String (e,v.getTradeId());
		Encode_IntradayHistoryPointExtended (e,v.getIntradayPointExtended());
	}
	inline void Decode_IntradayHistoryDataExtended (DataDecoder & d, IntradayHistoryDataExtended & v)
	{
		Decode_FOSInstrumentCode (d,v.getInstrCode());
		Decode_String (d,v.getTradeId());
		Decode_IntradayHistoryPointExtended (d,v.getIntradayPointExtended());
	}

	inline void Encode_ListOfIntradayHistoryDataExtended (DataEncoder & e, std::vector<IntradayHistoryDataExtended > const & l) { e.encode_count_long_list((unsigned int)l.size()); for (std::vector<IntradayHistoryDataExtended >::const_iterator it=l.begin(); it!=l.end(); ++it) Encode_IntradayHistoryDataExtended (e,*it);	}
	inline void Decode_ListOfIntradayHistoryDataExtended (DataDecoder & d, std::vector<IntradayHistoryDataExtended > & l) { unsigned int nb=d.decode_count_long_list(); l.clear(); l.resize (nb); for (unsigned int i=0; i<nb; ++i) Decode_IntradayHistoryDataExtended (d,l[i]); }

	inline void Encode_IntradayHistoryCancel (DataEncoder & e, IntradayHistoryCancel const & v)
	{
		Encode_FOSInstrumentCode (e,v.getInstrCode());
		Encode_String (e,v.getTradeId());
		Encode_Timestamp (e,v.getOriginalMarketTimestamp());
		Encode_bool (e,v.getFromVenue());
		Encode_bool (e,v.getOffBook());
	}
	inline void Decode_IntradayHistoryCancel (DataDecoder & d, IntradayHistoryCancel & v)
	{
		Decode_FOSInstrumentCode (d,v.getInstrCode());
		Decode_String (d,v.getTradeId());
		Decode_Timestamp (d,v.getOriginalMarketTimestamp());
		Decode_bool (d,v.getFromVenue());
		Decode_bool (d,v.getOffBook());
	}

	inline void Encode_IntradayHistoryCorrection (DataEncoder & e, IntradayHistoryCorrection const & v)
	{
		Encode_FOSInstrumentCode (e,v.getInstrCode());
		Encode_String (e,v.getTradeId());
		Encode_Timestamp (e,v.getOriginalMarketTimestamp());
		Encode_bool (e,v.getFromVenue());
		Encode_bool (e,v.getOffBook());
		Encode_FOSTradingSessionId (e,v.getTradingSessionId());
		Encode_TradeData (e,v.getTrade());
	}
	inline void Decode_IntradayHistoryCorrection (DataDecoder & d, IntradayHistoryCorrection & v)
	{
		Decode_FOSInstrumentCode (d,v.getInstrCode());
		Decode_String (d,v.getTradeId());
		Decode_Timestamp (d,v.getOriginalMarketTimestamp());
		Decode_bool (d,v.getFromVenue());
		Decode_bool (d,v.getOffBook());
		Decode_FOSTradingSessionId (d,v.getTradingSessionId());
		Decode_TradeData (d,v.getTrade());
	}

	}	// namespace Types
}	// namespace FeedOS
#endif

