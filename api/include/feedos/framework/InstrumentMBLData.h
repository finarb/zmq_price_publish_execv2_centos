
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2010 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_MBL_DATA_H
#define FEEDOS_FRAMEWORK_INSTRUMENT_MBL_DATA_H

#ifndef FEEDOS_FRAMEWORK_INSTRUMENT_TAG_DATA_H
#	include "InstrumentTagData.h"
#endif

namespace FeedOS {

	/**
	 * @brief Constants regarding layer's merge operation
	 */
	struct MBLMergeLayerConstants
	{
		static bool const s_UseLatestServerTimestamp	=	true; // By default ServerUTC timestamps are merged on Layers
		static bool const s_UseLatestMarketTimestamp	=	true; // By default MarketUTC timestamps are merged on Layers
		static bool const s_MergeVariables				=	false; // By default OtherValues are not merged on Layers
		static bool const s_PreserveMergedLayers		=	false; // By default merged layers are removed
	};

	class LayerMBLData
	{
		Types::MBLLayer	m_data;
		bool			m_IsBidFull;
		bool			m_IsAskFull;
		bool			m_max_visible_depth_IS_KNOWN;
		bool			m_ContinuationFlagSet;
	public:
		LayerMBLData ()
			: m_IsBidFull (false), m_IsAskFull (false), m_max_visible_depth_IS_KNOWN (false), m_ContinuationFlagSet (false)
		{
		}

		LayerMBLData (Types::OrderBookLayerId layer_id)
			: m_IsBidFull (false), m_IsAskFull (false), m_max_visible_depth_IS_KNOWN (false), m_ContinuationFlagSet (false)
		{
			m_data.setLayerId (layer_id);
		}

		LayerMBLData (	Types::OrderBookLayerId layer_id,
						int	maxVisibleDepth)
			: m_IsBidFull (false), m_IsAskFull (false), m_max_visible_depth_IS_KNOWN (false), m_ContinuationFlagSet (false)
		{
			m_data.setLayerId (layer_id);
			m_data.setMaxVisibleDepth (maxVisibleDepth);
		}

		LayerMBLData (LayerMBLData const & v)
		{
			operator=(v);
		}

		virtual ~LayerMBLData () {}

		LayerMBLData const & operator= (LayerMBLData const & v)
		{
			m_data = v.m_data;
			m_IsBidFull = v.m_IsBidFull;
			m_IsAskFull = v.m_IsAskFull;
			m_max_visible_depth_IS_KNOWN = v.m_max_visible_depth_IS_KNOWN;
			m_ContinuationFlagSet = v.m_ContinuationFlagSet;
			return *this;
		}

		LayerMBLData const & operator= (Types::MBLLayer const & v)
		{
			updateWithMBLFullRefresh (v);
			return *this;
		}

		bool operator== (Types::MBLLayer const & v) const
		{
			return m_data == v;
		}

		void reset ()
		{
			m_data.reset();
			m_IsBidFull = false;
			m_IsAskFull = false;
			m_max_visible_depth_IS_KNOWN = false;
			m_ContinuationFlagSet = false;
		}

		void clearLimits ()
		{
			m_data.getBidLimits().clear();
			m_data.getAskLimits().clear();
		}

		// beware: MaxVisibleDepth is used to crop the result ;
		// call setMaxVisibleDepth(-1) first in order to set an unlimited depth
		void merge_by_price (	Types::MBLLayer const & l,
								bool use_latest_server_timestamp=MBLMergeLayerConstants::s_UseLatestServerTimestamp,
								bool use_latest_market_timestamp=MBLMergeLayerConstants::s_UseLatestMarketTimestamp,
								bool merge_other_values=MBLMergeLayerConstants::s_MergeVariables
							);

		// Real-time notification: full refresh
		void updateWithMBLFullRefresh		(	Types::MBLLayer const & in_full_data	)
		{
			m_data = in_full_data;
			m_IsBidFull = true;
			m_IsAskFull = true;
			m_max_visible_depth_IS_KNOWN = true;
			m_ContinuationFlagSet = false;
		}

		// Real-time notification: delta refresh
		void updateWithMBLDeltaRefresh	(	Types::MBLDeltaRefresh const & in_delta		)
		{
			Types::MBLQty const & qty				= in_delta.getQty();
			FOSPrice const & price					= in_delta.getPrice();
			size_t const level						= static_cast<size_t> (in_delta.getLevel());
			Types::OrderBookDeltaAction const action= in_delta.getAction();

			switch (action) 
			{
			case Types::OrderBookDeltaAction_AskClearFromLevel:			internalUpdateMBLDeltaClearFromLevel		(m_data.getAskLimits(),level);			break;
			case Types::OrderBookDeltaAction_BidClearFromLevel:			internalUpdateMBLDeltaClearFromLevel		(m_data.getBidLimits(),level);			break;
			case Types::OrderBookDeltaAction_ALLClearFromLevel:			
																		internalUpdateMBLDeltaClearFromLevel		(m_data.getAskLimits(),level);
																		internalUpdateMBLDeltaClearFromLevel		(m_data.getBidLimits(),level);
																		break;
			case Types::OrderBookDeltaAction_AskInsertAtLevel:			if (!internalUpdateMBLDeltaInsertAtLevel	(m_data.getAskLimits(),level,price,qty)) {
																			logUnexpectedNewMaxVisibleDepth(in_delta);
																		}																					break;
			case Types::OrderBookDeltaAction_BidInsertAtLevel:			if (!internalUpdateMBLDeltaInsertAtLevel	(m_data.getBidLimits(),level,price,qty)) {
																			logUnexpectedNewMaxVisibleDepth(in_delta);
																		}																					break;
			case Types::OrderBookDeltaAction_AskRemoveLevelAndAppend:	internalUpdateMBLDeltaRemoveLevelAndAppend	(m_data.getAskLimits(),level,price,qty); break;
			case Types::OrderBookDeltaAction_AskRemoveLevel:			internalUpdateMBLDeltaRemoveLevel			(m_data.getAskLimits(),level); break;
			case Types::OrderBookDeltaAction_BidRemoveLevelAndAppend:	internalUpdateMBLDeltaRemoveLevelAndAppend	(m_data.getBidLimits(),level,price,qty); break;
			case Types::OrderBookDeltaAction_BidRemoveLevel:			internalUpdateMBLDeltaRemoveLevel			(m_data.getBidLimits(),level);break;
			case Types::OrderBookDeltaAction_AskChangeQtyAtLevel:		internalUpdateMBLDeltaChangeQtyAtLevel		(m_data.getAskLimits(),level,qty);		break;
			case Types::OrderBookDeltaAction_BidChangeQtyAtLevel:		internalUpdateMBLDeltaChangeQtyAtLevel		(m_data.getBidLimits(),level,qty);		break;
			default:
				logUnexpectedOrderBookDeltaAction(in_delta);
			}

			updateTimestampsAndOtherValues(in_delta.getTimestamps(), in_delta.getOtherValues());

			if (in_delta.getContinuationFlag())
			{
				m_ContinuationFlagSet = true;
				setTag(FeedOS::QuotationVariable_HasContinuationFlag(true));
			}
			else
			{
				m_ContinuationFlagSet = false;
				removeTag(FeedOS::TAG_HasContinuationFlag);
			}
		}

		// Real-time notification: overlap refresh (whole or part of Bid and/or Ask sides)
		void updateWithMBLOverlapRefresh	(	Types::MBLOverlapRefresh const & in_overlap	)
		{
			{
				bool is_full;
				if (!internalUpdateMBLOverlapRefreshOneSide (in_overlap.getBidChangeIndicator(),
															 in_overlap.getBidLimits(),m_data.getBidLimits(), is_full))
				{
					logUnexpectedNewMaxVisibleDepth(in_overlap);
				}
				if (is_full && !m_IsBidFull)
				{
					m_IsBidFull = true;
				}
			}
			{
				bool is_full;
				if (!internalUpdateMBLOverlapRefreshOneSide (in_overlap.getAskChangeIndicator(),
															 in_overlap.getAskLimits(),m_data.getAskLimits(), is_full))
				{
					logUnexpectedNewMaxVisibleDepth(in_overlap);
				}
				if (is_full && !m_IsAskFull)
				{
					m_IsAskFull = true;
				}
			}
			updateTimestampsAndOtherValues(in_overlap.getTimestamps(),in_overlap.getOtherValues());
			if (m_ContinuationFlagSet)
			{
				// sequence error: expected the continuation flag to be cleared by a Delta Refresh before dispatching an Overlap
				logOverlapClearsContinuationFlag(in_overlap);
				m_ContinuationFlagSet = false;
				removeTag(FeedOS::TAG_HasContinuationFlag);
			}
		}

		// Real-time notification: how deep is the visible part of the orderbook
		void updateWithMBLMaxVisibleDepth(	Types::MBLMaxVisibleDepth const & visible_depth)
		{
			setMaxVisibleDepth (visible_depth.getMaxVisibleDepth());
		}

		// if depth=-1 then retrieve the whole book
		void extractMBLLayer		(Types::MBLLayer & v, FOSLowLevelInteger requested_depth=-1) const
		{
			v = m_data;
			if (requested_depth<0) { return; }
			size_t const d = static_cast<size_t>(requested_depth);
			if (v.getBidLimits().size() > d) { v.getBidLimits().resize(d); }
			if (v.getAskLimits().size() > d) { v.getAskLimits().resize(d); }
		}

		// return false if all data has been received
		bool getAllDataHasBeenReceived() const	{ return m_IsBidFull && m_IsAskFull && !m_ContinuationFlagSet; }
		bool mayBeIncomplete() const			{ return !getAllDataHasBeenReceived(); }
		bool continuationFlagSet() const		{ return m_ContinuationFlagSet; }

		void						setMaxVisibleDepth(FOSLowLevelInteger mvd)
		{
			m_max_visible_depth_IS_KNOWN = true;
			m_data.setMaxVisibleDepth(mvd); 
			stripMBLOrderBookToVisibleDepth();
		}

		Types::MBLLayer	const &					getData ()				const { return m_data; }
		Types::UTCTimestamps const &			getTimestamps()			const { return m_data.getTimestamps(); }
		int										getMaxVisibleDepth()	const { return static_cast<int>(m_data.getMaxVisibleDepth()); }
		bool									getMaxVisibleDepthIfKnown(int & mvd)	const
		{
			if (m_max_visible_depth_IS_KNOWN)
			{
				mvd = getMaxVisibleDepth();
				return true;
			}
			return false;
		}
		Types::OrderBookLayerId					getLayerId()			const { return m_data.getLayerId(); }
		void									setLayerId(Types::OrderBookLayerId id) { m_data.getLayerId() = id; }
		Types::ListOfMBLOrderBookEntry const &	getBidLimits()			const { return m_data.getBidLimits(); }
		Types::ListOfMBLOrderBookEntry const &	getAskLimits()			const { return m_data.getAskLimits(); }
		Types::ListOfQuotationVariable const &	getOtherValues()		const { return m_data.getOtherValues(); }

		// return false if tag was not found
		bool getTag (Types::TagNumber tag_num, Any & tag_value) const;

		void setTag (Types::TagNumAndValue const & tag)
		{
			updateTag (tag.getNum(), tag.getValue());
		}

		void setTag (Types::TagNumber tag_num, Any const & tag_value)
		{
			updateTag (tag_num, tag_value);
		}

		void removeTag (Types::TagNumber tag_num)
		{
			updateTag (tag_num, Any());
		}

	private:

		FEEDOS_INLINE bool checkMBLOrderBookOverflowAfterInsert		(Types::ListOfMBLOrderBookEntry & side, size_t last_insert_level);
		FEEDOS_INLINE bool checkMBLOrderBookOverflowAfterOverlap	(Types::ListOfMBLOrderBookEntry & side);
		FEEDOS_INLINE bool updateMaxMBLOrderBookDepthAfterInsert	(size_t last_insert_level);	// return true if max_orderbook_depth has been updated
		FEEDOS_INLINE bool updateMaxMBLOrderBookDepthAfterOverlap	(size_t current_depth);		// return true if max_orderbook_depth has been updated

		// a value of Syntax_UNKNOWN removes the tag if found
		void updateTag (unsigned int const new_tag_num, Any const & new_tag_value)
		{
			Types::ListOfQuotationVariable & current_values = m_data.getOtherValues();
			for (	Types::ListOfQuotationVariable::iterator current_values_it = current_values.begin();
					current_values_it != current_values.end();
					++current_values_it
				) 
			{
				unsigned int const cur_tag_num  = current_values_it->getNum();
				if (cur_tag_num == new_tag_num)
				{
					// tag already present
					if (Syntax_UNKNOWN == new_tag_value.get_syntax())
					{
						// erase this tag
						current_values.erase(current_values_it);
					}
					else
					{
						// update this tag
						Any & cur_tag_value = current_values_it->getValue();
						// TODO (paranoid mode) check if syntax is changing
						cur_tag_value = new_tag_value;
					}
					return;	// RETURN HERE
				}
			}

			if (Syntax_UNKNOWN != new_tag_value.get_syntax())
			{
				// tag was not found and has a value. Add it
				current_values.push_back(Types::QuotationVariable(static_cast<Types::TagNumber> (new_tag_num), new_tag_value));
			}
		}

		void updateTimestampsAndOtherValues (	Types::UTCTimestamps const & timestamps,
												Types::ListOfQuotationVariable const & new_values)
		{
			m_data.setTimestamps(timestamps);
			for (	Types::ListOfQuotationVariable::const_iterator new_values_it = new_values.begin();
					new_values_it!= new_values.end(); 
					++new_values_it
				) 
			{
				unsigned int const new_tag_num  = new_values_it->getNum();
				Any const & new_tag_value = new_values_it->getValue();
				updateTag (new_tag_num, new_tag_value);
			}
		}

		// logging 
		void logUnexpectedOrderBookDeltaAction	(Types::MBLDeltaRefresh const & in_delta) const;
		void logUnexpectedNewMaxVisibleDepth	(Types::MBLDeltaRefresh const & in_delta) const;
		void logUnexpectedNewMaxVisibleDepth	(Types::MBLOverlapRefresh const & in_overlap) const;
		void logOverlapClearsContinuationFlag	(Types::MBLOverlapRefresh const & in_overlap) const;

		void stripMBLOrderBookToVisibleDepth		(	)
		{
			FOSLowLevelInteger const max_visible_depth = getMaxVisibleDepth();
			if (FeedOS::Types::ORDERBOOK_UNLIMITED_DEPTH == max_visible_depth)
			{
				return; 
			}
			size_t const d = static_cast<size_t>(max_visible_depth);
			if (m_data.getBidLimits().size() > d) m_data.getBidLimits().resize(d);
			if (m_data.getAskLimits().size() > d) m_data.getAskLimits().resize(d);
		}

		void internalUpdateMBLDeltaClearFromLevel	(	Types::ListOfMBLOrderBookEntry & dest, 
														size_t level)
		{	
			if (dest.size() > level)
			{
				dest.resize(level);	
			}
		}

		void internalUpdateMBLDeltaRemoveLevelAndAppend	(	Types::ListOfMBLOrderBookEntry & dest, 
													size_t level, 
													FOSPrice const & price, 
													Types::MBLQty const & qty)
		{
			if (dest.size() > level)
			{
				dest.erase (dest.begin()+level);
				dest.push_back (Types::MBLOrderBookEntry(price,qty));
			}
		}

		void internalUpdateMBLDeltaRemoveLevel	(	Types::ListOfMBLOrderBookEntry & dest, 
													size_t level
												)
		{
			if (dest.size() >  level)
			{
				dest.erase (dest.begin()+level);
			}
		}

		void internalUpdateMBLDeltaChangeQtyAtLevel(	Types::ListOfMBLOrderBookEntry & dest, 
														size_t level, 
														Types::MBLQty const & qty)
		{
			if (dest.size() > level)
			{
				dest[level].setQty (qty);
			}
		}

		bool internalUpdateMBLDeltaInsertAtLevel	(	Types::ListOfMBLOrderBookEntry & dest,
														size_t level, 
														FOSPrice const & price, 
														Types::MBLQty const & qty)
		{
			if (dest.size() >= level)
			{
				dest.insert (dest.begin()+level,Types::MBLOrderBookEntry(price,qty));
				return checkMBLOrderBookOverflowAfterInsert(dest, level);
			}
			return true;
		}

		// return true if update conveys the bottom of the half-book
		bool internalUpdateMBLOverlapRefreshOneSide(	FOSLowLevelInteger const source_Indicator, 
														Types::ListOfMBLOrderBookEntry const & source, 
														Types::ListOfMBLOrderBookEntry & dest,
														bool & is_full)
		{
			unsigned int source_start_level;
			Types::split_OrderBookChangeIndicator (static_cast<int>(source_Indicator), is_full, source_start_level);

			size_t const projected_dest_size = source_start_level+source.size();
			size_t const current_depth = dest.size();

			if (current_depth < source_start_level) {
				// received an update BEYOND CURRENT DATA (should not occur / race condition)
				// wait for better limits to come
			} else {
				if (current_depth < projected_dest_size) {
					// [OVERLAP+]APPEND
					dest.resize (projected_dest_size);
					std::copy (source.begin(),source.end(),dest.begin()+source_start_level);
					return checkMBLOrderBookOverflowAfterOverlap (dest);

				} else { 
					// OVERLAP
					// @TODO: protect hourself against invalid Overlap data and avoid memory corruption
					std::copy (source.begin(),source.end(),dest.begin()+source_start_level);
					if (is_full && (dest.size() > projected_dest_size))
						dest.resize (projected_dest_size);		// strip obsolete data
				}
			}
			return true;
		}

		int internalCheckMBLOrderBookConsistency			(		Types::ListOfMBLOrderBookEntry const & source, 
																	bool is_ask, 
																	bool feedos_log) const;

		int internalCheckMBLOrderBookPriceQtyNbOrders		 (		FOSPrice const & cur_price, 
																	Types::MBLQty const & cumulated_qty, 
																	Types::FOSOrderBookLevel const & i, 
																	bool feedos_log) const;

		int internalCheckMBLOrderBookBBidAsk				(		Types::ListOfMBLOrderBookEntry const &, 
																	Types::ListOfMBLOrderBookEntry const &, 
																	bool) const;
	public:

		int internalCheckMBLOrderBookConsistancy			(		bool feedos_log = false) const;
	};


	/**
	 * @brief class dedicated to manage a multi-layer orderbooks for a FeedOS instrument
	 */
	class InstrumentMBLData
	{
		typedef Types::ListOfMBLSnapshot::const_iterator		TSnapshotConstIter;
		typedef std::vector<Types::MBLLayer>::const_iterator	TMBLLayerConstIter; 
		typedef std::vector<LayerMBLData>::iterator				TLayerMBLDataIter;
		typedef std::vector<LayerMBLData>::const_iterator		TLayerMBLDataConstIter;

	public:
		InstrumentMBLData ()								{ }
		InstrumentMBLData (FOSInstrumentCode const & code)	{ m_InstrCode = code; }
		InstrumentMBLData (InstrumentMBLData const & v)		{ operator=(v); }
#if 0 // ON PURPOSE
		virtual ~InstrumentMBLData () { }
#endif

		FOSInstrumentCode const &	getInternalCode () const	{ return m_InstrCode; }

		void setInstrumentCode (FOSInstrumentCode const & instr_code)
		{
			m_InstrCode = instr_code;
		}

		void reset (FOSInstrumentCode const & instr_code)
		{
			m_MBLLayers.clear();
			m_InstrCode = instr_code;
		}

		/**
		 * @brief access to an MBLLayer thanks to its layer id, insert a new one if needed
		 * @param layer_id layer identifier
		 */
		LayerMBLData &	getOrInsertMBLLayerById(Types::OrderBookLayerId layer_id)
		{
			TLayerMBLDataIter const end = m_MBLLayers.end();
			for (TLayerMBLDataIter it = m_MBLLayers.begin(); end != it; ++it)
			{
				if (layer_id == it -> getLayerId()) 
				{
					return *it;
				}
			}
			m_MBLLayers.push_back (LayerMBLData(layer_id));
			return m_MBLLayers.back();
		}

		/**
		 * @brief access to an MBLLayer thanks to its layer id (non-const flavour)
		 * @param layer_id layer identifier
		 */
		LayerMBLData *		getMBLLayerById(Types::OrderBookLayerId layer_id)
		{
			TLayerMBLDataIter const end = m_MBLLayers.end();
			for (TLayerMBLDataIter it = m_MBLLayers.begin(); end != it; ++it)
			{
				if (layer_id == it -> getLayerId()) 
				{
					return &(*it);
				}
			}
			return NULL;
		}

		/**
		 * @brief access to an MBLLayer thanks to its layer id (const flavour)
		 * @param layer_id layer identifier
		 */
		LayerMBLData const *	getMBLLayerById(Types::OrderBookLayerId layer_id) const
		{
			TLayerMBLDataConstIter const end = m_MBLLayers.end();
			for (TLayerMBLDataConstIter it = m_MBLLayers.begin(); end != it ; ++it)
			{
				if (layer_id == it -> getLayerId()) 
				{
					return &(*it);
				}
			}
			return NULL;
		}

		/**
		 * @brief remove an MBLLayer
		 * @param layer_id id of the layer to remove
		 */
		void removeLayerById(Types::OrderBookLayerId layer_id)
		{
			TLayerMBLDataIter const end = m_MBLLayers.end();
			for (TLayerMBLDataIter it = m_MBLLayers.begin(); end != it; ++it)
			{
				if (layer_id == it -> getLayerId())
				{
					m_MBLLayers.erase(it);
					return;	// RETURN HERE
				}
			}
		}

		void updateWithMBLFullRefresh		(	Types::ListOfMBLLayer const & layers )
		{
			// erasing layers first
			m_MBLLayers.clear();
			TMBLLayerConstIter const end = layers.end();
			for (TMBLLayerConstIter it = layers.begin(); end != it; ++it)
			{
				getOrInsertMBLLayerById(it->getLayerId()).updateWithMBLFullRefresh(*it);
			}
		}

		// Real-time notification
		// return the impacted layer
		LayerMBLData &	updateWithMBLDeltaRefresh	(	Types::MBLDeltaRefresh const & in_delta	)
		{
			LayerMBLData & l = getOrInsertMBLLayerById(in_delta.getLayerId());
			l.updateWithMBLDeltaRefresh(in_delta);
			return l;
		}

		// Real-time notification
		// return the impacted layer
		LayerMBLData &	updateWithMBLOverlapRefresh	(	Types::MBLOverlapRefresh const & in_overlap	)
		{
			LayerMBLData & l = getOrInsertMBLLayerById(in_overlap.getLayerId());
			l.updateWithMBLOverlapRefresh(in_overlap);
			return l;
		}

		// Real-time notification
		// return the impacted layer
		LayerMBLData & updateWithMBLMaxVisibleDepth(	Types::MBLMaxVisibleDepth const & in_visible_depth)
		{
			LayerMBLData & l = getOrInsertMBLLayerById(in_visible_depth.getLayerId());
			l.updateWithMBLMaxVisibleDepth(in_visible_depth);
			return l;
		}

		// return false if the given layer was not found
		bool extractMBLLayer		(Types::OrderBookLayerId layer_id, Types::MBLLayer & v, FOSLowLevelInteger depth=-1) const
		{
			LayerMBLData const * l = getMBLLayerById(layer_id);
			if (l)
			{
				l->extractMBLLayer (v, depth);
				return true;
			}
			return false;
		}

		FOSLowLevelInteger getMaxVisibleDepth(Types::OrderBookLayerId layer_id) const
		{
			LayerMBLData const * l = getMBLLayerById (layer_id);
			return (l ? l->getMaxVisibleDepth() : 0);
		}

		bool hasLayerId(Types::OrderBookLayerId layer_id) const
		{
			return (NULL != getMBLLayerById (layer_id));
		}

		size_t getLayerIds(Types::ListOfOrderBookLayerId & layer_ids) const
		{
			layer_ids.clear();
			TLayerMBLDataConstIter const end = m_MBLLayers.end();
			for (TLayerMBLDataConstIter it = m_MBLLayers.begin(); end != it; ++it)
			{
				layer_ids.push_back(static_cast<uint32>(it -> getLayerId()));
			}
			return (layer_ids.size());
		}

		std::vector<LayerMBLData> const & getLayers() const { return m_MBLLayers; }

		/**
		 * @brief merge all snapshot's layers in specified layer id (and remove others merged layers if keep_layers_alive is false)
		 * @param[in] layer_id_merged is of the layer to merge all layers, layer will be created if needed				 
		 * @param[in] use_latest_server_timestamp merge server timestamp policy
		 * @param[in] use_latest_market_timestamp merge market timestamp policy
		 * @param[in] merge_variables do merge OtherValues attached to each layer if yes.
		 * @param[in] keep_layers_alive if true, merged layers are preserved (as a consequence, the layer_id_merged cannot be a layer_id already stored in the snapshot).
		 * @return true if a merge has been done
		 */
		bool mergeAllLayers(Types::OrderBookLayerId const target_layer_id = Types::ORDERBOOK_LAYER_DEFAULT,
							bool use_latest_server_timestamp=MBLMergeLayerConstants::s_UseLatestServerTimestamp,
							bool use_latest_market_timestamp=MBLMergeLayerConstants::s_UseLatestMarketTimestamp,
							bool merge_other_values=MBLMergeLayerConstants::s_MergeVariables,
							bool preserve_merged_layers=MBLMergeLayerConstants::s_PreserveMergedLayers
							);

		/**
		 * @brief dump all layers
		 */
		void dump (std::vector<Types::MBLLayer> & layers) const;

		// dump the set of requested layers (if present)
		void dump (std::vector<Types::MBLLayer> & layers, std::vector<Types::OrderBookLayerId> const & requested_list) const;

	private:
		FOSInstrumentCode								m_InstrCode;
		std::vector<LayerMBLData>						m_MBLLayers;
	};


#ifdef	FEEDOS_INLINE_ENABLED
#	include "internal/InstrumentMBLData.inl"
#endif


	class InstrumentMBLData_with_lock: public InstrumentMBLData
	{
		InstrumentMBLData_with_lock const & operator= (InstrumentMBLData_with_lock const & v);	// operation not permitted
		ExclusiveLock									m_MBLLock;
	public:
		InstrumentMBLData_with_lock ()								{ }
		InstrumentMBLData_with_lock (FOSInstrumentCode const & code) : InstrumentMBLData(code) {}
		virtual ~InstrumentMBLData_with_lock () { }

		// locked flavour of parent's methods

		void updateWithMBLDeltaRefresh	(	Types::MBLDeltaRefresh const & in_delta	)
		{
			SCOPE_AUTO_LOCK (l,getLock4MBL()); 
			InstrumentMBLData::updateWithMBLDeltaRefresh(in_delta);
		}

		void updateWithMBLOverlapRefresh	(	Types::MBLOverlapRefresh const & in_overlap	)
		{
			SCOPE_AUTO_LOCK (l,getLock4MBL()); 
			InstrumentMBLData::updateWithMBLOverlapRefresh(in_overlap);
		}

		void updateWithMBLMaxVisibleDepth(	Types::MBLMaxVisibleDepth const & in_visible_depth)
		{
			SCOPE_AUTO_LOCK (l,getLock4MBL()); 
			InstrumentMBLData::updateWithMBLMaxVisibleDepth(in_visible_depth);
		}

		ExclusiveLock	const &		getLock4MBL() const							{ return m_MBLLock; }

		void getLayers(std::vector<LayerMBLData> & result) const
		{
			SCOPE_AUTO_LOCK (l,getLock4MBL()); 
			result = InstrumentMBLData::getLayers();
		}

	};

}

#endif
