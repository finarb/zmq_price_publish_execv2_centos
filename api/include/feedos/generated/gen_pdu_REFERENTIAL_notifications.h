/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_REFERENTIAL_NOTIFICATIONS_H
#define FEEDOS_generated_PDU_REFERENTIAL_NOTIFICATIONS_H

#ifndef FEEDOS_COMM_PDU_H
#  include "../comm/PDU.h"
#endif

#ifndef FEEDOS_generated_PDU_IDS_H
#  include "gen_pdu_ids.h"
#endif

#ifndef FEEDOS_generated_ENCODING_H
#  include "gen_encoding.h"
#endif

namespace FeedOS
{
	using namespace Types;

	namespace PDU_outbound_REFERENTIAL
	{
	class SubscribeNotif_BranchBegin: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_BranchBegin (MarketBranchId const & a, uint32 b, uint32 c, uint32 d, uint32 e) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_BranchBegin)
		{
			Encode_MarketBranchId (*this, a);
			Encode_uint32 (*this, b);
			Encode_uint32 (*this, c);
			Encode_uint32 (*this, d);
			Encode_uint32 (*this, e);
		}
	};

	class SubscribeNotif_InstrumentsDeleted: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentsDeleted (ListOfFOSInstrumentCode const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_InstrumentsDeleted)
		{
			Encode_ListOfFOSInstrumentCode (*this, a);
		}
	};

	class SubscribeNotif_InstrumentsDeletedExt: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentsDeletedExt (ListOfBranchAndInstrument const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_InstrumentsDeletedExt)
		{
			Encode_ListOfBranchAndInstrument (*this, a);
		}
	};

	class SubscribeNotif_InstrumentsCreated: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentsCreated (ListOfInstrumentCharacteristics const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_InstrumentsCreated)
		{
			Encode_ListOfInstrumentCharacteristics (*this, a);
		}
	};

	class SubscribeNotif_InstrumentsModified: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentsModified (ListOfInstrumentCharacteristics const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_InstrumentsModified)
		{
			Encode_ListOfInstrumentCharacteristics (*this, a);
		}
	};

	class SubscribeNotif_MarkerTimestamp: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MarkerTimestamp (Timestamp const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_MarkerTimestamp)
		{
			Encode_Timestamp (*this, a);
		}
	};

	class SubscribeNotif_RealtimeBegin: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RealtimeBegin () :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_RealtimeBegin)
		{
		}
	};

	class SubscribeNotif_VariablePriceIncrementTables: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_VariablePriceIncrementTables (ListOfVariableIncrementPriceBandTable const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_VariablePriceIncrementTables)
		{
			Encode_ListOfVariableIncrementPriceBandTable (*this, a);
		}
	};

	class SubscribeNotif_TradeConditionsDictionary: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_TradeConditionsDictionary (ListOfTradeConditionsDictionaryEntry const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_TradeConditionsDictionary)
		{
			Encode_ListOfTradeConditionsDictionaryEntry (*this, a);
		}
	};

	class SubscribeNotif_MetaData: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MetaData (ListOfTagDeclaration const & a, ListOfEnumTypeDeclaration const & b, ListOfString const & c) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_MetaData)
		{
			Encode_ListOfTagDeclaration (*this, a);
			Encode_ListOfEnumTypeDeclaration (*this, b);
			Encode_ListOfString (*this, c);
		}
	};

	} // namespace PDU_outbound_REFERENTIAL


	namespace PDU_inbound_REFERENTIAL
	{
	class SubscribeNotif_BranchBegin: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_BranchBegin (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_BranchBegin, p)
		{
			Decode_MarketBranchId (*this, m_Branch);
			Decode_uint32 (*this, m_CurrentQuantity);
			Decode_uint32 (*this, m_DeletedQuantity);
			Decode_uint32 (*this, m_CreatedQuantity);
			Decode_uint32 (*this, m_ModifiedQuantity);
		}
		inline MarketBranchId const & getBranch() const { return m_Branch; }
		inline uint32 const & getCurrentQuantity() const { return m_CurrentQuantity; }
		inline uint32 const & getDeletedQuantity() const { return m_DeletedQuantity; }
		inline uint32 const & getCreatedQuantity() const { return m_CreatedQuantity; }
		inline uint32 const & getModifiedQuantity() const { return m_ModifiedQuantity; }
	private:
		MarketBranchId m_Branch;
		uint32 m_CurrentQuantity;
		uint32 m_DeletedQuantity;
		uint32 m_CreatedQuantity;
		uint32 m_ModifiedQuantity;
	public:
		inline MarketBranchId & _refBranch() { return m_Branch; }
		inline uint32 & _refCurrentQuantity() { return m_CurrentQuantity; }
		inline uint32 & _refDeletedQuantity() { return m_DeletedQuantity; }
		inline uint32 & _refCreatedQuantity() { return m_CreatedQuantity; }
		inline uint32 & _refModifiedQuantity() { return m_ModifiedQuantity; }
	};

	class SubscribeNotif_InstrumentsDeleted: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentsDeleted (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_InstrumentsDeleted, p)
		{
			Decode_ListOfFOSInstrumentCode (*this, m_InternalCodes);
		}
		inline ListOfFOSInstrumentCode const & getInternalCodes() const { return m_InternalCodes; }
	private:
		ListOfFOSInstrumentCode m_InternalCodes;
	public:
		inline ListOfFOSInstrumentCode & _refInternalCodes() { return m_InternalCodes; }
	};

	class SubscribeNotif_InstrumentsDeletedExt: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentsDeletedExt (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_InstrumentsDeletedExt, p)
		{
			Decode_ListOfBranchAndInstrument (*this, m_BranchesAndInstruments);
		}
		inline ListOfBranchAndInstrument const & getBranchesAndInstruments() const { return m_BranchesAndInstruments; }
	private:
		ListOfBranchAndInstrument m_BranchesAndInstruments;
	public:
		inline ListOfBranchAndInstrument & _refBranchesAndInstruments() { return m_BranchesAndInstruments; }
	};

	class SubscribeNotif_InstrumentsCreated: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentsCreated (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_InstrumentsCreated, p)
		{
			Decode_ListOfInstrumentCharacteristics (*this, m_Instruments);
		}
		inline ListOfInstrumentCharacteristics const & getInstruments() const { return m_Instruments; }
	private:
		ListOfInstrumentCharacteristics m_Instruments;
	public:
		inline ListOfInstrumentCharacteristics & _refInstruments() { return m_Instruments; }
	};

	class SubscribeNotif_InstrumentsModified: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_InstrumentsModified (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_InstrumentsModified, p)
		{
			Decode_ListOfInstrumentCharacteristics (*this, m_Instruments);
		}
		inline ListOfInstrumentCharacteristics const & getInstruments() const { return m_Instruments; }
	private:
		ListOfInstrumentCharacteristics m_Instruments;
	public:
		inline ListOfInstrumentCharacteristics & _refInstruments() { return m_Instruments; }
	};

	class SubscribeNotif_MarkerTimestamp: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MarkerTimestamp (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_MarkerTimestamp, p)
		{
			Decode_Timestamp (*this, m_MarkerTimestamp);
		}
		inline Timestamp const & getMarkerTimestamp() const { return m_MarkerTimestamp; }
	private:
		Timestamp m_MarkerTimestamp;
	public:
		inline Timestamp & _refMarkerTimestamp() { return m_MarkerTimestamp; }
	};

	class SubscribeNotif_RealtimeBegin: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_RealtimeBegin (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_RealtimeBegin, p)
		{
		}
	private:
	public:
	};

	class SubscribeNotif_VariablePriceIncrementTables: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_VariablePriceIncrementTables (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_VariablePriceIncrementTables, p)
		{
			Decode_ListOfVariableIncrementPriceBandTable (*this, m_Tables);
		}
		inline ListOfVariableIncrementPriceBandTable const & getTables() const { return m_Tables; }
	private:
		ListOfVariableIncrementPriceBandTable m_Tables;
	public:
		inline ListOfVariableIncrementPriceBandTable & _refTables() { return m_Tables; }
	};

	class SubscribeNotif_TradeConditionsDictionary: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_TradeConditionsDictionary (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_TradeConditionsDictionary, p)
		{
			Decode_ListOfTradeConditionsDictionaryEntry (*this, m_Entries);
		}
		inline ListOfTradeConditionsDictionaryEntry const & getEntries() const { return m_Entries; }
	private:
		ListOfTradeConditionsDictionaryEntry m_Entries;
	public:
		inline ListOfTradeConditionsDictionaryEntry & _refEntries() { return m_Entries; }
	};

	class SubscribeNotif_MetaData: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_MetaData (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_REFERENTIAL_MetaData, p)
		{
			Decode_ListOfTagDeclaration (*this, m_Tags);
			Decode_ListOfEnumTypeDeclaration (*this, m_Enums);
			Decode_ListOfString (*this, m_Providers);
		}
		inline ListOfTagDeclaration const & getTags() const { return m_Tags; }
		inline ListOfEnumTypeDeclaration const & getEnums() const { return m_Enums; }
		inline ListOfString const & getProviders() const { return m_Providers; }
	private:
		ListOfTagDeclaration m_Tags;
		ListOfEnumTypeDeclaration m_Enums;
		ListOfString m_Providers;
	public:
		inline ListOfTagDeclaration & _refTags() { return m_Tags; }
		inline ListOfEnumTypeDeclaration & _refEnums() { return m_Enums; }
		inline ListOfString & _refProviders() { return m_Providers; }
	};

	} // namespace PDU_inbound_REFERENTIAL

}
#endif
