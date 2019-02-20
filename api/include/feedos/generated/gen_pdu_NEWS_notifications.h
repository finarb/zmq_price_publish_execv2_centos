/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2005      **/
/** Author: Denery Fenouil         **/
/************************************/


#ifndef FEEDOS_generated_PDU_NEWS_NOTIFICATIONS_H
#define FEEDOS_generated_PDU_NEWS_NOTIFICATIONS_H

#ifndef FEEDOS_COMM_PDU_H
#  include "../comm/PDU.h"
#endif

#ifndef FEEDOS_generated_PDU_IDS_H
#  include "gen_pdu_ids.h"
#endif

#ifndef FEEDOS_generated_ENCODING_H
#  include "gen_encoding.h"
#endif

namespace FeedOS
{
	using namespace Types;

	namespace PDU_outbound_NEWS
	{
	class SubscribeNotif_NewsData: public PDU_outbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_NewsData (ListOfNewsData const & a) :
			PDU_outbound_SubscribeNotif (IDS::SubscribeNotif_NEWS_NewsData)
		{
			Encode_ListOfNewsData (*this, a);
		}
	};

	} // namespace PDU_outbound_NEWS


	namespace PDU_inbound_NEWS
	{
	class SubscribeNotif_NewsData: public PDU_inbound_SubscribeNotif
	{
	public:
		inline SubscribeNotif_NewsData (PDU const & p) :
			PDU_inbound_SubscribeNotif (IDS::SubscribeNotif_NEWS_NewsData, p)
		{
			Decode_ListOfNewsData (*this, m_News);
		}
		inline ListOfNewsData const & getNews() const { return m_News; }
	private:
		ListOfNewsData m_News;
	public:
		inline ListOfNewsData & _refNews() { return m_News; }
	};

	} // namespace PDU_inbound_NEWS

}
#endif
