
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_COMM_H
#define FEEDOS_COMM_COMM_H

#ifndef FEEDOS_BASE_BASE_H
#  include "../base/base.h"
#endif

namespace FeedOS {
	namespace Comm {

		void init ();
		void shutdown ();
		void check_init_done ();

	} // namespace Comm
} // namespace FeedOS

#endif
