
/************************************/
/** FeedOS sample client code      **/
/**                                **/
/** subscribing to MarketByLevel   **/
/** and merging layers             **/
/**                                **/
/** QuantHouse 2010                **/
/************************************/

#include <algorithm>
#include <string>
#include <sstream>
#include <limits>
#include <ios>
#include <iomanip>
#include <ostream>
#include <fstream>
#include <feedos/zmqpp/tools.h>
#include <feedos/api/api.h>
#include <feedos/framework/InstrumentMBLData.h>
#include <algorithm>

using namespace FeedOS;
using namespace FeedOS::Types;

// MBL Merger class

class MBLLayerMerger : public FeedOS::INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming
{
public:
// Constants
	static OrderBookLayerId const MERGED_LAYER_ID = 2;	// This defines the ID of the merging layer.
														// All layers from 0 to MERGED_LAYER_ID-1 are the realtime layers.
// Types
	enum OutputMode
	{
		Events,
		Cache,
		EventsAndCache
	};

// Construction
	MBLLayerMerger(OutputMode output_mode)
		:	m_LayerData(MERGED_LAYER_ID+1),
			m_OutputMode(output_mode)
	{
	}

// Implementation of MBL streaming interface
	FEEDOS_GEN_DECL_INTERFACE_QUOTATION_SubscribeInstrumentsMBL_streaming

private:
// Internal Tools
	void update_and_print_merged_layer();
	static char const * get_action_string(FeedOS::Types::OrderBookDeltaAction action);
	static void print_price_83f (double price);
	static void print_qty(FOSLowLevelInteger qty);
	static void print_nb_orders(FOSLowLevelInteger nb_orders);
	void print_layer(size_t const layer_id) const;

// Data
	std::vector<LayerMBLData>	m_LayerData;
	OutputMode m_OutputMode;
};

void MBLLayerMerger::update_and_print_merged_layer()
{
	// Prepare layer
	LayerMBLData & merged_layer = m_LayerData[MERGED_LAYER_ID];
	merged_layer.reset();

	// Do the merge
	for( OrderBookLayerId layer_id = 0 ; layer_id < MERGED_LAYER_ID ; ++layer_id )
	{
		LayerMBLData const & current_layer = m_LayerData[layer_id];
		
		// Set the max visible depth to UNLIMITED to avoid truncation of next merged layer
		merged_layer.setMaxVisibleDepth( FeedOS::Types::ORDERBOOK_UNLIMITED_DEPTH );
		merged_layer.merge_by_price(current_layer.getData());
	}

	if( m_OutputMode != Events )
	{
		print_layer(MERGED_LAYER_ID);
	}
}

char const * MBLLayerMerger::get_action_string(FeedOS::Types::OrderBookDeltaAction action)
{
	char const * action_str = "?";
	switch (action)
	{
	case FeedOS::Types::OrderBookDeltaAction_ALLClearFromLevel:
		action_str="ALLClearFromLevel";
		break;

	case FeedOS::Types::OrderBookDeltaAction_BidClearFromLevel:
		action_str="BidClearFromLevel";
		break;

	case FeedOS::Types::OrderBookDeltaAction_AskClearFromLevel:
		action_str="AskClearFromLevel";
		break;
	case FeedOS::Types::OrderBookDeltaAction_BidInsertAtLevel:
		action_str="BidInsertAtLevel";
		break;

	case FeedOS::Types::OrderBookDeltaAction_AskInsertAtLevel:
		action_str="AskInsertAtLevel";
		break;

	case FeedOS::Types::OrderBookDeltaAction_BidRemoveLevel:
		action_str="BidRemoveLevel";
		break;

	case FeedOS::Types::OrderBookDeltaAction_AskRemoveLevel:
		action_str="AskRemoveLevel";
		break;

	case FeedOS::Types::OrderBookDeltaAction_BidChangeQtyAtLevel:
		action_str="BidChangeQtyAtLevel";
		break;

	case FeedOS::Types::OrderBookDeltaAction_AskChangeQtyAtLevel:
		action_str="AskChangeQtyAtLevel";
		break;

	case FeedOS::Types::OrderBookDeltaAction_BidRemoveLevelAndAppend:
		action_str="BidRemoveLevelAndAppend";
		break;

	case FeedOS::Types::OrderBookDeltaAction_AskRemoveLevelAndAppend:
		action_str="AskRemoveLevelAndAppend";
		break;
	}

	return action_str;
}


void MBLLayerMerger::print_price_83f (double price)
{
	char const * special_price_str;
	if			(price == FeedOS::Types::UNQUOTED)						special_price_str = "UNQUOTED"; 
	else if		(price == FeedOS::Types::ORDERBOOK_MAGIC_PRICE_AT_BEST)	special_price_str = "AT_BEST"; 
	else if		(price == FeedOS::Types::ORDERBOOK_MAGIC_PRICE_AT_OPEN)	special_price_str = "AT_OPEN"; 
	else if		(price == FeedOS::Types::ORDERBOOK_MAGIC_PRICE_AT_CLOSE)special_price_str = "AT_CLOSE";
	else if		(price == FeedOS::Types::ORDERBOOK_MAGIC_PRICE_PEG)		special_price_str = "PEG"; 
	else
	{
		std::cout.precision(4);
		std::cout << std::setw(9) << std::fixed << price;
		return;
	}

	std::cout << std::setw(9) << std::setfill(' ') << special_price_str;
}

void MBLLayerMerger::print_qty(FOSLowLevelInteger qty)
{
	std::cout << " x" << std::setw(6) << std::setfill(' ') << qty;
}

void MBLLayerMerger:: print_nb_orders(FOSLowLevelInteger nb_orders)
{
	char const * special_nb_orders_str;
	if			(nb_orders == FeedOS::Types::ORDERBOOK_NB_ORDERS_EMPTY)		special_nb_orders_str = "EMPTY"; 
	else if		(nb_orders == FeedOS::Types::ORDERBOOK_NB_ORDERS_UNKNOWN)	special_nb_orders_str = "?"; 
	else
	{
		std::cout << " @" << std::setw(6) << std::setfill(' ') << nb_orders;
		return;
	}
	
	std::cout << " @" << std::setw(6) << std::setfill(' ') << special_nb_orders_str;
}

void MBLLayerMerger::print_layer(size_t const layer_id) const
{
	LayerMBLData const & layer_mbl_data = m_LayerData[layer_id];
	Types::ListOfMBLOrderBookEntry const & bid_limits = layer_mbl_data.getBidLimits();
	Types::ListOfMBLOrderBookEntry const & ask_limits = layer_mbl_data.getAskLimits();
	size_t const max_level = std::max (bid_limits.size(), ask_limits.size());

	std::cout	<< "\nCache content:"
				<< " LayerID=" << layer_id
				<< " Bid=" << bid_limits.size()
				<< " Ask=" << ask_limits.size()
				<< " MVD=" << layer_mbl_data.getMaxVisibleDepth()
				<< std::endl;
	
	for (size_t i=0; i<max_level; ++i)
	{
		std::cout << std::setfill(' ') << std::setw(3) << i;

		// Show buy side
		std::cout << " BID ";
		if (i < bid_limits.size())
		{
			print_price_83f (bid_limits[i].getPrice());
			print_qty		(bid_limits[i].getQty().getCumulatedUnits());
			print_nb_orders (bid_limits[i].getQty().getNbOrders());
		}
		else
		{
			std::cout << "*************************";
		}

		// Show sell side
		std::cout << " ASK ";
		if (i < ask_limits.size())
		{
			print_price_83f (ask_limits[i].getPrice());
			print_qty		(ask_limits[i].getQty().getCumulatedUnits());
			print_nb_orders (ask_limits[i].getQty().getNbOrders());
		}
		else
		{
			std::cout << "*************************";
		}
		std::cout << std::endl;
	}
	if( max_level > 0 )
	{
		std::cout << std::setw(3) << std::setfill(' ') << max_level << " BID ************************* ASK *************************" << std::endl;
	}

	std::cout.flush();
}

//
//  callback for "subscription accepted by server"
//
void MBLLayerMerger::response_QUOTATION_SubscribeInstrumentsMBL_Started (FeedOS::uint32 /*inTicket*/, FeedOS::Types::ListOfFOSInstrumentCode const & /*codes*/)
{
}

//
//  callback for "subscription refused by server"
//
void MBLLayerMerger::response_QUOTATION_SubscribeInstrumentsMBL_Failed (FeedOS::ReturnCode rc) 
{
	std::cerr << "SubscribeInstrumentsMBL_Failed, rc="<<rc<<std::endl;
}

//
//  callback for "subscription aborted by server" (after it had been accepted)
//
void MBLLayerMerger::aborted_QUOTATION_SubscribeInstrumentsMBL (FeedOS::ReturnCode rc)
{
	std::cerr << "aborted_SubscribeInstrumentsMVL, rc="<<rc<<std::endl;
}

//
//  callback for "all order book initialization"
//
void MBLLayerMerger::notif_MBLFullRefresh( FeedOS::ListOfMBLSnapshot const & inSnapshots)
{
	// Clear realtime layers
	for( OrderBookLayerId layer_id = 0 ; layer_id < MERGED_LAYER_ID ; ++layer_id )
	{
		m_LayerData[layer_id].reset();
	}

	// Empty snapshot, nothing to do
	if (inSnapshots.empty()) return;

	// Process the snapshot (single instrument subscription, only one snapshot)
	std::vector<FeedOS::Types::MBLLayer> const & snapshotLayers = (*inSnapshots.begin()).getLayers();
	size_t layer_count = snapshotLayers.size();

	for( size_t layer = 0 ; (layer < layer_count) ; ++layer )
	{
		MBLLayer const & snapshot_layer = snapshotLayers[layer];
		OrderBookLayerId const layer_id = snapshot_layer.getLayerId();
		if( layer_id < MERGED_LAYER_ID )
		{
			// Process event
			m_LayerData[layer_id].updateWithMBLFullRefresh(snapshot_layer);
			
			// Show event
			if( m_OutputMode != Cache )
			{
				FeedOS::UTCTimestamps const & inUTCTimestamps = snapshot_layer.getTimestamps();

				std::cout	<< "\nInitial snapshot:"
							<< " LayerId "		<< layer_id
							<< " ,MarketUTC="	<< inUTCTimestamps.getMarket()
							<< " ,ServerUTC="	<< inUTCTimestamps.getServer()
							<< std::endl;
			}
		}
	}

	update_and_print_merged_layer();
}

//
//  callback for "all or part of the order book was updated"
//
void MBLLayerMerger::notif_MBLOverlapRefresh	(FeedOS::Types::MBLOverlapRefresh const & inOverlap)
{
	OrderBookLayerId const layer_id = inOverlap.getLayerId();
	
	if( layer_id < MERGED_LAYER_ID )
	{
		// Process event
		m_LayerData[layer_id].updateWithMBLOverlapRefresh(inOverlap);
		
		// Show event
		if( m_OutputMode != Cache )
		{
			FeedOS::UTCTimestamps const & inUTCTimestamps = inOverlap.getTimestamps();

			std::cout	<< "\nMBLOverlapRefresh:"
						<< " LayerId="		<< layer_id
						<< " ,MarketUTC="	<< inUTCTimestamps.getMarket()
						<< " ,ServerUTC="	<< inUTCTimestamps.getServer()
						<< std::endl;
		}
	}

	update_and_print_merged_layer();
}

//
//  callback for "a small part of the order book was updated"
//

void MBLLayerMerger::notif_MBLDeltaRefresh	( FeedOS::Types::MBLDeltaRefresh const & inDelta )
{
	OrderBookLayerId const layer_id = inDelta.getLayerId();

	// Process realtime layers (delta refresh)
	if( layer_id < MERGED_LAYER_ID )
	{
		// Process event
		m_LayerData[layer_id].updateWithMBLDeltaRefresh(inDelta);

		// Show event
		if( m_OutputMode != Cache )
		{
			FeedOS::UTCTimestamps const & inUTCTimestamps		= inDelta.getTimestamps(); 

			std::cout	<< "\nMBLDeltaRefresh:"
						<< " LayerId="				<< layer_id
						<< " ,MarketUTC="			<< inUTCTimestamps.getMarket()
						<< " ,ServerUTC="			<< inUTCTimestamps.getServer()
						<< std::endl
						<< " Action="				<< get_action_string(inDelta.getAction())
						<< " ,Level="				<< inDelta.getLevel()	
						<< " ,Price=";				print_price_83f (inDelta.getPrice());
			std::cout	<< " ,Qty=";				print_qty(inDelta.getQty().getCumulatedUnits());
			std::cout	<< " ,NbOrders=";			print_nb_orders(inDelta.getQty().getNbOrders());
			std::cout	<< " ,ContinuationFlag="	<< std::boolalpha << inDelta.getContinuationFlag()
						<< " ,Nb_values="			<< inDelta.getOtherValues().size()
						<< std::endl;
		}
	}

	update_and_print_merged_layer();
}

void MBLLayerMerger::notif_MBLMaxVisibleDepth	(FeedOS::Types::MBLMaxVisibleDepth const & inDepth)
{
	OrderBookLayerId const layer_id = inDepth.getLayerId();

	if( layer_id < MERGED_LAYER_ID )
	{
		// Process event
		m_LayerData[layer_id].updateWithMBLMaxVisibleDepth(inDepth);

		// Show event
		if( m_OutputMode != Cache )
		{
			std::cout	<< "\nMBLMaxVisibleDepth:"
						<< " LayerId="			<< layer_id
						<< " ,MaxVisibleDepth="	<< inDepth.getMaxVisibleDepth()
						<< std::endl;
		}
	}

	update_and_print_merged_layer();
}

//
//
//    MAIN function (start the subscription and wait for ANY key to be pressed)
//
//
void perform_subscribe_oneMBL_and_mergeLayers(FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	// this will produce "entering" and "leaving" messages in the log file
	FEEDOS_SCOPER (User, "perform_subscribe_oneMBL_and_mergeLayers");	

	// Extract instrument code
	if (argc < 2) {
		std::cerr <<"? CODE"<<std::endl;
		return;
	}
	FeedOS::PolymorphicInstrumentCode instr_code;
	if( !instr_code.read_from_string(argv[1]) )
	{
		std::cerr << "syntax error while reading PolymorphicInstrumentCodes from: "<< argv[1] << std::endl;
		return;
	}

	// Extract output options
	MBLLayerMerger::OutputMode outputMode = MBLLayerMerger::Events;
	if (argc == 3)
	{
		if( strcmp(argv[2],"-cache") == 0 )
		{
			outputMode = MBLLayerMerger::Cache;
		}
		else if( strcmp(argv[2],"-events_and_cache") == 0 )
		{
			outputMode = MBLLayerMerger::EventsAndCache;
		}
	}

	MBLLayerMerger merger(outputMode);
	FeedOS::API_QUOTATION_SubscribeInstrumentsMBL_delegate req (merger);

	// subscription parameters construction
	FeedOS::ListOfPolymorphicInstrumentCode code_list;
	code_list.push_back (instr_code);   // Single instrument
	FeedOS::ListOfOrderBookLayerId requestedLayerIds; // Empty list means we want ALL layers
	bool ignoreInvalidCodes = false;														// "Invalid code" policy on server side
	FeedOS::ReturnCode rc = req.sync_start (connection, code_list, requestedLayerIds, ignoreInvalidCodes);

	if (rc == FeedOS::RC_OK) {
		getchar();
		req.stop ();
	}
}
