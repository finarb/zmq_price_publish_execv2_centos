
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2013 **/
/**                                **/
/************************************/

// NEWS Items declaration.
// FIX.5.0SP2
FEEDOS_DEF_TAG			(50000,		Headline,				std::string,					String)
FEEDOS_DEF_TAG			(50001,		Body,					std::string,					String)
FEEDOS_DEF_TAG			(50002,	    OrigUTCTime,			Timestamp,						Timestamp)
FEEDOS_DEF_TAG			(50003,	   	Urgency,   				Types::FIXNewsUrgency,			Enum)
FEEDOS_DEF_TAG			(50004,	   	LanguageCode,			std::string,					String)
FEEDOS_DEF_TAG			(50005,	   	URLLink,				std::string,					String)
FEEDOS_DEF_TAG			(50006,	   	Submitter,				std::string,					String)
FEEDOS_DEF_TAG			(50007,	   	Category,				Types::FIXNewsCategory,			Enum)
FEEDOS_DEF_TAG			(50008,	  	MarketId,				std::string,					String)
FEEDOS_DEF_TAG_ALIAS	(1300,		MarketSegmentID,		std::string,					String)

// Other Items
FEEDOS_DEF_TAG			(50101,	   RelatedInstrument,		std::string,					String)
FEEDOS_DEF_TAG			(50102,	   RelatedFOSInstrument,	FOSLowLevelInstrumentCode,		uint32)

// Aliases
FEEDOS_DEF_TAG_ALIAS	(107,		Description,			std::string,					String)

FEEDOS_DEF_TAG_ALIAS	(470,		CountryOfIssue,			std::string,					String)
FEEDOS_DEF_TAG_ALIAS	(9503,		ISIN,					std::string,					String)
FEEDOS_DEF_TAG_ALIAS	(9504,		CUSIP,					std::string,					String)
FEEDOS_DEF_TAG_ALIAS	(9512,		MaturityYear,			unsigned int,					uint16)
FEEDOS_DEF_TAG_ALIAS	(9513,		MaturityMonth,			unsigned int,					uint8)
FEEDOS_DEF_TAG_ALIAS	(9514,		MaturityDay,			unsigned int,					uint8)
FEEDOS_DEF_TAG_ALIAS	(9541,		CINS,					std::string,					String)
FEEDOS_DEF_TAG_ALIAS	(9530,		GICS,					std::string,					String)
FEEDOS_DEF_TAG_ALIAS	(9403,		InternalSourceId,		uint16,							uint16)
FEEDOS_DEF_TAG_ALIAS	(9405,		InternalEntitlementId,	int32,							int32)

// Comon S&P tags
FEEDOS_DEF_TAG			(50199,	   InternalSnPReference,	std::string,					String)

// S&P Equities items
FEEDOS_DEF_TAG			(50250,	   EquityPriorTargetPrice,					std::string,						String)
FEEDOS_DEF_TAG			(50251,	   EquityCurrentTargetPrice,				std::string,						String)
FEEDOS_DEF_TAG			(50252,	   EquityCurrencyTargetPrice,				std::string,						String)
FEEDOS_DEF_TAG			(50253,	   EquityContributor,						std::string,						String)
FEEDOS_DEF_TAG			(50254,	   EquityGicsSector,						std::string,						String)
FEEDOS_DEF_TAG			(50255,	   EquityUpdateDate,						std::string,						String)
FEEDOS_DEF_TAG			(50256,	   EquityPublicPubTime,						std::string,						String)
FEEDOS_DEF_TAG			(50257,	   EquityCountry,							std::string,						String)
FEEDOS_DEF_TAG			(50258,	   ArticleType,								std::string,						String)
FEEDOS_DEF_TAG			(50259,	   EquityActionValue,						std::string,						String)
FEEDOS_DEF_TAG			(50260,	   EquityPriorValue,						std::string,						String)

// Common tags for all S&P News data
FEEDOS_DEF_TAG			(50400,	   SnPNewsKind,								char,								char)

// S&P Rating
FEEDOS_DEF_TAG			(50401,	   SAndPRatingsServicesActionType,			std::string,						String)
FEEDOS_DEF_TAG			(50402,	   SAndPRatingsServicesActionId,			std::string,						String)
FEEDOS_DEF_TAG			(50403,	   SAndPRatingsServicesIdentifierId,		std::string,						String)
FEEDOS_DEF_TAG			(50404,	   SAndPRatingsServicesIdType,				std::string,						String)
FEEDOS_DEF_TAG			(50405,	   SAndPRatingsServicesType,				std::string,						String)
FEEDOS_DEF_TAG			(50406,	   SAndPRatingsServicesOrgDebtType,			std::string,						String)
FEEDOS_DEF_TAG			(50407,	   SAndPRatingsServicesActionName,			std::string,						String)
FEEDOS_DEF_TAG			(50408,	   SAndPRatingsServicesActionDetailName,	std::string,						String)
FEEDOS_DEF_TAG			(50409,	   SAndPRatingsServicesMaturityDate,		std::string,						String)
FEEDOS_DEF_TAG			(50410,	   SAndPRatingsServicesActionToValue,		std::string,						String)
FEEDOS_DEF_TAG			(50411,	   SAndPRatingsServicesActionPriorValue,	std::string,						String)
FEEDOS_DEF_TAG			(50412,	   SAndPRatingsServicesCWToValue,			std::string,						String)
FEEDOS_DEF_TAG			(50413,	   SAndPRatingsServicesCWPriorValue,		std::string,						String)
FEEDOS_DEF_TAG			(50414,	   SAndPRatingsServicesOLToValue,			std::string,						String)
FEEDOS_DEF_TAG			(50415,	   SAndPRatingsServicesOLPriorValue,		std::string,						String)
FEEDOS_DEF_TAG			(50416,	   SAndPRatingsServicesActionDateTime,		std::string,						String)
FEEDOS_DEF_TAG			(50417,	   SAndPRatingsServicesPublicPubTime,		std::string,						String)
FEEDOS_DEF_TAG			(50418,	   SAndPRatingsServicesPublishedTime,		std::string,						String)
FEEDOS_DEF_TAG			(50419,	   SAndPRatingsServicesCurrencyType,		std::string,						String)
FEEDOS_DEF_TAG			(50420,	   SAndPRatingsServicesCountry,				std::string,						String)
FEEDOS_DEF_TAG			(50421,	   MessageType,								std::string,						String)
FEEDOS_DEF_TAG			(50422,	   ArticleSource,							std::string,						String)
FEEDOS_DEF_TAG			(50423,	   ArticleAction,							std::string,						String)

// S&P Equities Rankings
FEEDOS_DEF_TAG			(50450,	   EquityActionType,						std::string,						String)
FEEDOS_DEF_TAG			(50451,	   EquityActionId,							std::string,						String)
FEEDOS_DEF_TAG			(50452,	   EquityIdentifierId,						std::string,						String)
FEEDOS_DEF_TAG			(50453,	   EquityIdType,							std::string,						String)
FEEDOS_DEF_TAG			(50454,	   EquityActionName,						std::string,						String)
FEEDOS_DEF_TAG			(50455,	   EquityActionDetailName,					std::string,						String)
FEEDOS_DEF_TAG			(50456,	   EquityActionDesc,						std::string,						String)
FEEDOS_DEF_TAG			(50457,	   EquityPublishedTime,						std::string,						String)

// Item lists
FEEDOS_DEF_TAG_LIST		(50510,		Keyword,								std::string,					String,		100)
FEEDOS_DEF_TAG_LIST		(50610,		RelatedCompany,							std::string,					String,		100)
