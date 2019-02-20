
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2018 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_API_VERSION_H
#define FEEDOS_API_API_VERSION_H

#ifndef FEEDOS_COMM_ERRORS_H
#  include "../comm/errors.h"
#endif

#define FEEDOS_API_VERSION_SYMBOL	v3_9_0_6
#define FEEDOS_API_VERSION_STRING	"v3.9.0.6"
#define FEEDOS_API_METADATA_VERSION	"v1.0.2.6"

namespace FeedOS {

	namespace API {

		void FEEDOS_API_VERSION_SYMBOL ();

		ReturnCode __init__ (char const * user_application_name);
		inline ReturnCode init (char const * user_application_name)
		{
			FeedOS::API::FEEDOS_API_VERSION_SYMBOL();
			return __init__ (user_application_name);
		}

	}
}

#endif
