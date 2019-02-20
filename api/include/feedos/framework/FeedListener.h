
/*****************************************/
/** FeedOS C++ Client API			 	**/
/**									 	**/
/** copyright QuantHouse 2005-2010		**/
/**										**/
/*****************************************/

#ifndef FEEDOS_FRAMEWORK_FEEDLISTENER_H
#define FEEDOS_FRAMEWORK_FEEDLISTENER_H

#include "FeedListenerBase.h"

#ifndef FEEDOS_API_API_H
#  include "../api/api.h"
#endif

#ifndef FEEDOS_COMM_MULTICAST_FEED_TOOLS_H
#  include "../comm/MulticastFeedTools.h"
#endif

#ifndef FEEDOS_deprecated_NOTIF_OrderBookRefresh_H
#  include "../deprecated/deprecated_notif_OrderBookRefresh.h"
#endif

#include <set>

namespace FeedOS
{

class FeedObject;
class InstrumentReferentialData;
class InstrumentFilter_QuotationAllDataAndStatus;
class InstrumentFilter_QuotationAllOrderBook;
class InstrumentFilter_QuotationAllMarketSheet;
class PDU_L1_dispatcher;
class PDU_L2_dispatcher;
class PDU_MBO_dispatcher;
class IPCSharedMemoryOptions;
class RecoveryObserver;
class MsgDispatchingHooksBase;

template<class CONSUMER, class FILTER, class DISPATCHER> class Subscriber;
class Subscriber_MixedL1L2;
class RefDownload;

/*! Interface to implement to handle RealTime L1 stream
*/
class RealtimeHandler_L1:	public virtual INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming
{

public:

	// not used
	virtual void response_QUOTATION_SubscribeAllDataAndStatus_Started ()	{}
	virtual void response_QUOTATION_SubscribeAllDataAndStatus_Failed (ReturnCode /*rc*/)	{}
	virtual void aborted_QUOTATION_SubscribeAllDataAndStatus (ReturnCode /*rc*/)	{}

	// optional notification
	virtual void notif_MarketNews	(FeedOS::Types::MarketNews const & /*inNews*/)
	{
		// default is to ignore this event
	}

private:
	// obsolete notifications
	virtual void notif_TradeEvent	(FOSInstrumentCode /*inInternalCode*/, Timestamp const & /*inMarketUTCTimestamp*/,  FeedOS::Types::QuotationTradeEvent const & /*inData*/) {}
	virtual void notif_ValuesUpdate	(FOSInstrumentCode /*inCode*/, Timestamp const & /*inMarketUTCTimestamp*/,  FeedOS::Types::QuotationValuesUpdate const & /*inData*/) {}
	virtual void notif_MarketStatus	(FeedOS::Types::MarketStatus const & /*inStatus*/) {}
};


// Optional L1 snapshot handler
class SnapshotHandler_L1
{

public:
	virtual ~SnapshotHandler_L1() { }

	// response callback : success + outputs
	virtual void response_SnapshotInstrumentsL1_Success (Types::ListOfInstrumentStatusL1 const & result) = 0;

	// response callback : some error occurred
	virtual void response_SnapshotInstrumentsL1_Failed (ReturnCode rc) = 0;
};

/*! Interface to implement to handle RealTime L2 stream
*/
class RealtimeHandler_L2:	public virtual FeedOS::INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming_v18_USE_NEW_NOTIF
{
public:
	// not used
	virtual void response_QUOTATION_SubscribeAllOrderBook_Started()	{}
	virtual void response_QUOTATION_SubscribeAllOrderBook_Failed(FeedOS::ReturnCode /*rc*/)	{}
	virtual void aborted_QUOTATION_SubscribeAllOrderBook(FeedOS::ReturnCode /*rc*/)	{}
};

// Optional MBL snapshot handler
class SnapshotHandler_L2
{

public:
	virtual ~SnapshotHandler_L2() { }

	// response callback : success + outputs
	virtual void response_SnapshotInstrumentsL2_Success (Types::ListOfMBLSnapshot const & result) = 0;

	// response callback : some error occurred
	virtual void response_SnapshotInstrumentsL2_Failed (ReturnCode rc) = 0;

};

/*! Interface to implement to handle RealTime MBO stream
*/
class RealtimeHandler_MBO:	public virtual FeedOS::INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming
{
public:
	// not used
	virtual void response_QUOTATION_SubscribeAllMarketSheet_Started () {}
	virtual void response_QUOTATION_SubscribeAllMarketSheet_Failed (ReturnCode /*rc*/) {}
	virtual void aborted_QUOTATION_SubscribeAllMarketSheet (ReturnCode /*rc*/) {}
};

// Optional MBO snapshot handler
class SnapshotHandler_MBO
{

public:
	virtual ~SnapshotHandler_MBO() { }

	// response callback : success + outputs
	virtual void response_SnapshotInstrumentsMBO_Success (Types::ListOfInstrumentStatusMarketSheet const & result) = 0;

	// response callback : some error occurred
	virtual void response_SnapshotInstrumentsMBO_Failed (ReturnCode rc) = 0;

};

/*! Interface to implement to handle RealTime and Snapshot data for the L1 stream
*/
class FeedHandler_L1:	public RealtimeHandler_L1,
						public SnapshotHandler_L1
{
};

/*! Interface to implement to handle RealTime and Snapshot data for the L2 stream
*/
class FeedHandler_L2:	public RealtimeHandler_L2,
						public SnapshotHandler_L2
{
};

/*! Interface to implement to handle RealTime and Snapshot data for the MBO stream
*/
class FeedHandler_MBO:	public RealtimeHandler_MBO,
						public SnapshotHandler_MBO
{
};

/*! Object to instantiate to subscribe to multicast stream of one FrontEnd
*/
class FeedListener
	: public FeedListenerBase, public StartableObject
	, public INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming
{
	FeedListener(const FeedListener&);
	FeedListener& operator=(const FeedListener&);

public:
	/*! Underlying feed transport.
	 */
	enum Transport
	{
		Multicast,
		SharedMemory,
		InProcess
	};

	FeedListener(std::string const & instance_name);
	~FeedListener();

	/*! Retrieve the number of packets and bytes received on the multicast stream
	*/
	void get_counters (uint64 & bytes_received, uint64 & packets_received) const;

	/*! Reads the configuration file and stores connection and subscription parameters.
	 *
	 * start_object() should then be called to connect to the front end server
	 * and download the referential data.
	 *
	 * \return false if an error occurred while parsing the file,
	 * true otherwise.
	 */
	bool load_config(std::string const & filename);

	std::string const & get_config_login () const { return m_config_login; }
	std::string const & get_config_password () const { return m_config_password; }
	std::string const & get_config_server_ip () const { return m_config_server_ip; }
	int					get_config_server_port() const { return m_config_server_port; }
	API::Connection	& get_config_connection() { return m_connection; }

	/*! Set the consumer handling RealTime L1 data
	 */
	void set_realtime_consumer_L1(INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming & rt_consumer);

	/*! Set the consumer handling Snapshot L1 data
	 */
	void set_snapshot_consumer_L1(SnapshotHandler_L1 & snapshot_consumer);

	template<typename T>
	void set_consumer_L1(T&c)
	{
		set_realtime_consumer_L1(c);
		set_snapshot_consumer_L1(c);
	}

	/*! Set the consumer handling RealTime L2 data
	 */
	void set_realtime_consumer_L2(INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming & rt_consumer);
	
	/*! Set the consumer handling Snapshot L2 data
	 */
	void set_snapshot_consumer_L2(SnapshotHandler_L2 & snapshot_consumer);

	/*! Set the consumer handling Snapshot MBO data
	 */
	void set_snapshot_consumer_MBO(SnapshotHandler_MBO & snapshot_consumer);

	template<typename T>
	void set_consumer_L2(T&c)
	{
		set_realtime_consumer_L2(c);
		set_snapshot_consumer_L2(c);
	}

	/*! Set the consumer handling RealTime MBO data
	 */
	void set_realtime_consumer_MBO(INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming & rt_consumer);

	template<typename T>
	void set_consumer_MBO(T&c)
	{
		set_realtime_consumer_MBO(c);
		set_snapshot_consumer_MBO(c);
	}

	/*! L1-Subscribes to the given list of instruments
	 *
	 * Note: In mixedL1L2 mode, this method is invalid. You need to use subscribe_L1L2_by_instruments
	 *
	 * \param instr_list List of InstrumentCode to subscribe
	 * \param snapshot_tag_list List of additional QuotationTag to retrieve during Snapshot
	 * \return false if an error occurred.
	 */
	bool subscribe_L1_by_instruments(	Types::ListOfPolymorphicInstrumentCode const & instr_list,
										Types::ListOfQuotationTagNumber const & snapshot_tag_list = Types::ListOfQuotationTagNumber());

	/*! L1-Subscribes to a single instrument
	 *
	 * Note: In mixedL1L2 mode, this method is invalid. You need to use subscribe_L1L2_by_instrument
	 *
	 * \param instr InstrumentCode of the instrument to subscribe
	 * \param snapshot_tag_list List of additional QuotationTag to retrieve during Snapshot. By default, only retrieve the default QuotationTags.
	 * \return false if an error occurred.
	 */
	bool subscribe_L1_by_instrument(	PolymorphicInstrumentCode const & instr,
										Types::ListOfQuotationTagNumber const & snapshot_tag_list = Types::ListOfQuotationTagNumber())
	{
		return subscribe_L1_by_instruments (ListOfPolymorphicInstrumentCode(1,instr), snapshot_tag_list);
	}

	/*! L2-Subscribes to the given list of instruments
	 *
	 * Note: In mixedL1L2 mode, this method is invalid. You need to use subscribe_L1L2_by_instruments
	 *
	 * \param instr_list List of InstrumentCode to subscribe
	 * \param snapshot_layer_list List of layers to retrieve (Snapshot and RealTime), other will not be requested (Snapshot) or filtered (RealTime)
	 * \return false if an error occurred.
	 */
	bool subscribe_L2_by_instruments(	Types::ListOfPolymorphicInstrumentCode const & instr_list,
										Types::ListOfOrderBookLayerId const & snapshot_layer_list = Types::ListOfOrderBookLayerId ());

	/*! L2-Subscribes to a signal instrument
	 *
	 * Note: In mixedL1L2 mode, this method is invalid. You need to use subscribe_L1L2_by_instrument
	 *
	 * \param instr InstrumentCode of the instrument to subscribe
	 * \param snapshot_layer_list List of layers to retrieve (Snapshot and RealTime), other will not be requested (Snapshot) or filtered (RealTime).
	 * \return false if an error occurred.
	 */
	bool subscribe_L2_by_instrument(	PolymorphicInstrumentCode const & instr,
										Types::ListOfOrderBookLayerId const & snapshot_layer_list = Types::ListOfOrderBookLayerId ())
	{
		return subscribe_L2_by_instruments (ListOfPolymorphicInstrumentCode(1,instr), snapshot_layer_list);
	}

	/*! MBO-Subscribes to the given list of instruments
	 *
	 * \param instr_list List of InstrumentCode to subscribe
	 * \return false if an error occurred.
	 */
	bool subscribe_MBO_by_instruments(	Types::ListOfPolymorphicInstrumentCode const & instr_list);

	/*! MBO-Subscribes to a signal instrument
	 *
	 * \param instr InstrumentCode of the instrument to subscribe
	 * \return false if an error occurred.
	 */
	bool subscribe_MBO_by_instrument(	PolymorphicInstrumentCode const & instr)
	{
		return subscribe_L2_by_instruments (ListOfPolymorphicInstrumentCode(1,instr));
	}

	/*! L1L2-Subscribes to the given list of instruments
	 *
	 * \param instr InstrumentCode of the instrument to subscribe
	 * \param snapshot_tag_list List of additional QuotationTag to retrieve during Snapshot. By default, only retrieve the default QuotationTags.
	 * \param snapshot_layer_list List of layers to retrieve (Snapshot and RealTime), other will not be requested (Snapshot) or filtered (RealTime).
	 * \return false if an error occurred.
	 */
	bool subscribe_L1L2_by_instruments(	Types::ListOfPolymorphicInstrumentCode const & instr_list,
										Types::ListOfQuotationTagNumber const & snapshot_tag_list = Types::ListOfQuotationTagNumber(),
										Types::ListOfOrderBookLayerId const & snapshot_layer_list = Types::ListOfOrderBookLayerId ());

	/*! L1L2-Subscribes to a signal instrument
	 *
	 * \param instr InstrumentCode of the instrument to subscribe
	 * \param snapshot_tag_list List of additional QuotationTag to retrieve during Snapshot. By default, only retrieve the default QuotationTags.
	 * \param snapshot_layer_list List of layers to retrieve (Snapshot and RealTime), other will not be requested (Snapshot) or filtered (RealTime).
	 * \return false if an error occurred.
	 */
	bool subscribe_L1L2_by_instrument(	PolymorphicInstrumentCode const & instr,
										Types::ListOfQuotationTagNumber const & snapshot_tag_list = Types::ListOfQuotationTagNumber(),
										Types::ListOfOrderBookLayerId const & snapshot_layer_list = Types::ListOfOrderBookLayerId ())
	{
		return subscribe_L1L2_by_instruments (ListOfPolymorphicInstrumentCode(1,instr), snapshot_tag_list, snapshot_layer_list);
	}

	/*! L1-Subscribes to whole feed. No initial snapshot
	 * \return false if an error occurred.
	 */
	bool subscribe_L1_by_feed_name(std::string const & feed_name);

	/*! L1-Subscribes to whole feed. No initial snapshot
	 * \return false if an error occurred.
	 */
	bool subscribe_L1_by_source_id(int source_id);

	/*! L2-Subscribes to whole feed. No initial snapshot
	 * \return false if an error occurred.
	 */
	bool subscribe_L2_by_feed_name(std::string const & feed_name);

	/*! L2-Subscribes to whole feed. No initial snapshot
	 * \return false if an error occurred.
	 */
	bool subscribe_L2_by_source_id(int source_id);

	/*! MBO-Subscribes to whole feed. No initial snapshot
	 * \return false if an error occurred.
	 */
	bool subscribe_MBO_by_feed_name(std::string const & feed_name);

	/*! MBO-Subscribes to whole feed. No initial snapshot
	 * \return false if an error occurred.
	 */
	bool subscribe_MBO_by_source_id(int source_id);

	/*! L1L2-Subscribes to whole feed. No initial snapshot
	 * \return false if an error occurred.
	 */
	bool subscribe_L1L2_by_feed_name(std::string const & feed_name);

	/*! L1L2-Subscribes to whole feed. No initial snapshot
	 * \return false if an error occurred.
	 */
	bool subscribe_L1L2_by_source_id(int source_id);

	/*! Associate a user data to an instrument code
	 */
	void								register_user_data (FOSInstrumentCode const & instr, void * data);
	void								register_user_data (PolymorphicInstrumentCode const & instr, void * data);
	void *								get_user_data (FOSInstrumentCode const & instr) const;

	/*! Retrieve the referential data of an instrument
		\param instr The instrument's referential to retrieve, using its FOSInstrumentCode
		\return A non modifiable pointer to the ReferentialData of the instrument
	*/
	InstrumentReferentialData const *	get_referential_data (FOSInstrumentCode const & instr) const;

	/*! Retrieve the referential data of an instrument
		\param instr The instrument's referential to retrieve, using its LocalInstrumentCode
		\return A non modifiable pointer to the ReferentialData of the instrument
	*/
	InstrumentReferentialData const *	get_referential_data (LocalInstrumentCode const & instr) const;

	/*! Retrieve the referential data of an instrument
		\param instr The instrument's referential to retrieve, using its PolymorphicInstrumentCode
		\return A non modifiable pointer to the ReferentialData of the instrument
	*/
	InstrumentReferentialData const *	get_referential_data (PolymorphicInstrumentCode const & instr) const;

	/*! Resolve a FOSInstrumentCode in the equivalent LocalInstrumentCode structure if known
		\return The LocalInstrumentCode if the FOSInstrumentCode was found
	*/
	LocalInstrumentCode					convert_numeric_instrument_code (FOSInstrumentCode const & instr) const;

	/*! Resolve a LocalInstrumentCode in the equivalent FOSInstrumentCode structure if known
		\return the FOSInstrumentCode if the LocalInstrumentCode was found
	*/
	FOSInstrumentCode					resolve_instrument_code (LocalInstrumentCode const & instr) const;

	/*! Resolve a PolymorphicInstrumentCode in the equivalent FOSInstrumentCode structure if known
		\return the FOSInstrumentCode if the PolymorphicInstrumentCode was found
	*/
	FOSInstrumentCode					resolve_instrument_code (PolymorphicInstrumentCode const & instr) const;

	/*! Return true if mixedL1L2 feed is set, false otherwise.
	 */
	bool mixedL1L2_enabled () const { return m_config_enable_mixedL1L2; }

	Transport transport () const { return m_config_transport; }

	/*! Set the shared memory transport options.
	 */
	void setSharedMemoryOptions (IPCSharedMemoryOptions const &);

	/*! Return the L1 consumer (inprocess only).
	 */
	INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming *get_L1_consumer () const;

	/*! Return the L2 consumer (inprocess only).
	 */
	INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming *get_L2_consumer () const;

	/*! Return the MBO consumer (inprocess only).
	 */
	INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming *get_MBO_consumer () const;

	/*! Set the recovery observer
	 */
	void set_recovery_observer(RecoveryObserver &);

	/*! Provide an object to be notified when messages are being dispatched
	 */
	void set_dispatching_observer(MsgDispatchingHooksBase &);

	/*! Enable the internal queue.
	 */
	void enable_queue (unsigned int warning_level);

private:
	typedef FEEDOS_STLEXT_NAMESPACE::hash_map<FOSInstrumentCode		, InstrumentReferentialData*, FOSInstrumentCode::Hash> NumericInstrumentsCodeMap;
	typedef FEEDOS_STLEXT_NAMESPACE::hash_map<LocalInstrumentCode	, InstrumentReferentialData*, LocalInstrumentCode::Hash> LocalInstrumentsCodeMap;

	/*! Return true if the CFICode OR the MIC are listed in the configuration file
	 */
	bool is_allowed(CFICode const & cficode, FOSMarketId mic) const;
	void set_instruments(NumericInstrumentsCodeMap&, LocalInstrumentsCodeMap&);
	friend class RefDownload;

private:
	virtual bool	impl_start_object();
	virtual bool	impl_stop_object();

	ReturnCode sync_connect();

	// return true if connection is available
	bool	reconnect_if_needed();

	void abort_subscriptions();
	void clear_instr_maps();

	bool setup_mixedL1L2();
	bool setup_L1L2();

	template<class SUB>
	bool subscribe_by_instruments	(ListOfPolymorphicInstrumentCode const & input_poly_codes, SUB*);

	template<class SUB>
	bool subscribe_by_source_id		(unsigned int source_id, SUB*);

	template<class SUB>
	bool subscribe_by_feed_name		(std::string const & feed_name, SUB*);

	void snapshot_L1(ListOfPolymorphicInstrumentCode const &,	 Types::ListOfQuotationTagNumber const &);
	void snapshot_L2(ListOfPolymorphicInstrumentCode const &,	 Types::ListOfOrderBookLayerId const &	);
	void snapshot_MBO(ListOfPolymorphicInstrumentCode const &);

	bool read_server_parameters (unsigned int line_nb, std::string const &value_str,
								 std::string & ip, int & port);

	API_CONNECTION_SubscribeToFeedStatus_delegate	m_requester_feed_status;
	typedef std::map<std::string,std::vector<int> >	ListOfMcastIDsIndexedByFeedName;
	ListOfMcastIDsIndexedByFeedName					m_mcast_ids_by_feed_name;

	FEEDOS_GEN_DECL_INTERFACE_CONNECTION_SubscribeToFeedStatus_streaming

	INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming* m_consumer_L1;
	INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming* m_consumer_L2;
	INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming* m_consumer_MBO;

	SnapshotHandler_L1* m_snapshot_handler_L1;
	SnapshotHandler_L2* m_snapshot_handler_L2;
	SnapshotHandler_MBO* m_snapshot_handler_MBO;

	typedef FEEDOS_STLEXT_NAMESPACE::hash_map<FOSInstrumentCode, void *, FOSInstrumentCode::Hash> UserDataMap;
	UserDataMap m_user_data;

	NumericInstrumentsCodeMap m_instruments_by_numeric_code;
	LocalInstrumentsCodeMap m_instruments_by_local_code;

	Network::SocketListener_ptr	m_listener_thread;

	typedef Subscriber<INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming, InstrumentFilter_QuotationAllDataAndStatus, PDU_L1_dispatcher> Subscriber_L1;
	Subscriber_L1* m_subscriber_L1;

	typedef Subscriber<INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming, InstrumentFilter_QuotationAllOrderBook, PDU_L2_dispatcher> Subscriber_L2;
	Subscriber_L2* m_subscriber_L2;

	Subscriber_MixedL1L2* m_subscriber_mixedL1L2;

	typedef Subscriber<INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming, InstrumentFilter_QuotationAllMarketSheet, PDU_MBO_dispatcher> Subscriber_MBO;
	Subscriber_MBO* m_subscriber_MBO;

	typedef std::set<std::string> StringSet;
	typedef std::set<int> IntSet;

	API::Connection	m_connection;
	std::string		m_config_login;
	std::string		m_config_password;
	std::string		m_config_server_ip;
	int				m_config_server_port;
	std::string		m_config_recovery_server_ip;
	int				m_config_recovery_server_port;
	int				m_config_mcast_upper8bits;
	int				m_config_global_mcast_id;
	bool			m_config_enable_mixedL1L2;
	bool			m_config_disable_snapshot_L1;
	bool			m_config_disable_snapshot_L2;
	bool			m_config_disable_snapshot_MBO;
	std::string		m_config_ref_allowed_cficodes;
	StringSet		m_config_ref_allowed_mics;
	StringSet		m_config_subscribed_feednames;
	IntSet			m_config_subscribed_sourceids;
	Transport		m_config_transport;
	bool			m_config_enable_recovery;
	API::Connection	m_recovery_connection;
	bool			m_use_recovery_connection;
	std::string		m_config_mcast_binding_addr;
	RecoveryObserver *m_recovery_observer;
	MsgDispatchingHooksBase *m_observer;
	unsigned int	m_queue_warning_level;
	bool			m_enable_queue;
};

} // namespace FeedOS

#endif // FEEDOS_FEEDLISTENER_H
