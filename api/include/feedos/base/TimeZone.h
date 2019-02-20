
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_TIMEZONE_H
#define FEEDOS_BASE_TIMEZONE_H

#ifndef FEEDOS_BASE_SMART_PTR_H
#	include "smart_ptr.h"
#endif

#ifndef FEEDOS_BASE_DATE_H
#	include "date.h"
#endif

#include <time.h>
#include <string>
#include <vector>
#include <ostream>


namespace FeedOS {

/**
 * TimeZone
 *
 */
class TimeZone
{
public:
	/// TimeType
	enum TimeType
	{
		TimeType_UTC,		///< Coordinated Universal Time
		TimeType_WallClock,	///< Wall Clock Time, local time with Daylight Saving Time
		TimeType_STD		///< Standard Time, local time without Daylight Saving Time
	};

	/// Period
	class Period
	{
	public:
		/// ctor
		Period(	TimeType time_type,
				time_t const & begin_time,
				time_t const & end_time,
				bool is_dst,
				int offset_from_utc_to_wall_clock,
				int offset_from_utc_to_std)
		: m_TimeType(time_type)
		, m_BeginTime(begin_time)
		, m_EndTime(end_time)
		, m_IsDST(is_dst)
		, m_OffsetFromUTCToWallClock(offset_from_utc_to_wall_clock)
		, m_OffsetFromUTCToSTD(offset_from_utc_to_std)
		{
		}

		/// copy ctor
		Period(Period const & other)
		{
			operator=(other);
		}

		/// copy operator
		Period const & operator=(Period const & other)
		{
			m_TimeType					= other.m_TimeType;
			m_BeginTime					= other.m_BeginTime;
			m_EndTime					= other.m_EndTime;
			m_IsDST						= other.m_IsDST;
			m_OffsetFromUTCToWallClock	= other.m_OffsetFromUTCToWallClock;
			m_OffsetFromUTCToSTD		= other.m_OffsetFromUTCToSTD;

			return *this;
		}

		/// check if the period contains the given time (with the same time type)
		bool	contains(time_t const & time) const;

		time_t const &	getBeginTime() const				{ return m_BeginTime; }
		time_t const &	getEndTime() const					{ return m_EndTime; }
		TimeType		getTimeType() const					{ return m_TimeType; }
		bool			isDST() const						{ return m_IsDST; }
		int				getOffsetFromUTCToWallClock() const	{ return m_OffsetFromUTCToWallClock; }
		int				getOffsetFromUTCToSTD() const		{ return m_OffsetFromUTCToSTD; }

		/// for debug
		std::string	asString() const;

	private:
		TimeType	m_TimeType;
		time_t		m_BeginTime;
		time_t		m_EndTime;
		bool		m_IsDST;
		int			m_OffsetFromUTCToWallClock;
		int			m_OffsetFromUTCToSTD;
	};

public:
	/// ctor
	TimeZone();
	/// dtor
	~TimeZone();

	/// load the time zone
	bool	loadTimeZone(char const * tz_buffer, unsigned int tz_buffer_len);

	/// convert an UTC time to a local time (wall clock)
	/// WARNING: it might return a null timestamp if the conversion is not possible
	Timestamp	convertUTCToLocalTime(Timestamp const & utc_time) const;
	/// convert a local time (wall clock) to an UTC time
	/// WARNING: it might return a null timestamp if the conversion is not possible or ambiguous
	Timestamp	convertLocalTimeToUTC(Timestamp const & wall_clock_time) const;
	Timestamp	convertLocalTimeToUTC(Timestamp const & wall_clock_time, bool in_dst_period) const;
	/// convert a local time (wall clock) to an UTC time
	/// WARNING: this method should never return a null timestamp if wall_clock_time is not null, but the result might be wrong
	Timestamp	convertLocalTimeToUTC_BestEffort(Timestamp const & wall_clock_time, bool in_dst_period = true) const;

	/// get the matching periods
	void	getMatchingPeriods(time_t time, TimeType time_type, std::vector<Period> & matching_periods) const;
	/// get the matching and the overlapped periods (only for wall clock time type)
	void	getMatchingAndOverlappedPeriods(time_t wall_clock_time, std::vector<Period> & matching_and_overlapped_periods) const;
	/// get all periods
	void	getAllPeriods(TimeType time_type, std::vector<Period> & all_periods) const;

	/// for debug
	void	dump(std::ostream & os);

	/// get the name of the given time type
	static std::string const &	getTimeTypeName(TimeType time_type);

	/// get the default offset from UTC to wall clock
	bool	getDefaultOffsetFromUTCToWallClock(int & offset_from_utc_to_wall_clock) const
	{
		if (m_DefaultTimeTypeInfo != NULL)
		{
			offset_from_utc_to_wall_clock = m_DefaultTimeTypeInfo->getOffsetFromUTCToWallClock();
			return true;
		}
		return false;
	}

private:
	/**
	 * TimeTypeInfo
	 *
	 */
	class TimeTypeInfo
	{
	public:
		/// default ctor
		TimeTypeInfo()	{}
		/// ctor
		TimeTypeInfo(	int		offset_from_utc_to_wall_clock,
						bool	is_dst,
						bool	transition_is_std,
						bool	transition_is_utc,
						char const * abbreviation)
		: m_OffsetFromUTCToWallClock(offset_from_utc_to_wall_clock)
		, m_IsDST(is_dst)
		, m_TransitionIsSTD(transition_is_std)
		, m_TransitionIsUTC(transition_is_utc)
		, m_Abbreviation(abbreviation)
		{
		}

		int		getOffsetFromUTCToWallClock() const	{ return m_OffsetFromUTCToWallClock; }
		bool	getIsDST() const					{ return m_IsDST; }
		bool	getTransitionIsSTD() const			{ return m_TransitionIsSTD; }
		bool	getTransitionIsUTC() const			{ return m_TransitionIsUTC; }
		char const *	getAbbreviation() const		{ return m_Abbreviation; }

		/// for debug
		std::string	asString() const;

	private:
		/// offset from UTC to wall clock in seconds
		int		m_OffsetFromUTCToWallClock;
		/// true if Daylight Saving Time
		bool	m_IsDST;
		/// true if transition is std time
		bool	m_TransitionIsSTD;
		/// true if transition is UTC
		bool	m_TransitionIsUTC;
		/// abbreviation
		char const *	m_Abbreviation;
	};

	/**
	 * LeapSecondInfo
	 *
	 */
	class LeapSecondInfo
	{
	public:
		/// default ctor
		LeapSecondInfo()	{}
		/// ctor
		LeapSecondInfo(time_t transition_time, int correction)
		: m_TransitionTime(transition_time)
		, m_Correction(correction)
		{
		}

		time_t const &	getTransitionTime() const	{ return m_TransitionTime; }
		int				getCorrection() const		{ return m_Correction; }

		/// for debug
		std::string	asString() const;

	private:
		/// transition time
		time_t	m_TransitionTime;
		/// correction to apply
		int		m_Correction;
	};

	/**
	 * Transition
	 *
	 */
	class Transition
	{
	public:
		/// default ctor
		Transition()	{}
		/// ctor
		Transition(time_t transition_utc_time, int offset_from_utc_to_std, TimeTypeInfo const * time_type_info)
		: m_TransitionUTCTime(transition_utc_time)
		, m_OffsetFromUTCToSTD(offset_from_utc_to_std)
		, m_TimeTypeInfo(time_type_info)
		{
		}

		time_t const &			getTransitionUTCTime() const	{ return m_TransitionUTCTime; }
		int						getOffsetFromUTCToSTD() const	{ return m_OffsetFromUTCToSTD; }
		TimeTypeInfo const &	getTimeTypeInfo() const			{ return *m_TimeTypeInfo; }

		/// for debug
		std::string	asString() const;

	private:
		time_t					m_TransitionUTCTime;
		int						m_OffsetFromUTCToSTD;
		TimeTypeInfo const *	m_TimeTypeInfo;
	};

private:
	/// clear the time zone
	void	clear();

	/// get a transition time converted to the given time type
	time_t	getTransitionTime(Transition const & transition, TimeType time_type) const;
	time_t	getTransitionTime(time_t const & transition_utc_time, Transition const & transition, TimeType time_type) const;

	// TODO?
	//int	getOffsetWithLeapCorrection(time_t time, TimeTypeInfo const & time_type_info) const;

private:
	std::vector<Transition>		m_Transitions;
	std::string					m_Abbreviations;
	std::vector<TimeTypeInfo>	m_TimeTypeInfos;
	std::vector<LeapSecondInfo>	m_LeapSecondInfos;
	TimeTypeInfo const *		m_DefaultTimeTypeInfo;
};
typedef FeedOS::smart_ptr<TimeZone>	TimeZone_ptr;

}

#endif
