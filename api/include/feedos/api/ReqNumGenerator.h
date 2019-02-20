
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_REQ_NUM_GENERATOR_H
#define FEEDOS_API_REQ_NUM_GENERATOR_H

#ifndef FEEDOS_COMM_TYPES_H
#  include "../comm/types.h"
#endif

#ifndef FEEDOS_BASE_LOCK_H
#  include "../base/lock.h"
#endif

namespace FeedOS {

	/// use this to generate "unique" request numbers
	class ReqNumGenerator
	{
	public:

		// req_nums higher than that are reserved for subscriptions
		static unsigned int const subscription_range_begin = 1000000;

		// req_nums higher than that are reserved for simple requests
		// req_nums lower than that are never generated
		static unsigned int const request_range_begin = 1000;


		ReqNumGenerator () :
			m_counter_req (request_range_begin),
			m_counter_sub (subscription_range_begin)
		{}

		inline RequestNumber new_req_num_for_request ()
		{
			RequestNumber n = ++m_counter_req;
			if (n < subscription_range_begin)	// case 1 (normal inc)
				return n;
			if (n == subscription_range_begin)	// case 2 (should wrap)
				return m_counter_req=request_range_begin+1;

			// case 3 (another thread is in case 2)
			return retry_req_num_for_request ();
		}

		inline RequestNumber new_req_num_for_subscription ()	
		{
			RequestNumber n = ++m_counter_sub;
			if (n > subscription_range_begin)	// case 1 (normal inc)
				return n;
			if (n == 0)							// case 2 (wrapped)
				return m_counter_sub=subscription_range_begin+1;

			// case 3 (another thread is in case 2)
			return retry_req_num_for_subscription ();
		}
	private:
		void operator=(ReqNumGenerator const &) {}	// dummy private operator
		LockedCounter	m_counter_req;
		LockedCounter	m_counter_sub;

		RequestNumber	retry_req_num_for_request ();
		RequestNumber	retry_req_num_for_subscription ();
	};


}

#endif
