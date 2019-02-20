
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_MULTICAST_DEFINITIONS_H
#define FEEDOS_COMM_MULTICAST_DEFINITIONS_H

#ifndef FEEDOS_COMM_MARKET_ID_H
#  include "FOSMarketId.h"
#endif

#define FOS_MCAST_EXTENSION			"fos_mcast"	// TODO: move this to Multicast_file_storage

namespace FeedOS {

class Multicast_definitions
{
public:

	static unsigned int const MCAST_IP_UPPER_8BITS_DEFAULT		=	232;
	static unsigned int const MCAST_IP_UPPER_8BITS_MIN			=	224;
	static unsigned int const MCAST_IP_UPPER_8BITS_MAX			=	239;

	static unsigned int const MCAST_PORT_BASE					=	10000;

	static unsigned int const MCAST_ID_MIN_VALUE				=	10;		// values below this are for TEST PURPOSES (*not* Production env.)
	static unsigned int const MCAST_ID_MAX_VALUE				=	(1 << 16) - 1;
	static unsigned int const MCAST_ID_MAX_VALID_FOR_LISTENING	=	MCAST_ID_MAX_VALUE;

	static std::string const GLOBAL_PSEUDO_SOURCE_NAME;			// "GLOBAL"
	static unsigned int const GLOBAL_PSEUDO_SOURCE_ID			= 0;

	static int const SHARED_PseudoServerId = 0;

	typedef enum {

		InternalSwarm			= 1,
		QuotationDataAndStatus	= 2,
		QuotationOrderBook		= 3,
		QuotationMixedL1L2		= 4,
		QuotationMarketSheet	= 5,
		QuotationIntradayBars	= 6,
		ConnectionFeedStatus	= 7,
		Multiplexed				= 8,
		News					= 9,
		ReferentialData			= 10,

        MAX_PREDEFINED_SERVICES

	} PredefinedServices;

	typedef enum {
		TTL_Scope_host			= 0,
		TTL_Scope_subnet		= 1,
		TTL_Scope_site			= 32,
		TTL_Scope_region		= 64,
		TTL_Scope_continent		= 128,
		TTL_Scope_unrestricted	= 255
	} TTL_Scope;

	static bool			ttl_scope2str			(std::string & str, TTL_Scope scope); 

	static char const * service_number2string (PredefinedServices s);
	static bool			service_string2number (PredefinedServices & s, char const * service_name);

	static bool compute_multicast_channel_address (	
											// output
											std::string & group_ip,
											int & group_port,
											bool & is_seqnum_enabled,
											// input
											int group_ip_upper_8bits,
											int server_id,
											PredefinedServices service_number,
											FOSMarketId	market_id
										);

};

} // namespace FeedOS

#endif 
