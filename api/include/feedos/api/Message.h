
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_API_MESSAGE_H
#define FEEDOS_API_MESSAGE_H

#include "../comm/PDU.h"

#include <ostream>

namespace FeedOS {

	// used to uniquely identify a Client object (within a process, NOT across several FeedOS apps)
	typedef unsigned int RequesterId;
	class RequestHandler;


	class UniqueRequestId
	{
	public:
		UniqueRequestId (RequesterId requester_id, RequestNumber req_num) :
			m_requester_id (requester_id), m_req_num (req_num)
		{}
		UniqueRequestId (UniqueRequestId const & v) :
			m_requester_id (v.m_requester_id), m_req_num (v.m_req_num)
		{}
		UniqueRequestId () :
			m_requester_id (0), m_req_num (0)
		{}

		UniqueRequestId const & operator= (UniqueRequestId const & v) { m_req_num=v.m_req_num; m_requester_id=v.m_requester_id; return *this; }

		RequesterId		get_requester_id() const { return m_requester_id; }
		RequestNumber	get_req_num		() const { return m_req_num; }

		bool operator== (UniqueRequestId const & v) const { return (m_requester_id == v.m_requester_id) && (m_req_num == v.m_req_num); }
		bool operator!= (UniqueRequestId const & v) const { return !operator== (v); }
		bool operator<  (UniqueRequestId const & r) const
		{
			if (get_requester_id() == r.get_requester_id())	return (get_req_num() < r.get_req_num());
			return (get_requester_id() < r.get_requester_id());
		}

		struct hasher
		{
			inline size_t operator()(UniqueRequestId const & v) const {
				return (size_t)v.get_requester_id() ^ (size_t)v.get_req_num();
			}
		};

	protected:
		RequesterId		m_requester_id;
		RequestNumber	m_req_num;
	};



	// authentication informations (UserId + GroupId)
	// default constructor sets uid=0,gid=0
	class AuthInfo
	{
	public:
		AuthInfo (unsigned int uid, unsigned int gid) :
			m_uid(uid), m_gid(gid)
		{}
		AuthInfo (AuthInfo const & v) :
			m_uid(v.m_uid), m_gid(v.m_gid)
		{}
		AuthInfo () :
			m_uid(0), m_gid(0)
		{}

		AuthInfo const & operator= (AuthInfo const & v) { m_uid=v.m_uid; m_gid=v.m_gid; return *this; }

		unsigned int	get_uid	() const { return m_uid; }
		unsigned int	get_gid	() const { return m_gid; }
		void			set_uid	(unsigned int uid) { m_uid=uid; }
		void			set_gid	(unsigned int gid) { m_gid=gid; }
		void			set		(unsigned int uid, unsigned int gid) { m_uid=uid; m_gid=gid; }

		bool			is_set () const { return (m_uid!=0) || (m_gid!=0); }

		bool operator== (AuthInfo const & v) const	{ return (m_uid == v.m_uid) && (m_gid == v.m_gid); }
		bool operator!= (AuthInfo const & v) const	{ return (m_uid != v.m_uid) || (m_gid != v.m_gid); }
		bool operator<  (AuthInfo const & v) const
		{
			if (m_uid == v.m_uid) return (m_gid < v.m_gid);
			return (m_uid < v.m_uid);
		}

	private:
		unsigned int	m_uid;
		unsigned int	m_gid;
	};



	/** "RequesterId + RequestNumber + AuthInfo" structure */
	class RequestContext: public UniqueRequestId
	{
	public:
		inline RequestContext (RequesterId requester_id, RequestNumber req_num, AuthInfo const & auth) :
			UniqueRequestId (requester_id, req_num), m_auth(auth)
		{}
		inline RequestContext (UniqueRequestId const & short_context, AuthInfo const & auth) :
			UniqueRequestId (short_context), m_auth(auth)
		{}
		inline RequestContext (RequestContext const & v) :
			UniqueRequestId (v), m_auth(v.m_auth)
		{}
		inline RequestContext ()
		{}

		inline RequestContext const & operator= (RequestContext const & v)	{ UniqueRequestId::operator= (v); m_auth=v.m_auth; return *this; }

		inline AuthInfo const&	get_auth		() const { return m_auth; }

		// "auth info" is not part of the identity
		inline bool operator== (RequestContext const & v) const {	return UniqueRequestId::operator==(v); } 
		inline bool operator!= (RequestContext const & v) const {	return UniqueRequestId::operator!=(v); } 
		inline bool operator<  (RequestContext const & v) const {	return UniqueRequestId::operator< (v); } 

	private:
		AuthInfo		m_auth;
	};




	/** "RequesterId + RequestNumber + RequestHandler*" structure */
	class ResponseContext: public UniqueRequestId
	{
	public:
		inline ResponseContext (RequesterId requester_id, RequestNumber req_num, RequestHandler & req_handler) :
			UniqueRequestId (requester_id, req_num), m_req_handler(&req_handler)
		{}
		inline ResponseContext (UniqueRequestId const & request_id, RequestHandler & req_handler) :
			UniqueRequestId (request_id), m_req_handler(&req_handler)
		{}
		inline ResponseContext (ResponseContext const & v) :
			UniqueRequestId (v), m_req_handler(v.m_req_handler)
		{}
		inline ResponseContext () :
			m_req_handler (0)
		{}

		inline ResponseContext const & operator= (ResponseContext const & v)	{ UniqueRequestId::operator= (v); m_req_handler=v.m_req_handler; return *this; }

		inline RequestHandler & get_request_handler () const { return *m_req_handler; }

		// "req_handler" is not part of the identity
		inline bool operator== (ResponseContext const & v) const {	return UniqueRequestId::operator==(v); } 
		inline bool operator!= (ResponseContext const & v) const {	return UniqueRequestId::operator!=(v); } 
		inline bool operator<  (ResponseContext const & v) const {	return UniqueRequestId::operator< (v); } 

	private:
		RequestHandler * m_req_handler;
	};



	template <class CNTX>
	class Message
	{
	public:
		Message () {}
		Message (CNTX const & context, PDU const & pdu) :
			m_context (context),
			m_pdu (pdu)
		{}

  		Message (Message const & m) :
			m_context	(m.get_context()),
			m_pdu		(m.get_pdu())
		{}

		Message const & operator= (Message const & m)
		{
			m_context	= m.get_context();
			m_pdu		= m.get_pdu();
			return *this;
		}

		CNTX const &	get_context ()	const { return m_context; }
		PDU const &		get_pdu ()		const { return m_pdu; }

		// TODO: add a Timestamp ?

	private:
		CNTX		m_context;
		PDU			m_pdu;
	};


	/// a Request is a client==>server message (where "client" is a user *object*)
	typedef Message<RequestContext> Request;

	/// a Response is a server==>client message (where "client" is a user *object*)
	typedef Message<ResponseContext> Response;

	/// a pair "PDU + RequestNumber" (carries both requests and responses between user *application* and remote server)
	typedef Message<RequestNumber>	RemoteMessage;

}



std::ostream & operator<<(std::ostream & os, FeedOS::UniqueRequestId const & v);


#endif
