
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_FRAMEWORK_H
#define FEEDOS_FRAMEWORK_FRAMEWORK_H

#ifndef FEEDOS_BASE_BASE_H
#  include "../base/base.h"
#endif

namespace FeedOS {
	namespace Framework {

		void init (char const * application_name);
		void shutdown ();
		void check_init_done ();

	} // namespace Framework
} // namespace FeedOS

#endif
