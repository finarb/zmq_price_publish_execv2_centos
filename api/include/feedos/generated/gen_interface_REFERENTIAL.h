/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_INTERFACE_REFERENTIAL_H
#define FEEDOS_generated_INTERFACE_REFERENTIAL_H

#ifndef FEEDOS_API_GENERATED_TYPES_H
#  include "../api/generated_types.h"
#endif

namespace FeedOS {

#define FEEDOS_GEN_DECL_INTERFACE_REFERENTIAL_Download_streaming \
		virtual void response_REFERENTIAL_Download_Started (Timestamp const & inLastUpdateTimestamp); \
		virtual void response_REFERENTIAL_Download_Failed (ReturnCode rc); \
		virtual void aborted_REFERENTIAL_Download (ReturnCode rc); \
		virtual void notif_BranchBegin	(FeedOS::Types::MarketBranchId const & inBranch, uint32 inCurrentQuantity, uint32 inDeletedQuantity, uint32 inCreatedQuantity, uint32 inModifiedQuantity); \
		virtual void notif_InstrumentsDeleted	(FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes); \
		virtual void notif_InstrumentsCreated	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments); \
		virtual void notif_InstrumentsModified	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments); \


	class INTERFACE_REFERENTIAL_Download_streaming
	{
	public:
		virtual ~INTERFACE_REFERENTIAL_Download_streaming() {}

		virtual void response_REFERENTIAL_Download_Started (Timestamp const & inLastUpdateTimestamp) = 0;
		virtual void response_REFERENTIAL_Download_Failed (ReturnCode rc) = 0;
		virtual void aborted_REFERENTIAL_Download (ReturnCode rc) = 0;
		virtual void notif_BranchBegin	(FeedOS::Types::MarketBranchId const & inBranch, uint32 inCurrentQuantity, uint32 inDeletedQuantity, uint32 inCreatedQuantity, uint32 inModifiedQuantity) = 0;
		virtual void notif_InstrumentsDeleted	(FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes) = 0;
		virtual void notif_InstrumentsCreated	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments) = 0;
		virtual void notif_InstrumentsModified	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_REFERENTIAL_DownloadAndSubscribe_streaming \
		virtual void response_REFERENTIAL_DownloadAndSubscribe_Started (); \
		virtual void response_REFERENTIAL_DownloadAndSubscribe_Failed (ReturnCode rc); \
		virtual void aborted_REFERENTIAL_DownloadAndSubscribe (ReturnCode rc); \
		virtual void notif_BranchBegin	(FeedOS::Types::MarketBranchId const & inBranch, uint32 inCurrentQuantity, uint32 inDeletedQuantity, uint32 inCreatedQuantity, uint32 inModifiedQuantity); \
		virtual void notif_InstrumentsDeleted	(FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes); \
		virtual void notif_InstrumentsCreated	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments); \
		virtual void notif_InstrumentsModified	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments); \
		virtual void notif_MarkerTimestamp	(Timestamp const & inMarkerTimestamp); \
		virtual void notif_RealtimeBegin	(); \
		virtual void notif_VariablePriceIncrementTables	(FeedOS::Types::ListOfVariableIncrementPriceBandTable const & inTables); \
		virtual void notif_TradeConditionsDictionary	(FeedOS::Types::ListOfTradeConditionsDictionaryEntry const & inEntries); \
		virtual void notif_MetaData	(FeedOS::Types::ListOfTagDeclaration const & inTags,  FeedOS::Types::ListOfEnumTypeDeclaration const & inEnums,  FeedOS::Types::ListOfString const & inProviders); \


	class INTERFACE_REFERENTIAL_DownloadAndSubscribe_streaming
	{
	public:
		virtual ~INTERFACE_REFERENTIAL_DownloadAndSubscribe_streaming() {}

		virtual void response_REFERENTIAL_DownloadAndSubscribe_Started () = 0;
		virtual void response_REFERENTIAL_DownloadAndSubscribe_Failed (ReturnCode rc) = 0;
		virtual void aborted_REFERENTIAL_DownloadAndSubscribe (ReturnCode rc) = 0;
		virtual void notif_BranchBegin	(FeedOS::Types::MarketBranchId const & inBranch, uint32 inCurrentQuantity, uint32 inDeletedQuantity, uint32 inCreatedQuantity, uint32 inModifiedQuantity) = 0;
		virtual void notif_InstrumentsDeleted	(FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes) = 0;
		virtual void notif_InstrumentsCreated	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments) = 0;
		virtual void notif_InstrumentsModified	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments) = 0;
		virtual void notif_MarkerTimestamp	(Timestamp const & inMarkerTimestamp) = 0;
		virtual void notif_RealtimeBegin	() = 0;
		virtual void notif_VariablePriceIncrementTables	(FeedOS::Types::ListOfVariableIncrementPriceBandTable const & inTables) = 0;
		virtual void notif_TradeConditionsDictionary	(FeedOS::Types::ListOfTradeConditionsDictionaryEntry const & inEntries) = 0;
		virtual void notif_MetaData	(FeedOS::Types::ListOfTagDeclaration const & inTags,  FeedOS::Types::ListOfEnumTypeDeclaration const & inEnums,  FeedOS::Types::ListOfString const & inProviders) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming \
		virtual void response_REFERENTIAL_SubscribeAllReferential_Started (); \
		virtual void response_REFERENTIAL_SubscribeAllReferential_Failed (ReturnCode rc); \
		virtual void aborted_REFERENTIAL_SubscribeAllReferential (ReturnCode rc); \
		virtual void notif_InstrumentsDeleted	(FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes); \
		virtual void notif_InstrumentsDeletedExt	(FeedOS::Types::ListOfBranchAndInstrument const & inBranchesAndInstruments); \
		virtual void notif_InstrumentsCreated	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments); \
		virtual void notif_InstrumentsModified	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments); \
		virtual void notif_MarkerTimestamp	(Timestamp const & inMarkerTimestamp); \
		virtual void notif_VariablePriceIncrementTables	(FeedOS::Types::ListOfVariableIncrementPriceBandTable const & inTables); \
		virtual void notif_TradeConditionsDictionary	(FeedOS::Types::ListOfTradeConditionsDictionaryEntry const & inEntries); \
		virtual void notif_MetaData	(FeedOS::Types::ListOfTagDeclaration const & inTags,  FeedOS::Types::ListOfEnumTypeDeclaration const & inEnums,  FeedOS::Types::ListOfString const & inProviders); \


	class INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming
	{
	public:
		virtual ~INTERFACE_REFERENTIAL_SubscribeAllReferential_streaming() {}

		virtual void response_REFERENTIAL_SubscribeAllReferential_Started () = 0;
		virtual void response_REFERENTIAL_SubscribeAllReferential_Failed (ReturnCode rc) = 0;
		virtual void aborted_REFERENTIAL_SubscribeAllReferential (ReturnCode rc) = 0;
		virtual void notif_InstrumentsDeleted	(FeedOS::Types::ListOfFOSInstrumentCode const & inInternalCodes) = 0;
		virtual void notif_InstrumentsDeletedExt	(FeedOS::Types::ListOfBranchAndInstrument const & inBranchesAndInstruments) = 0;
		virtual void notif_InstrumentsCreated	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments) = 0;
		virtual void notif_InstrumentsModified	(FeedOS::Types::ListOfInstrumentCharacteristics const & inInstruments) = 0;
		virtual void notif_MarkerTimestamp	(Timestamp const & inMarkerTimestamp) = 0;
		virtual void notif_VariablePriceIncrementTables	(FeedOS::Types::ListOfVariableIncrementPriceBandTable const & inTables) = 0;
		virtual void notif_TradeConditionsDictionary	(FeedOS::Types::ListOfTradeConditionsDictionaryEntry const & inEntries) = 0;
		virtual void notif_MetaData	(FeedOS::Types::ListOfTagDeclaration const & inTags,  FeedOS::Types::ListOfEnumTypeDeclaration const & inEnums,  FeedOS::Types::ListOfString const & inProviders) = 0;

	};
#define FEEDOS_GEN_DECL_INTERFACE_REFERENTIAL_Synchronise_streaming \
		virtual void response_REFERENTIAL_Synchronise_Started (); \
		virtual void response_REFERENTIAL_Synchronise_Failed (ReturnCode rc); \
		virtual void aborted_REFERENTIAL_Synchronise (ReturnCode rc); \
		virtual void notif_NewInstrument	(Timestamp const & inTimestamp, FOSInstrumentCode inCode,  FeedOS::Types::ListOfReferentialAttribute const & inAttributes); \
		virtual void notif_DeleteAllInstrumentsForMarket	(Timestamp const & inTimestamp, FOSMarketId inMarketId); \
		virtual void notif_DeleteInstruments	(Timestamp const & inTimestamp,  FeedOS::Types::ListOfFOSInstrumentCode const & inCodes); \
		virtual void notif_SetInstrument	(Timestamp const & inTimestamp, FOSInstrumentCode inCode,  FeedOS::Types::ListOfReferentialAttribute const & inAttributes); \
		virtual void notif_CapitalAdjustment	(Timestamp const & inTimestamp, FOSInstrumentCode inCode,  FeedOS::Types::YMD_Date const & inEventDate, float64 inPriceFactor); \
		virtual void notif_CatchUpComplete	(Timestamp const & inLastUpdateTimestamp); \


	class INTERFACE_REFERENTIAL_Synchronise_streaming
	{
	public:
		virtual ~INTERFACE_REFERENTIAL_Synchronise_streaming() {}

		virtual void response_REFERENTIAL_Synchronise_Started () = 0;
		virtual void response_REFERENTIAL_Synchronise_Failed (ReturnCode rc) = 0;
		virtual void aborted_REFERENTIAL_Synchronise (ReturnCode rc) = 0;
		virtual void notif_NewInstrument	(Timestamp const & inTimestamp, FOSInstrumentCode inCode,  FeedOS::Types::ListOfReferentialAttribute const & inAttributes) = 0;
		virtual void notif_DeleteAllInstrumentsForMarket	(Timestamp const & inTimestamp, FOSMarketId inMarketId) = 0;
		virtual void notif_DeleteInstruments	(Timestamp const & inTimestamp,  FeedOS::Types::ListOfFOSInstrumentCode const & inCodes) = 0;
		virtual void notif_SetInstrument	(Timestamp const & inTimestamp, FOSInstrumentCode inCode,  FeedOS::Types::ListOfReferentialAttribute const & inAttributes) = 0;
		virtual void notif_CapitalAdjustment	(Timestamp const & inTimestamp, FOSInstrumentCode inCode,  FeedOS::Types::YMD_Date const & inEventDate, float64 inPriceFactor) = 0;
		virtual void notif_CatchUpComplete	(Timestamp const & inLastUpdateTimestamp) = 0;

	};
}
#endif
