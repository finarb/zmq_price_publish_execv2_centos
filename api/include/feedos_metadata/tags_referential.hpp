
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

// FIX tags
FEEDOS_DEF_TAG			(207,	FOSMarketId,				FOSLowLevelMarketId,	uint16)
FEEDOS_DEF_TAG			(100,	ExDestination,				std::string,			String)
FEEDOS_DEF_TAG			(461,	CFICode,					std::string,			String)
FEEDOS_DEF_TAG			(167,	SecurityType,				std::string,			String)
FEEDOS_DEF_TAG			(762,	SecuritySubType,			std::string,			String)
FEEDOS_DEF_TAG			(55 ,	Symbol,						std::string,			String)
FEEDOS_DEF_TAG			(107,	Description,				std::string,			String)
FEEDOS_DEF_TAG			(460,	Product,					unsigned int,			uint32)
FEEDOS_DEF_TAG			(470,	CountryOfIssue,				std::string,			String)
FEEDOS_DEF_TAG			(15,	PriceCurrency,				std::string,			String)
FEEDOS_DEF_TAG			(231,	ContractMultiplier,			float64,				float64)
FEEDOS_DEF_TAG			(202,	StrikePrice,				float64,				float64)
FEEDOS_DEF_TAG			(9468,	UpperStrikePrice,			float64,				float64) // #41904: Upper Strike Price of a Derivative Financial Instrument with Lower and Upper Strike Prices
FEEDOS_DEF_TAG			(947,	StrikeCurrency,				std::string,			String)
FEEDOS_DEF_TAG			(206,	OptAttributeVersion,		unsigned int,			uint8)
FEEDOS_DEF_TAG			(555,	NbLegs,						unsigned int,			uint8)
FEEDOS_DEF_TAG			(223,	CouponRate,					float64,				float64)
FEEDOS_DEF_TAG			(224,	CouponPaymentDate,			unsigned int,			uint32)
FEEDOS_DEF_TAG			(561,	RoundLot,					float64,				float64)
FEEDOS_DEF_TAG			(562,	MinTradeVol,				float64,				float64)
FEEDOS_DEF_TAG			(255,	CreditRating,				std::string,			String)
FEEDOS_DEF_TAG			(106,	Issuer,						std::string,			String)
FEEDOS_DEF_TAG			(225,	IssueDate,					Timestamp,				Timestamp)
FEEDOS_DEF_TAG			(228,	Factor,						float64,				float64)
FEEDOS_DEF_TAG			(291,	FinancialStatus,			std::string,			String)
FEEDOS_DEF_TAG			(423,	PriceType,					unsigned int,			uint8)
FEEDOS_DEF_TAG			(1,		Account,					std::string,			String)
FEEDOS_DEF_TAG			(873,	DatedDate,					Timestamp,				Timestamp)
FEEDOS_DEF_TAG			(1396,	MarketSegmentDesc,			std::string,			String)
FEEDOS_DEF_TAG			(1300,	MarketSegmentID,			std::string,			String)
FEEDOS_DEF_TAG			(200,	StdMaturity,				std::string,			String)
FEEDOS_DEF_TAG			(1142,	MatchAlgorithm,				std::string,			String)
FEEDOS_DEF_TAG			(996,	UnitOfMeasure,				std::string,			String)
FEEDOS_DEF_TAG			(1151,	SecurityGroup,				std::string,			String)
FEEDOS_DEF_TAG			(1093,	LotType,					unsigned int,			uint8)
FEEDOS_DEF_TAG			(1140,	MaxTradeVol,				float64,				float64)
FEEDOS_DEF_TAG			(111,	MaxFloor,					float64,				float64)
FEEDOS_DEF_TAG			(1227,	ProductComplex,				std::string,			String)
FEEDOS_DEF_TAG			(965,	SecurityStatus,				unsigned int,			uint8)

// custom tags (some FIX tags can be computed from them)
FEEDOS_DEF_TAG			(9500,	LocalCodeStr,					std::string,				String)
FEEDOS_DEF_TAG			(9501,	ForeignFOSMarketId,				FOSLowLevelMarketId,		uint16)
FEEDOS_DEF_TAG			(9502,	ForeignMarketId,				std::string,				String)
FEEDOS_DEF_TAG			(9503,	ISIN,							std::string,				String)
FEEDOS_DEF_TAG			(9584,	ContractISIN,					std::string,				String) // #40137: ISIN of a Contract (a group of derivatives instruments on the same underlying)
FEEDOS_DEF_TAG			(9504,	CUSIP,							std::string,				String)
FEEDOS_DEF_TAG			(9541,	CINS,							std::string,				String) // An extension to the CUSIP numbering system, which is used to uniquely identify securities offered outside of the United States and Canada
FEEDOS_DEF_TAG			(9505,	SEDOL,							std::string,				String)
FEEDOS_DEF_TAG			(9586,	ProductID,						std::string,				String) // #41063: Exchange Product Identifier
FEEDOS_DEF_TAG			(9506,	PriceIncrement_static,			float64,					float64)
FEEDOS_DEF_TAG			(9507,	PriceDisplayPrecision,			int,						int16)		// number of decimal digits
FEEDOS_DEF_TAG			(9508,	ReutersInstrumentCode,			std::string,				String)
FEEDOS_DEF_TAG			(9509,	UnderlyingFOSMarketId,			FOSLowLevelMarketId,		uint16)
FEEDOS_DEF_TAG			(9585,	UnderlyingMIC,					std::string,				String) // #41376: Market Identifier Code of the Underlying as specified in ISO 10383
FEEDOS_DEF_TAG			(9510,	UnderlyingLocalCodeStr,			std::string,				String)
FEEDOS_DEF_TAG			(9511,	UnderlyingFOSInstrumentCode,	FOSLowLevelInstrumentCode,	uint32)
FEEDOS_DEF_TAG			(9512,	MaturityYear,					unsigned int,				uint16)
FEEDOS_DEF_TAG			(9513,	MaturityMonth,					unsigned int,				uint8)
FEEDOS_DEF_TAG			(9514,	MaturityDay,					unsigned int,				uint8)
FEEDOS_DEF_TAG			(9582,	IsFrontMonth,					bool,						bool) // #37702: Identifies the Front Month (or Front Contract) on Future instruments
FEEDOS_DEF_TAG			(9515,	ICB_IndustryCode,				unsigned int,				uint32) // #37567: deprecated
FEEDOS_DEF_TAG			(9516,	ICB_SupersectorCode,			unsigned int,				uint32) // #37567: deprecated
FEEDOS_DEF_TAG			(9517,	ICB_SectorCode,					unsigned int,				uint32) // #37567: deprecated
FEEDOS_DEF_TAG			(9518,	ICB_SubsectorCode,				unsigned int,				uint32) // Deprecated
FEEDOS_DEF_TAG			(9519,	BloombergTicker,				std::string,				String)
FEEDOS_DEF_TAG			(9520,	WertpapierKennNummer,			std::string,				String)
FEEDOS_DEF_TAG			(9521,	Telekurs_Valor,					std::string,				String)
FEEDOS_DEF_TAG			(9522,	PriceIncrement_dynamic_TableId,	unsigned int,				uint32)
FEEDOS_DEF_TAG			(9523,	PrimaryReutersInstrumentCode,	std::string,				String)
FEEDOS_DEF_TAG			(9524,	PrimaryBloombergTicker,			std::string,				String)
FEEDOS_DEF_TAG			(9525,	SecurityTradingId,				std::string,				String)
FEEDOS_DEF_TAG			(9576,	AlternativeSecurityTradingId,			std::string,				String)
FEEDOS_DEF_TAG			(9526,	UMTF,							std::string,				String)
FEEDOS_DEF_TAG			(9527,	NbIndexComponents,				unsigned int,				uint16)
FEEDOS_DEF_TAG			(9528,	IndexMemberships,				std::string,				String)
FEEDOS_DEF_TAG			(9529,	InitialListingMarketId,			std::string,				String)
FEEDOS_DEF_TAG			(9530,	GICS,							std::string,				String)
FEEDOS_DEF_TAG			(9531,	ICB,							std::string,				String)
FEEDOS_DEF_TAG			(9580,	SICC_SectorCode,				std::string,				String) // #35767: SICC Sector (aka Industry) classification. SICC stands for Securities Identification Code Committee
FEEDOS_DEF_TAG			(9532,	MBLLayersDesc,					std::string,				String)
FEEDOS_DEF_TAG			(9533,	OperatingMIC,					std::string,				String)
FEEDOS_DEF_TAG			(9534,	SegmentMIC,						std::string,				String)
FEEDOS_DEF_TAG			(9583,	AuctionOnDemand_MIC,				std::string,				String) // #37970: MIC to trade on Auction on Demand
FEEDOS_DEF_TAG			(9581,	IsCentralOrderBook,					bool, 			bool) // #37287: Indicates whether the instrument represents the Main Order Book for the Security on this particular exchange

FEEDOS_DEF_TAG			(9535,	CIQ_ExchangeID,					FOSLowLevelInteger,			int64)  // See 9542 - CapitalIQ_ExchangeID
FEEDOS_DEF_TAG			(9536,	CIQ_ExchangeName,				std::string,				String)
FEEDOS_DEF_TAG			(9537,	CIQ_CompanyID,					FOSLowLevelInteger,			int64)  // See 9543 - CapitalIQ_CompanyID
FEEDOS_DEF_TAG			(9538,	CIQ_CompanyName,				std::string,				String)
FEEDOS_DEF_TAG			(9539,	CIQ_SecurityID,					FOSLowLevelInteger,			int64)  // See 9544 - CapitalIQ_SecurityID
FEEDOS_DEF_TAG			(9540,	CIQ_TradingItemID,				FOSLowLevelInteger,			int64)  // See 9545 - CapitalIQ_TradingItemID

FEEDOS_DEF_TAG			(9542,	CapitalIQ_ExchangeID,			int,						int32)
FEEDOS_DEF_TAG			(9543,	CapitalIQ_CompanyID,			int,						int32)
FEEDOS_DEF_TAG			(9544,	CapitalIQ_SecurityID,			int,						int32)
FEEDOS_DEF_TAG			(9545,	CapitalIQ_TradingItemID,		int,						int32)

FEEDOS_DEF_TAG			(9550,	CouponPaymentDate2,				int,				int32)
FEEDOS_DEF_TAG			(9551,	IssueAttributeInfo,				char,				char)

FEEDOS_DEF_TAG			(9552,	CCP_Eligible,					bool,				bool)
FEEDOS_DEF_TAG			(9546,	IndustryCode,					std::string,		String)

FEEDOS_DEF_TAG			(9547,	EMCF_Eligible,					bool,				bool)
FEEDOS_DEF_TAG			(9548,	XCLEAR_Eligible,				bool,				bool)
FEEDOS_DEF_TAG			(9549,	LCH_Clearnet_Eligible,			bool,				bool)

FEEDOS_DEF_TAG_LIST		(9600,	LegFOSInstrumentCode,			FOSLowLevelInstrumentCode,	uint32,		100)

FEEDOS_DEF_TAG_LIST		(9700,	LegRatioQty,					float64,					float64,	100)
FEEDOS_DEF_TAG_LIST		(9800,	LegFIXSide,						Types::FIXSide,				char,		100)
FEEDOS_DEF_TAG_LIST		(10100,	LegPrice,						float64,					float64,	100) // #42037: List of prices. Each price is the one of the underlying instrument of the leg (ex: the leg is an option on future, it's the price of its future)

FEEDOS_DEF_TAG			(9553,	DynamicVariationRange,						FOSPrice,		float64)
FEEDOS_DEF_TAG			(9554,	StaticVariationRange,						FOSPrice,		float64)

FEEDOS_DEF_TAG			(9555,	ParValue,						float64,				float64)
FEEDOS_DEF_TAG			(9556,	ShortSellEligibleFlag,			bool,					bool)

FEEDOS_DEF_TAG			(9557,	OutstandingSharesBillions,				int32,					int32)
FEEDOS_DEF_TAG			(9558,	OutstandingShares,				int32,					int32)
FEEDOS_DEF_TAG			(9559,	MarginTradingEligibleFlag,		bool,					bool)
FEEDOS_DEF_TAG			(9560,	ShortSellRule,					char,					char)
FEEDOS_DEF_TAG			(9561,	BookType,						char,					char)
FEEDOS_DEF_TAG			(9562,	BuyBoardLot,					uint32,					uint32)
FEEDOS_DEF_TAG			(9563,	SellBoardLot,					uint32,					uint32)
FEEDOS_DEF_TAG			(9564,	PriceEarningRatio,				float64,				float64)
FEEDOS_DEF_TAG			(9587,	QuantityDisplayFactor,			uint8,					uint8) // #42089: Factor by which quantity in quotation data (L1 BBO, Trades, MBL, MBO) need to be divided. 8 meaning quantities need to be divided by 100.000.000 in MBL,MBO and L1 BBO or Trades.

FEEDOS_DEF_TAG			(9565,	FaceValue,						float64,				float64) // The face value represents the principal of a bond
FEEDOS_DEF_TAG			(9566,	RateType,						char,					char) // 'F':fixed 'Z':Zero rate 'V':ariable
FEEDOS_DEF_TAG			(9567,	PaymentPeriod,					uint16,					uint16) // It is a value measured in days. It should be time between two adjacent coupon payment dates
FEEDOS_DEF_TAG			(9568,	PrimeRate,						float64,				float64) // The best rate of interest at which a bank lends to its customers
FEEDOS_DEF_TAG			(9569,	YieldToMaturity,				float64,				float64) // It is the interest rate an investor would earn by investing every coupon payment from the bond at a constant interest rate until the bond’s maturity date

FEEDOS_DEF_TAG			(9570,	RedemptionValue,				float64,				float64) // Redemption value equals the amount paid at the maturity. The redemption value is expressed in percentage of Nominal Value
FEEDOS_DEF_TAG			(9571,	BlockSize,						float64,				float64) // Blocks of securities are traded in what are called "block trades"
FEEDOS_DEF_TAG			(9572,	AutomaticExerciseLimit,			float64,				float64) //The limit from the at-the-money value when an automatic exercise is done
FEEDOS_DEF_TAG			(9406,	IPO_Indicator,					bool,					bool) // Indicates if the NASDAQ security is set up for IPO release. This field is intended to help NASDAQ market participant firms comply with FINRA Rule 5131(b).
FEEDOS_DEF_TAG			(9407,	DelayedFeedMin,					uint16,					uint16)

FEEDOS_DEF_TAG			(9573,	CompositeFIGI,					std::string,			String) // Composite Financial Instrument Global Identifier assigned by Bloomberg
FEEDOS_DEF_TAG			(9574,	BloombergCode,					std::string,			String) // Compound Bloomberg identifier
FEEDOS_DEF_TAG			(9575,	PrimaryBloombergCode,			std::string,			String) // Financial Instrument Global Identifier assigned by Bloomberg

// Corporate Action specific
FEEDOS_DEF_TAG			(9577,	ContractVersion, 				uint8,					uint8) // 35214: Version of a Derivative Contract series. The version of a Derivative Contract series changes as a result of Corporate Action events.
FEEDOS_DEF_TAG			(9578,	OriginalContractMultiplier,		float64,				float64) // 35214: Original contract size (amount of underlying asset represented by each contract) of the Future or Option contract, prior to any Corporate Action.
FEEDOS_DEF_TAG			(9579,	OriginalStrikePrice,			float64,				float64) // 35214: Original Strike Price of the Option, prior to any Corporate Action.

// MiFID specific tags -> 9450 -> 9499
FEEDOS_DEF_TAG			(9450,	MiFID_Flags,					uint16,					uint16) // 37453: MiFID II Instrument Flags - Normalized tag providing the regulatory status of the Security, determined in accordance with MiFID rules
FEEDOS_DEF_TAG			(9451,	AverageDailyTurnover,			float64,				float64) // 37453: Average Daily Turnover (ADT) across all European Trading Venues, calculated in accordance with MiFID rules.
FEEDOS_DEF_TAG			(9452,	AverageValueOfTransactions,		float64,				float64) // 37453:  Average Value of Transactions (AVT) of the Share across all European Trading Venues, calculated in accordance with MiFID rules.
FEEDOS_DEF_TAG			(9453,	StandardMarketSize,				uint32,					uint32) // 37453: Standard Market Size (SMS) is the average order size threshold for System Internalisers (SI), calculated in accordance with MiFID rules.
FEEDOS_DEF_TAG			(9454,	AverageDailyNumberOfTransactions,	float64,			float64) // 37453: Average Daily Number of Transactions (ADNT) for a particular Financial Instrument across all European Trading Venues, calculated in accordance with MiFID rules.
FEEDOS_DEF_TAG			(9455,	ReportedFOSInstrumentCode,		FOSLowLevelInstrumentCode, uint32) // 38145: link to Instrument code reported by APA.
FEEDOS_DEF_TAG			(9456,	MiFID_MostRelevantMarket,		std::string,			String) // 39312: The most relevant market in terms of liquidity, determined in accordance with MiFID II rules.
FEEDOS_DEF_TAG			(9457,	VenueTradingUnderWaiversPercentage,		float64,			float64) // 39312: Percentage of trading under the waivers in a Financial Instrument carried out on the trading venue.
FEEDOS_DEF_TAG			(9458,	TotalTradingUnderWaiversPercentage,		float64,			float64) // 39312: Percentage of trading under the waivers in a Financial Instrument carried out on all trading venues across the EU.
FEEDOS_DEF_TAG			(9467,	InwardTradingUnderWaiversPercentage,		float64,			float64) // 39432: Percentage of trading under the waivers in a Financial Instrument computed by the trading venue and potentially different from ESMA computation
FEEDOS_DEF_TAG			(9459,	DVC_SuspensionEndDate,		std::string,			String) // 39312: String (this is not a Timestamp in order to be able to reset it with a blank string, when needed)
FEEDOS_DEF_TAG			(9460,	DVC_Status,		uint8,			uint8) // 39312: Normalized tag indicating the status of the Financial Instrument regarding Double Volume Caps.
FEEDOS_DEF_TAG			(9461,	PreTradeLIS,		float64,			float64) // 39312: Pre-Trade LiS (Large in Scale) threshold.
FEEDOS_DEF_TAG			(9462,	PostTradeLIS,		float64,			float64) // 39312: Post-Trade LiS (Large in Scale) threshold.
FEEDOS_DEF_TAG			(9463,	PreTradeSSTI,		float64,			float64) // 39312: Pre-Trade SSTI (Size Specific To the Instrument) threshold.
FEEDOS_DEF_TAG			(9464,	PostTradeSSTI,		float64,			float64) // 39312: Post-Trade SSTI (Size Specific To the Instrument) threshold.
FEEDOS_DEF_TAG			(9465,	MaxVolumeOTR,		float64,			float64) // 39312: Maximum volume-based OTR (Order to Trade Ratio), calculated by the trading venue.
FEEDOS_DEF_TAG			(9466,	MaxNumberOTR,		float64,			float64) // 39312: Maximum number-based OTR (Order to Trade Ratio), calculated by the trading venue.
FEEDOS_DEF_TAG			(9469,	ESMA_DVC_Status,		uint8,			uint8) // #42013: Normalized tag indicating the status of the Financial Instrument regarding Double Volume Caps, as published by ESMA.
FEEDOS_DEF_TAG			(9470,	ESMA_DVC_SuspensionEndDate,		std::string,	String) // #42013: Expected suspension end date as published by ESMA. (this is not a Timestamp in order to be able to reset it with a blank string, when needed)


// internal stuff: generic -> 9400-9449
FEEDOS_DEF_TAG			(9400,	InternalCreationDate,			Timestamp,				Timestamp)
FEEDOS_DEF_TAG			(9401,	InternalModificationDate,		Timestamp,				Timestamp)
FEEDOS_DEF_TAG			(9402,	InternalHideFromLookup,			bool,					bool)
FEEDOS_DEF_TAG			(9403,	InternalSourceId,				uint16,					uint16)
FEEDOS_DEF_TAG			(9404,	InternalAggregationId,			uint16,					uint16)
FEEDOS_DEF_TAG			(9405,	InternalEntitlementId,			int32,					int32)

FEEDOS_DEF_TAG			(9408,	DeliveryStartDate,				Timestamp,				Timestamp) // used for commodities to define the start of delivery date. It represents the early redemption date.
FEEDOS_DEF_TAG			(9409,	DeliveryEndDate,				Timestamp,				Timestamp) // used for commodities to define the end of delivery date.
FEEDOS_DEF_TAG			(9421,	LastTradingDate,				Timestamp,				Timestamp) // used to populate the last trading date of an instrument (different from the maturity date)
FEEDOS_DEF_TAG			(9422,	UnderlyingSymbol,				std::string,			String) // The Underlying Symbol as a standalone tag would allow access to the contract's Underlying (or Root) Symbol without the need to parse the ticker symbol using a complex and exchange-specific logic. (Mentioned in Dess scope of Work for futures)
FEEDOS_DEF_TAG			(9423,	UnderlyingISIN,					std::string,			String) // The Underlying ISIN as a standalone tag would allow access to the contract's Underlying (or Root) ISIN. (Mentioned in Dess scope of Work for futures)
FEEDOS_DEF_TAG			(9424,	FIGI,							std::string,			String) // Financial Instrument Global Identifier. A FIGI is a unique, persistent twelve character string that serves to identify financial instruments across asset classes at the venue level. It is associated with one Composite ID. For further information, see Bloomberg Open Symbology - http://bsym.bloomberg.com/sym
FEEDOS_DEF_TAG			(9442,	FISN,							std::string,			String) //38145:  ISO 18774:2015 standard defining an international system for building short names for any kind of financial instruments.
FEEDOS_DEF_TAG			(9443,	PartitionID,					uint32,					uint32) // 38998: Technical unique identifier of a partition across all partitions of an exchange. This is useful for passing orders.
FEEDOS_DEF_TAG			(9425,	SettlementPeriod,				uint8,					uint8) // Period of time between the transaction date and the settlement date. The settlement period denotes how many business days after the transaction date the settlement or the transfer of money and security ownership takes place. For instance, '2' (T+2) means transaction date plus two business days. The length of the settlement period may differ depending on the market and / or the security type.
FEEDOS_DEF_TAG			(9426,	ExchangeSymbol,					std::string,			String) // Exchange-provided ticker Symbol.
FEEDOS_DEF_TAG			(9427,	PriceDisplayFormat,				uint8,					uint8) // Specifies the fractional format for a given instrument. Example: 16 / 32 / 128.
FEEDOS_DEF_TAG			(9428,	ContractMultiplierUnit,			std::string,			String) // Unit of measure of the underlying asset upon which the contract is based. The unit of measure for the contract size: Currency, Index Points, Tons,Grams, Pounds, Gallons, Bushel, Megawatts,... This tag is required to interpret the value populated in tag ContractMultiplier. The initial list of possible values will be defined upon the completion of the feed by feed analysis.
FEEDOS_DEF_TAG			(9429,	ExpiryMonthCode,				char,					char) // The delivery / expiry month code of the Futures / Option contract.
FEEDOS_DEF_TAG			(9430,	FirstTradingDate,				Timestamp,				Timestamp) // The first day under an exchange's rules on which a particular Futures or Options contract may start trading.
FEEDOS_DEF_TAG			(9431,	SettlementDate,					Timestamp,				Timestamp) // The date on which the final settlement price for the Futures or Option contract will be determined, according to the exchange’s regulation rules. Settlement date for delivery or payment. The Settlement Date may be different from the expiration date of the Futures or Option contract itself.
FEEDOS_DEF_TAG			(9432,	SettlementCurrency,				std::string,			String) // ISO Currency Code of settlement denomination. The currency used for the settlement price, if different from the trade price currency (disseminated via the tag “PriceCurrency”). This tag is required to interpret the values populated in tags DailySettlementPrice and PreviousDailySettlementPrice.
FEEDOS_DEF_TAG			(9433,	InternalFeedQualifier,			uint32,					uint32)

FEEDOS_DEF_TAG			(11712,	HasClosingAuctionSession,		bool,					bool) // Indicates whether Closing Auction Session (CAS) is applicable to the security
FEEDOS_DEF_TAG			(11713,	HasVolatilityControlMechanism,	bool,					bool) // Indicates whether Volatility Control Mechanism (VCM) is applicable to the security

FEEDOS_DEF_TAG			(9434,	ShortSellUptickRule,			bool,					bool) // #37127: The uptick rule is a trading restriction that states that short selling a stock is only allowed on an uptick
FEEDOS_DEF_TAG			(9435,	Parity,							float64,				float64) // #37127: Number of Rights / Warrants needed to obtain exposure to one unit of the underlying asset
FEEDOS_DEF_TAG			(9436,	DeactivationBarrierPrice,		float64,				float64) // #37127: Price level at which an Out Barrier Option (aka Knock-Out Option) becomes inactive
FEEDOS_DEF_TAG			(9437,	ActivationBarrierPrice,			float64,				float64) // #37127: Price level at which an In Barrier Option (aka Knock-In Option) becomes active

// Order Entry related tags
FEEDOS_DEF_TAG			(9438,	OrderEntryPriceDecimals,		uint8,					uint8) // #37494: Number of decimals related to prices while formatting a price for order entry
FEEDOS_DEF_TAG			(9439,	OrderEntryQuantityDecimals,		uint8,					uint8) // #37494: Number of decimals related to quantities while formatting a quantity for order entry
FEEDOS_DEF_TAG			(9440,	OrderEntryAmountDecimals,		uint8,					uint8) // #37494: Number of decimals related to amounts while formatting an amount for order entry
FEEDOS_DEF_TAG			(9441,	OrderEntryRatioDecimals,		uint8,					uint8) // #37494: Number of decimals related to ratio/multiplier while formatting a ratio for order entry


// internal stuff: market-specific
FEEDOS_DEF_TAG_LIST		(9410,	InternalMagic,					std::string,			String,	10)


FEEDOS_DEF_TAG_LIST		(20000,		IndexComponentFOSInstrumentCode,	FOSLowLevelInstrumentCode,	uint32,		5000)
// range 25000-29999 is RESERVED for future use
FEEDOS_DEF_TAG_LIST		(40000,		IndexComponentWeight,				float64,					float64,	5000)
// range 45000-49999 is RESERVED for future use



////////////////////////////
// USER-specific fields (60000..60999)
////////////////////////////
FEEDOS_DEF_TAG_LIST		(60000,	REF_USER,						std::string,			String,	1000)



////////////////////////////
// MARKET-specific fields
////////////////////////////

// LSE
FEEDOS_DEF_TAG			(11000,	MARKET_LSE_NormalMarketSize,	float64,			float64)
FEEDOS_DEF_TAG			(11001,	MARKET_LSE_SectorCode,			std::string,		String)
FEEDOS_DEF_TAG			(11002,	MARKET_LSE_SegmentCode,			std::string,		String)

// Euronext UTP
FEEDOS_DEF_TAG			(11050,	MARKET_EURONEXT_InstrumentGroupCode,						std::string,	String)
FEEDOS_DEF_TAG			(11051,	MARKET_EURONEXT_TypeOfUnitOfExpressionForInstrumentPrice,	std::string,	String)
FEEDOS_DEF_TAG			(11052,	MARKET_EURONEXT_NominalMarketValueOfTheSecurity,			float64,		float64)
FEEDOS_DEF_TAG			(11053,	MARKET_EURONEXT_QuantityNotation,							std::string,	String)
FEEDOS_DEF_TAG			(11054,	MARKET_EURONEXT_IndicatorOfUnderlyingSecurityOnLending,		std::string,	String)
FEEDOS_DEF_TAG			(11055, MARKET_EURONEXT_EligibleToPEA,								bool,			bool)
FEEDOS_DEF_TAG			(11056,	MARKET_EURONEXT_TypeOfMarketAdmission,						char,			char)
FEEDOS_DEF_TAG			(11057,	MARKET_EURONEXT_PartitionID,								int,			int32) // Identifies uniquely an Optiq partition across all the Exchange partitions
FEEDOS_DEF_TAG			(11058,	MARKET_EURONEXT_AvailableMarketMechanisms,						std::string,			String) // #38749: Euronext Market Mechanism(s) available for that instrument.

// Xetra
FEEDOS_DEF_TAG			(11100,	MARKET_XETRA_SegmentCode,				std::string,		String)
FEEDOS_DEF_TAG			(11101,	MARKET_XETRA_ISIX,						unsigned int,		uint32)
FEEDOS_DEF_TAG			(11102,	MARKET_XETRA_OptimalGatewayLocation,	std::string,		String)
FEEDOS_DEF_TAG			(11103,	MARKET_XETRA_CCP_Eligible,				bool,				bool)
FEEDOS_DEF_TAG			(11104,	MARKET_XETRA_VolumeDiscoveryMinimumExecutedQuantity,	float64,	float64) // Volume Discovery Minimum Executed Quantity: the minimum number of shares that has to be executed with any match at the midpoint
FEEDOS_DEF_TAG			(11105,	MARKET_XETRA_OrderTypes,				unsigned int,		uint32) // Indicates for a given instrument the collection of possible order types eligibility (for example: IceBerg, peg order, etc)

// Chi-X
FEEDOS_DEF_TAG			(11150,	MARKET_CHIX_LegacyInstrumentCode,	std::string,		String)

// OMX
FEEDOS_DEF_TAG			(11200, MARKET_OMX_SubSegmentName,		std::string,		String)
FEEDOS_DEF_TAG			(11201, MARKET_OMX_SegmentName,			std::string,		String)

// BPIPE
FEEDOS_DEF_TAG			(11250,	BPIPE_BSID,						std::string,		String)
FEEDOS_DEF_TAG			(11251,	BPIPE_EntitlementId,			std::string,		String)
FEEDOS_DEF_TAG			(11252,	BPIPE_SessionType,				char,				char)

// TURQUOISE
FEEDOS_DEF_TAG			(11300,	MARKET_TURQUOISE_Ticker,		std::string,		String)

// SWX
FEEDOS_DEF_TAG			(11350,	MARKET_SWX_IssuerCountry,		std::string,		String)
FEEDOS_DEF_TAG			(11351,	MARKET_SWX_InstrumentPartitionCode,		unsigned int,		uint8)
FEEDOS_DEF_TAG			(11353,	MARKET_SWX_TradingSessionID,	std::string,		String)
FEEDOS_DEF_TAG			(11354,	MARKET_SWX_ListingStateCode,	std::string,		String)
FEEDOS_DEF_TAG			(11355,	MARKET_SWX_ListingStateDesc,	std::string,		String)

// MICEX
FEEDOS_DEF_TAG			(11400, MARKET_MICEX_Remarks,			std::string,		String)
FEEDOS_DEF_TAG			(11401, MARKET_MICEX_FaceValue,			float64,			float64)
FEEDOS_DEF_TAG			(11402, MARKET_MICEX_FaceValueCurrency,	std::string,		String)
FEEDOS_DEF_TAG			(11403, MARKET_MICEX_QuoteBasis,		std::string,		String)

// CME
FEEDOS_DEF_TAG			(11500, MARKET_CME_DisplayPricePrimaryDenominator,		unsigned int,	uint16)
FEEDOS_DEF_TAG			(11501, MARKET_CME_DisplayPriceSecondaryDenominator,	unsigned int,	uint16)
FEEDOS_DEF_TAG			(11502, MARKET_CME_DisplayPriceNbOfDecimal,				unsigned int,	uint16)
FEEDOS_DEF_TAG			(11503, MARKET_CME_IntercommoditiesMIC,					std::string,	String) // #41747: Inter-market Identifier Code for Futures spreads in which the outright legs are listed on different exchanges (NYUM,MGKB,MGCB,CBCM)

// COMSTOCK
FEEDOS_DEF_TAG			(11550,	COMSTOCK_IdCode,				int,		int32)
FEEDOS_DEF_TAG			(11551,	COMSTOCK_MarketIdCode,			int,		int32)

// ICE
FEEDOS_DEF_TAG			(11600, MARKET_ICE_ContractSymbol,		std::string,		String)
FEEDOS_DEF_TAG			(11601, MARKET_ICE_OffExchangeIncrementQty,		float64,	float64) // new field related to Liffe to ICE migration
FEEDOS_DEF_TAG			(11602, MARKET_ICE_OffExchangeIncrementPrice,	float64,	float64) // new field related to Liffe to ICE migration
FEEDOS_DEF_TAG			(11603, MARKET_ICE_SerialUnderlyingLocalCodeStr,	std::string, String) // new field related to Liffe to ICE migration used for serial options
FEEDOS_DEF_TAG			(11604, MARKET_ICE_IsBlockOnly,					bool, 		bool) // Indicates if Market is only tradable via ICE Block Trade. This also means the screen trading is not allowed for the market.
FEEDOS_DEF_TAG			(11605, MARKET_ICE_FlexAllowed,					bool, 		bool) // Indicates if flexible expiries can be created for the market.

// RTS
FEEDOS_DEF_TAG			(11650,	MARKET_RTS_Signs,				unsigned int,		uint32)

// EUREX ULTRA PLUS
FEEDOS_DEF_TAG			(11670,	MARKET_EUREX_ULTRA_PLUS_ProductComplexType,				unsigned int,		uint8)
FEEDOS_DEF_TAG			(11671,	MARKET_EUREX_ULTRA_PLUS_DisseminatedByNTA,				bool,				bool)

// LIFFE XDP
FEEDOS_DEF_TAG			(11700, MARKET_LIFFE_XDP_StrikePriceDenominator,		unsigned int,	uint32) // #37944: deprecated
FEEDOS_DEF_TAG			(11701, MARKET_LIFFE_XDP_StrikePriceDecimalLocator,		unsigned int,	uint16) // #37944: deprecated
FEEDOS_DEF_TAG			(11702, MARKET_LIFFE_XDP_InstrumentDenominator,			unsigned int,	uint32) // #37944: deprecated

// HK
FEEDOS_DEF_TAG			(11710,	MARKET_HK_ExchangeRate,							float64,		float64)
FEEDOS_DEF_TAG			(11711,	MARKET_HK_HasStampDutyFlag,						bool,			bool) // default value 'false' (tag not created). Specific Tag to provide if a security is subject to a stamp duty or not

// JSDA
FEEDOS_DEF_TAG			(11720,	MARKET_JSDA_IssueNameKana,						std::string,	String)

// MFDS
FEEDOS_DEF_TAG			(11730,	MARKET_MFDS_FundType,							char,			char)
FEEDOS_DEF_TAG			(11731,	MARKET_MFDS_FundCode,							char,			char)

// TOCOM
FEEDOS_DEF_TAG			(11740,	MARKET_TOCOM_MinVisibleVolume,					uint32,			uint32) // Minimum visible volume that must be specified in hidden orders
FEEDOS_DEF_TAG			(11741,	MARKET_TOCOM_AdditionalHiddenVolumeAllowed,		bool,			bool) // true: additional, false: normal

// OMX NORDIC
FEEDOS_DEF_TAG			(11750,	MARKET_OMX_NORDIC_NoteCodes,					int,			int32) // This field is a decimal encoded bit field where multiple Note Codes can be set concurrently by being binary OR:ed together. A value of zero means no Note Code set.

// TSE
FEEDOS_DEF_TAG			(11760, MARKET_TSE_IndexMemberships,					unsigned int,	uint32) // #41906: indicates if the instrument is a constituent issue of arbitrary indexes. The field will be a bit mask where each bit will reprensent an index. if the bit is set it means the issue belongs to the related index

// SET Thailand
FEEDOS_DEF_TAG			(11770, MARKET_SET_NoticeFlag,					uint8,	uint8) // #42312: warn investors to invest cautiously in particular securities
FEEDOS_DEF_TAG			(11771, MARKET_SET_AllowNVDR,					std::string,	String) // #42312: indicates if the security can be trade as NVDR
FEEDOS_DEF_TAG			(11772, MARKET_SET_AllowShortSellOnNVDR,		bool,	bool) // #42312: indicates if the NVDR security can be short sell

