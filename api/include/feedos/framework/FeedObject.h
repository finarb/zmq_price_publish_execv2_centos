
/*****************************************/
/** FeedOS C++ Client API			 	**/
/**									 	**/
/** copyright QuantHouse 2005-2009		**/
/**										**/
/*****************************************/

#ifndef FEEDOS_FRAMEWORK_FEEDOBJECT_H
#define FEEDOS_FRAMEWORK_FEEDOBJECT_H

#ifndef FEEDOS_API_API_H
#  include "../api/api.h"
#endif

namespace FeedOS
{

class FeedObject : public StartableObject
{
public:
	FeedObject(Object & derived_instance, std::string const & instance_name)
		: StartableObject(derived_instance, instance_name)
	{
	}
	virtual void get_counters (uint64 & bytes_recv, uint64 & datagram_recv) const = 0;
	virtual void reset_counters () = 0;
	virtual void set_observer(MsgDispatchingHooksBase *) = 0;
};

} // namespace FeedOS

#endif // FEEDOS_FEEDOBJECT_H
