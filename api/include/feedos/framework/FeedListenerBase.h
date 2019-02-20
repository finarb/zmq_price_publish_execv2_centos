
/*****************************************/
/** FeedOS C++ Client API			 	**/
/**									 	**/
/** copyright QuantHouse 2005-2012		**/
/**										**/
/*****************************************/

#ifndef FEEDOS_FRAMEWORK_FEEDLISTENER_BASE_H
#define FEEDOS_FRAMEWORK_FEEDLISTENER_BASE_H

namespace FeedOS
{

	class INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming;
	class INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming;
	class INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming;

	class FeedListenerBase
	{

	public:
		virtual ~FeedListenerBase () { }

		/*! Return the L1 consumer (inprocess only).
		 */
		virtual INTERFACE_QUOTATION_SubscribeAllDataAndStatus_streaming *get_L1_consumer () const = 0;

		/*! Return the L2 consumer (inprocess only).
		 */
		virtual INTERFACE_QUOTATION_SubscribeAllOrderBook_streaming *get_L2_consumer () const = 0;

		/*! Return the MBO consumer (inprocess only).
		 */
		virtual INTERFACE_QUOTATION_SubscribeAllMarketSheet_streaming *get_MBO_consumer () const = 0;

	};

}

#endif
