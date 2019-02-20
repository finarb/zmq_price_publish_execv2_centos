
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** subscribing to quotation events         **/
/** on several instruments at once          **/
/**                                         **/
/** QuantHouse 2016                         **/
/*********************************************/

#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>
#include <feedos/framework/InstrumentQuotationData_2.h>
#include <feedos/comm/FOSDictionaryEntryId.h>
#include <iomanip>
#include <limits>
#include <zmq.h>


namespace FeedOS { namespace Types {
	extern char const * getFIXSecurityTradingStatusString(FIXSecurityTradingStatus value);
}}

class SampleL1Consumer: public virtual FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsL1_streaming
{
public:
	typedef std::map<FeedOS::FOSLowLevelInstrumentCode, std::string> TranslationMap;

private:
	typedef std::map<FeedOS::FOSInstrumentCode, FeedOS::InstrumentQuotationData_2> L1Cache;
	L1Cache	m_caches;
	
	TranslationMap m_translat;

	FeedOS::uint32 m_ticket;
	void* pvPubContext;
	void *pvPublisher;
public:
	SampleL1Consumer () // @suppress("Class members should be properly initialized")
		: m_ticket	(0)
	{
		std::cout << std::setprecision(std::numeric_limits<double>::digits10);
	}

	TranslationMap& get_translat_map() { return m_translat; }

	void dump_instr(bool & dump_instr_done, FeedOS::FOSLowLevelInstrumentCode instr_code, std::string const & header) 
	{
		if (!dump_instr_done) 
		{
			std::cout << "instr: " << m_translat[instr_code] << " / " << header << std::endl;
			dump_instr_done = true;
		}
	}

	// partial output
	void dump_cache(FeedOS::InstrumentQuotationData_2 const & cache, std::string const & header)
	{
		std::string json = "{";
		FeedOS::FOSLowLevelInstrumentCode const instr_code = cache.get_internal_code().get_numeric();
		bool dump_instr_done = false;
		std::cout << "\n\tTicker= " << m_translat[instr_code] << " / " << header << std::endl;
		json += "\"Ticker\": \"" + m_translat[instr_code] + " / " + header + "\",";
		{
			FeedOS::OrderBookBestLimitsExt volume;
			cache.get_best_limits(volume);
			FeedOS::OrderBookEntryExt entry = volume.getBestBid();
			double const price = entry.getPrice();
			FeedOS::float64 const qty_units = entry.getQty();
			FeedOS::int32 const qty_nb_orders = entry.getNbOrders();
			if (qty_nb_orders == FeedOS::Types::ORDERBOOK_NB_ORDERS_EMPTY)
			{
				std::cout << "\tBid=?" << std::endl;
				json += "\"Bid\": \"?\",";
			}
			else
			{
				std::cout << "\tBid=" << price << " " << qty_units << std::endl;
				json += "\"Bid\": \"" + std::to_string(price)  + " " + std::to_string(qty_units) + "\",";
			}
			
		}
		{
			FeedOS::OrderBookBestLimitsExt volume;
			cache.get_best_limits(volume);
			FeedOS::OrderBookEntryExt entry = volume.getBestAsk();
			double const price = entry.getPrice();
			FeedOS::float64 const qty_units = entry.getQty();
			FeedOS::int32 const qty_nb_orders = entry.getNbOrders();

			if (qty_nb_orders == FeedOS::Types::ORDERBOOK_NB_ORDERS_EMPTY)
			{
				std::cout << "\tAsk=?" << std::endl;
				json += "\"Ask\": \"?\",";
			}
			else
			{
				std::cout << "\tAsk=" << price << " " << qty_units << std::endl;
				json += "\"Ask\": \"" + std::to_string(price) + " " + std::to_string(qty_units) + "\",";
			}
		}

		{
			FeedOS::float64 volume;
			if (cache.get_LastPrice(volume))
			{
				std::cout << "\tLastPrice=" << volume << std::endl;
				json += "\"LastPrice\": \"" + std::to_string(volume) + "\",";
			}
			else
			{
				std::cout << "\tLastPrice=?" << std::endl;
				json += "\"LastPrice\": \"?\",";
			}
		}
		{
			FeedOS::float64 volume;
			if (cache.get_LastTradeQty(volume))
			{
				std::cout << "\tLastTradeQty=" << volume << std::endl;
				json += "\"LastTradeQty\": \"" + std::to_string(volume) + "\",";
			}
			else
			{
				std::cout << "\tLastTradeQty=?" << std::endl;
				json += "\"LastTradeQty\": \"?\",";
			}
		}
		{
			FeedOS::float64 volume;
			if (cache.get_DailyHighPrice(volume))
			{
				std::cout << "\tDailyHighPrice=" << volume << std::endl;
				json += "\"DailyHighPrice\": \"" + std::to_string(volume) + "\",";
			}
			else
			{
				std::cout << "\tDailyHighPrice=?" << std::endl;
				json += "\"DailyHighPrice\": \"?\",";
			}
		}
		{
			FeedOS::float64 volume;
			if (cache.get_DailyLowPrice(volume))
			{
				std::cout << "\tDailyLowPrice=" << volume << std::endl;
				json += "\"DailyLowPrice\": \"" + std::to_string(volume) + "\",";
			}
			else
			{
				std::cout << "\tDailyLowPrice=?" << std::endl;
				json += "\"DailyLowPrice\": \"?\",";
			}
		}
		{
			FeedOS::float64 volume;
			if (cache.get_DailyTotalVolumeTraded(volume))
			{
				std::cout << "\tDailyTotalVolumeTraded=" << volume << std::endl;
				json += "\"DailyTotalVolumeTraded\": \"" + std::to_string(volume) + "\",";
			}
			else
			{
				std::cout << "\tDailyTotalVolumeTraded=?" << std::endl;
				json += "\"DailyTotalVolumeTraded\": \"?\",";
			}
		}
		{
			FeedOS::float64 volume;
			if (cache.get_LastPrice(volume))
			{
				std::cout << "\tDailyTotalAssetTraded=" << volume << std::endl;
				json += "\"DailyTotalAssetTraded\": \"" + std::to_string(volume) + "\",";
			}
			else
			{
				std::cout << "\tDailyTotalAssetTraded=?" << std::endl;
				json += "\"DailyTotalAssetTraded\": \"?\",";
			}
		}
		{
			FeedOS::Timestamp volume;
			if (cache.get_LastTradeTimestamp(volume))
			{
				std::cout << "\tLastTradeTimestamp=" << volume << std::endl;
				json += "\"LastTradeTimestamp\": \"" + volume.str() + "\",";
			}
			else
			{
				std::cout << "\tLastTradeTimestamp=?" << std::endl;
				json += "\"LastTradeTimestamp\": \"?\",";
			}
		}
		{
			FeedOS::Timestamp volume;
			if (cache.get_InternalDailyOpenTimestamp(volume))
			{
				std::cout << "\tInternalDailyOpenTimestamp=" << volume << std::endl;
				json += "\"InternalDailyOpenTimestamp\": \"" + volume.str() + "\",";
			}
			else
			{
				std::cout << "\tInternalDailyOpenTimestamp=?" << std::endl;
				json += "\"InternalDailyOpenTimestamp\": \"?\",";
			}
		}
		{
			FeedOS::Timestamp volume;
			if (cache.get_InternalDailyCloseTimestamp(volume))
			{
				std::cout << "\tInternalDailyCloseTimestamp=" << volume << std::endl;
				json += "\"InternalDailyCloseTimestamp\": \"" + volume.str() + "\",";
			}
			else
			{
				std::cout << "\tInternalDailyCloseTimestamp=?" << std::endl;
				json += "\"InternalDailyCloseTimestamp\": \"?\",";
			}
		}
		{
			FeedOS::Timestamp volume;
			if (cache.get_InternalDailyHighTimestamp(volume))
			{
				std::cout << "\tInternalDailyHighTimestamp=" << volume << std::endl;
				json += "\"InternalDailyHighTimestamp\": \"" + volume.str() + "\",";
			}
			else
			{
				std::cout << "\tInternalDailyHighTimestamp=?" << std::endl;
				json += "\"InternalDailyHighTimestamp\": \"?\",";
			}
		}
		{
			FeedOS::Timestamp volume;
			if (cache.get_InternalDailyLowTimestamp(volume))
			{
				std::cout << "\tInternalDailyLowTimestamp=" << volume << std::endl;
				json += "\"InternalDailyLowTimestamp\": \"" + volume.str() + "\"}";
			}
			else
			{
				std::cout << "\tInternalDailyLowTimestamp=?" << std::endl;
				json += "\"InternalDailyLowTimestamp\": \"?\"}";
			}
		}
		zmq_publish_message(json);
	}

	void zmq_publish_message(std::string message)
	{
		std::string payload = "{\"data_size\": " + std::to_string(message.length()) + ", \"data\": " + message + "}";
		//std::cout << "zmq_publish_message " << message << std::endl;
		if (pvPublisher != NULL)
		{
			if (zmq_send(pvPublisher, payload.c_str(), payload.length(), 0) != 0)
				printf("%s, l%d : zmq_publish_message Failed, errno=%d \n", __FUNCTION__, __LINE__, errno);
			else
			{
				std::cout << "\t===============================" << std::endl;
				std::cout << "\tzmq_publish_message SUCCESS: " << message << std::endl;
				std::cout << "\t===============================" << std::endl;
			}
		}
		else
		{
			std::cout << "\tzmq_publish_message Failed. pvPublisher is NULL" << std::endl;
		}
	}

	void dump_snapshot(FeedOS::Types::InstrumentStatusL1 const & snapshot)
	{
		std::cout << "instr: " << m_translat[snapshot.getCode().get_numeric()] << std::endl;
		FeedOS::Types::ListOfQuotationVariable const & quotation_tags = snapshot.getValues();
		for (FeedOS::Types::ListOfQuotationVariable::const_iterator it = quotation_tags.begin(); quotation_tags.end() != it; ++it)
		{
			switch (it->getNum())
			{
			case FeedOS::TAG_TradingStatus:
				std::cout << "\tTradingStatus=" << FeedOS::Types::getFIXSecurityTradingStatusString(static_cast<FeedOS::Types::FIXSecurityTradingStatus>((it->getValue()).get_Enum())) << std::endl;
				break;
			case FeedOS::TAG_MARKET_TradingStatus:
				{
					FeedOS::Types::FOSDictionaryEntryId const key = it->getValue().get_uint32();
					std::string short_name;
					std::cout << "\tMARKET_TradingStatus=";
					if (FeedOS::dictionary_entry_id_to_short_name(FeedOS::TAG_MARKET_TradingStatus, key, short_name))
					{
						std::cout << short_name
								<< " (" << FeedOS::dictionary_entry_id_to_long_name(FeedOS::TAG_MARKET_TradingStatus, key) << ")"
								<< std::endl;
					}
					else
					{
						std::cout << key << std::endl;
					}
					break;
				}
			case FeedOS::TAG_MARKET_HaltReason:
				{
					FeedOS::Types::FOSDictionaryEntryId const key = it->getValue().get_uint32();
					std::string short_name;
					std::cout << "\tMARKET_HaltReason=";
					if (FeedOS::dictionary_entry_id_to_short_name(FeedOS::TAG_MARKET_HaltReason, key, short_name))
					{
						std::cout << short_name
								<< " (" << FeedOS::dictionary_entry_id_to_long_name(FeedOS::TAG_MARKET_HaltReason, key) << ")"
								<< std::endl;
					}
					else
					{
						std::cout << key << std::endl;
					}
					break;
				}
			case FeedOS::TAG_DailyTotalVolumeTraded:
				std::cout << "\tDailyTotalVolumeTraded=" << it->getValue().get_float64() << std::endl;
				break;
			case FeedOS::TAG_DailyTotalAssetTraded:
				std::cout << "\tDailyTotalAssetTraded=" << it->getValue().get_float64() << std::endl;
				break;
			default:
				break;
			}
		}
	}

	// subscription management
	void response_QUOTATION_SubscribeInstrumentsL1_Started(
			FeedOS::uint32 inTicket,
			FeedOS::Types::ListOfInstrumentStatusL1 const & inSnapshot)
	{
		std::cout << "SubscribeInstrumentsL1 OK. Hit <ENTER> to stop"
				<< std::endl;

		// init ZMQ publisher
		pvPubContext = NULL;
		pvPublisher = NULL;

		pvPubContext = zmq_ctx_new();
		if (pvPubContext == NULL)
		{
			printf("%s, l%d : Failed to create pub. context, errno=%d \n", __FUNCTION__, __LINE__, errno);
		}
		else
		{
			pvPublisher = zmq_socket(pvPubContext, ZMQ_PUB);
			if (pvPublisher == NULL)
			{
				printf("%s, l%d : Failed to create pub. socket, errno=%d \n", __FUNCTION__, __LINE__, errno);
			}
			else
			{
				int linger = 0;
				zmq_setsockopt(pvPublisher, 17, &linger, sizeof(linger));
				char pcZmqUrl[300];
				snprintf(pcZmqUrl, (sizeof(pcZmqUrl) - 1), "tcp://*:%d", 7000);

				int rc = zmq_bind(pvPublisher, pcZmqUrl);

				printf("%s,l%d : Zmq publisher URL '%s'\n", __FUNCTION__, __LINE__, pcZmqUrl);

				if (rc == 0)
					printf("%s, l%d : PUBLISHER Ready \n%d", __FUNCTION__, __LINE__, errno);
				else
				{
					printf("%s, l%d : PUBLISHER Failed Init \n%d", __FUNCTION__, __LINE__, errno);
					zmq_close(pvPublisher);
					pvPublisher = NULL;
				}
			}
		}
		
		// Store the "ticket" associated to the ongoing subscription.
		// It is required to modify the subscription "profile".
		// (instruments/mask/values)
		m_ticket=inTicket;

		// Initialize caches
		for (FeedOS::Types::ListOfInstrumentStatusL1::const_iterator it = inSnapshot.begin(); it != inSnapshot.end(); ++it)
		{
			FeedOS::Types::InstrumentStatusL1 const & instr_snapshot = *it;
			
			// Dump the current values
			dump_snapshot(instr_snapshot);

			FeedOS::FOSInstrumentCode const inCode = instr_snapshot.getCode();						// numeric instrument code
			FeedOS::Types::ListOfQuotationVariable const & values = instr_snapshot.getValues();
			FeedOS::Types::OrderBookBestLimitsExt const & best_limits = instr_snapshot.getBestLimits();

			// allocate an entry for this instrument
			FeedOS::InstrumentQuotationData_2 & cache = m_caches[inCode];
			cache.reset (inCode);
			
			// load memory image
			cache.set_best_limits (best_limits);
			cache.update_values_nolock (	
												FeedOS::Timestamp(),
												FeedOS::Timestamp(),
												FeedOS::Timestamp(),
												values
											);

			//![snippet_sub_L1_track_init]
			// enable the tracking feature
			cache.set_track_updates_enabled(true);
			//![snippet_sub_L1_track_init]
		}
	}

	void response_QUOTATION_SubscribeInstrumentsL1_Failed(FeedOS::ReturnCode rc)
	{
		std::cerr << "SubscribeInstrumentsL1_Failed, rc=" << rc << std::endl;
	}

	void aborted_QUOTATION_SubscribeInstrumentsL1(FeedOS::ReturnCode rc)
	{
		std::cerr << "aborted_SubscribeInstrumentsL1, rc=" << rc << std::endl;
		
	}

	void notif_TradeEventExt(
			FeedOS::FOSInstrumentCode inCode,
			FeedOS::Timestamp const & inServerUTCTimestamp,
			FeedOS::Timestamp const & inMarketUTCTimestamp,
			FeedOS::Types::QuotationTradeEventExt const & inData)
	{
		// get the instrument's data cache
		FeedOS::InstrumentQuotationData_2& cache = m_caches[inCode];

		//![snippet_sub_L1_track_process]
		// reset the tracking cache
		cache.reset_tracking();

		// update the instrument's data cache
		cache.notif_TradeEventExt(inCode, inServerUTCTimestamp, inMarketUTCTimestamp, inData);
		//![snippet_sub_L1_track_process]
		if (cache.ask_updated() || cache.bid_updated()
			|| cache.tag_updated(FeedOS::TAG_LastPrice)
				|| cache.tag_updated(FeedOS::TAG_LastTradeQty)
					|| cache.tag_updated(FeedOS::TAG_DailyHighPrice)
						|| cache.tag_updated(FeedOS::TAG_DailyLowPrice)
							|| cache.tag_updated(FeedOS::TAG_DailyTotalVolumeTraded)
								|| cache.tag_updated(FeedOS::TAG_DailyTotalAssetTraded)
									|| cache.tag_updated(FeedOS::TAG_LastTradePrice))
			dump_cache(cache, "TE"); // dump tags 
		

	}

	void notif_TradeCancelCorrection(
			FeedOS::FOSInstrumentCode inCode,
			FeedOS::Timestamp const & inServerTimestamp,
			FeedOS::Types::QuotationTradeCancelCorrection const & inData)
	{
		FeedOS::InstrumentQuotationData_2 & cache = m_caches[inCode];
		cache.set_track_updates_enabled(true);
		cache.reset_tracking();
		cache.notif_TradeCancelCorrection(inCode, inServerTimestamp, inData);
		dump_cache(cache, "TCC");
	}
};


void perform_subscribe_L1_tags (FeedOS::API::Connection & connection, int argc, char * argv[])
{
	if (argc < 2) {
		std::cerr << "? CODES..." << std::endl;
		return;
	}

	FeedOS::Types::ListOfPolymorphicInstrumentCode polymorphic_codes;
	// list of instruments we are interested into
	if (!extract_codes (polymorphic_codes, argc, argv))	// read them from command-line arguments
		return;

	// The list of "other values" that you are interested in (none at this time)
	FeedOS::Types::ListOfQuotationTagNumber otherValues;

	// Declare the events that you are interested in (combination of bits).
	// Use FeedOS::Types::QuotationContentBit_LastPrice to receive only the
	// "last price" events (mainly trades).
	// Use FeedOS::Types::QuotationContentBit_LastTradeQty to receive only the
	// trades. Use | QuotationContentBit_BidOrAsk to add the "best bid" /
	// "best ask" events.
	FeedOS::Types::QuotationContentMask contentMask = FeedOS::Types::QuotationContentMask_EVERYTHING;

	FeedOS::Types::ListOfFOSInstrumentCode internal_codes;

	// "relaxed" behaviour ... don't fail if some codes are invalid
	// (however if only 1 code is provided and it is invalid then the server will refuse the request)
	bool ignore_invalid_codes = true;

	FeedOS::ReturnCode rc = API_REFERENTIAL_ResolveCodes(
			connection,
			internal_codes,
			polymorphic_codes,
			ignore_invalid_codes);

	if (rc != FeedOS::RC_OK)
	{
		std::cerr << "error in ResolveCodes request, rc=" << error_string(rc) << std::endl;
		return;
	}

	// Build the request object (responsible for maintaining the data transfer).
	// The object type is "delegate"; hence it requires an external object to
	// handle the incoming data.
	SampleL1Consumer printer;

	SampleL1Consumer::TranslationMap & map = printer.get_translat_map();
	for (size_t i = 0; i < polymorphic_codes.size(); i++)
	{
		if (internal_codes[i].is_valid())
		{
			map[internal_codes[i].get_numeric()] = polymorphic_codes[i].to_str();
		}
	}

	FeedOS::API_QUOTATION_SubscribeInstrumentsL1_delegate req(printer);

	// Start the subscription (synchronous version).
	rc = req.sync_start(connection, polymorphic_codes, otherValues, contentMask, ignore_invalid_codes);

	if (rc != FeedOS::RC_OK)
	{
		std::cerr << "sync_start error, rc=" << FeedOS::error_string(rc)
		<< std::endl;
	}
	while (true){
        int testa=1;
    }
	//else
	//{
	//	getchar(); // Wait for user input.
	//}
	//req.stop (); // Stop the subscription.
}

