
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_ERRORS_H
#define FEEDOS_COMM_ERRORS_H

#define FEEDOS_AGRESSIVE_RETURN_CODE	0

#include <iostream>

namespace FeedOS {
	
	enum ReturnCode_enum {
		RC_OK								,	// success
		RC_ERROR							,	// general error
		RC_NOT_AVAILABLE					,	// feature is not available
		RC_NOT_AUTHORISED					,	// wrong permission
		RC_NORMAL_DISCONNECT				,	// disconnected at user request
		RC_DISCONNECTED						,	// disconnected (network problem)
		RC_TIMEOUT							,	// timeout
		RC_SERVER_BUSY						,	// server is busy
		RC_SERVER_ERROR						,	// general server error
		RC_CLIENT_VERSION_TOO_OLD			,	// API is too old
		RC_CLIENT_VERSION_TOO_RECENT		,	// API is too recent (server is too old)
		RC_INVALID_INSTRUMENT_CODE			,	// an invalid instrument code was provided
		RC_INVALID_MARKET_ID				,	// an invalid market id was provided
		RC_INVALID_REFERENTIAL_TAG			,	// an invalid referential tag was provided
		RC_INVALID_QUOTATION_TAG			,	// an invalid quotation tag was provided
		RC_INVALID_ARGUMENT					,	// an invalid argument was provided
		RC_MISSING_ARGUMENT					,	// a mandatory argument was not provided
		RC_UA_INVALID_USER_ID				,	// invalid user id (maybe it is already in use)
		RC_UA_INVALID_GROUP_ID				,	// invalid or unknown group id
		RC_UA_INVALID_NAME_OR_PASSWORD		,	// authentication failed
		RC_UA_TOO_MANY_CONNECTIONS			,	// maximum number of simultaneous connections reached
		RC_UA_USER_EXPIRED					,	// user account expired
		RC_IN_PROGRESS						,	// requested operation cannot be completed immediately
		RC_DATA_NOT_AVAILABLE				,   // resource is not available
		rc_max_value
	};

#if FEEDOS_AGRESSIVE_RETURN_CODE
	// aggressive version (do not allow BOOL expressions )
	class ReturnCode
	{
	public:
		inline ReturnCode () : m_rc(RC_OK) {}
		inline ReturnCode (uint16 rc) : m_rc((enum ReturnCode_enum)rc) {}
		inline ReturnCode (unsigned int rc) : m_rc((enum ReturnCode_enum)rc) {}
		inline ReturnCode (enum ReturnCode_enum const & rc) : m_rc(rc) {}
		inline ReturnCode (ReturnCode const & other) : m_rc (other.m_rc) {}
		inline ReturnCode const & operator= (enum ReturnCode_enum const & rc) { m_rc = rc; return *this; }
		inline ReturnCode const & operator= (ReturnCode const & other) { m_rc = other.m_rc; return *this; }
		inline bool operator== (ReturnCode const & b) const { return m_rc == b.m_rc; }
		inline bool operator!= (ReturnCode const & b) const { return m_rc != b.m_rc; }
		unsigned int numeric_value() const { return m_rc; }
	private:
		ReturnCode (bool v) : m_rc(v?RC_OK:RC_ERROR) {}	// TODO: make this public ?
		enum ReturnCode_enum m_rc;
	};

	inline unsigned int	return_code_to_numeric	(ReturnCode rc)		{ return (ReturnCode_enum) rc.numeric_value(); }
#else

	// simple version
	typedef enum ReturnCode_enum ReturnCode;

	inline unsigned int	return_code_to_numeric	(ReturnCode rc)		{ return (ReturnCode_enum) rc; }
#endif

	inline ReturnCode	numeric_to_return_code	(unsigned int rc)	{ return (ReturnCode_enum) rc; }

	

	/** Convert a return code into a printable string
	  * @param value Numeric return code
	  * @return the string version of the given ReturnCode
	  */
	char const * error_string (ReturnCode value);


	/** Merge several return codes into one "global" value
	  * @return a compound value for all merge()d return codes
	  */
	class CompoundReturnCode
	{
	public:
		CompoundReturnCode () : m_global_rc (RC_OK) {}
		CompoundReturnCode (CompoundReturnCode const & other) : m_global_rc (other.m_global_rc) {}
		CompoundReturnCode const & operator= (CompoundReturnCode const & other)
		{
			m_global_rc = other.m_global_rc;
			return *this;
		}

		void merge (ReturnCode const & sub_rc)
		{
			if (sub_rc!=RC_OK) {
				if (m_global_rc==RC_OK)
					m_global_rc=sub_rc;			// first error
				else if (m_global_rc!=sub_rc)
					m_global_rc=RC_ERROR;		// at least 2 errors different, use generic error code
			}
		}

		operator ReturnCode () const { return m_global_rc; }
	private:
		ReturnCode m_global_rc;
	};

};


inline std::ostream & operator << (std::ostream & s, FeedOS::ReturnCode const & v) { return s << FeedOS::error_string(v); }
inline std::ostream & operator << (std::ostream & s, FeedOS::CompoundReturnCode const & v) { return s << FeedOS::error_string(v); }

#if FEEDOS_AGRESSIVE_RETURN_CODE

inline bool operator== (FeedOS::ReturnCode const & a, enum FeedOS::ReturnCode_enum const & b) { return a.numeric_value() == (unsigned int)b; }
inline bool operator!= (FeedOS::ReturnCode const & a, enum FeedOS::ReturnCode_enum const & b) { return a.numeric_value() != (unsigned int)b; }
inline bool operator== (enum FeedOS::ReturnCode_enum const & a, FeedOS::ReturnCode const & b) { return (unsigned int)a == b.numeric_value(); }
inline bool operator!= (enum FeedOS::ReturnCode_enum const & a, FeedOS::ReturnCode const & b) { return (unsigned int)a != b.numeric_value(); }

inline bool operator== (unsigned int a, FeedOS::ReturnCode const & b) { return a == b.numeric_value(); }
inline bool operator!= (unsigned int a, FeedOS::ReturnCode const & b) { return a != b.numeric_value(); }
inline bool operator== (FeedOS::ReturnCode const & a, unsigned int b) { return a.numeric_value() == b; }
inline bool operator!= (FeedOS::ReturnCode const & a, unsigned int b) { return a.numeric_value() != b; }

#endif



#endif

