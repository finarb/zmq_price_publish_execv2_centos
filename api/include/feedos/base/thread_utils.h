
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2011 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_THREAD_UTILS_H
#define FEEDOS_BASE_THREAD_UTILS_H

#ifndef FEEDOS_BASE_BASE_H
#  include "base.h"
#endif

namespace FeedOS {

	namespace ThreadUtilsHelper
	{
#if defined TARGET_PLATFORM_WIN32
		typedef unsigned int	TThreadId;
#else
		typedef pthread_t		TThreadId;
#endif

		/** Get the thread id
		  *
		  * @return the thread id
		  */
		inline TThreadId getCurrentThreadId() 
		{
#if defined TARGET_PLATFORM_WIN32
			return ::GetCurrentThreadId(); 
#else
			return pthread_self();
#endif
		}	
	}
}

#endif
