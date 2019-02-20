
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_DATE_H
#define FEEDOS_BASE_DATE_H

#ifndef FEEDOS_BASE_BASE_H
#  include "base.h"
#endif

#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <string>
//#include <stdio.h>
#include <iostream>
#include <sstream>

#ifdef TARGET_PLATFORM_WIN32
#	include <Windows.h>
#else
#	include <sys/time.h>
#	include <time.h>
#endif

namespace FeedOS {

	class Day
	{
	public:
		Day (int year, int month, int day) : m_year(year), m_month (month), m_day (day)	{}

		int get_year()	const  {return m_year;}
		int get_month()	const  {return m_month;}
		int get_day()	const  {return m_day;}

	private:
		int m_year;
		int m_month;
		int m_day;
	};



#define FEEDOS_DATE_COMPATIBILITY_ACCESSORS		1	// TODO remove this some time

	class Timestamp
	{
	public:
		inline Timestamp ()					: m_sec(0),			m_sub_microsec(0) {}
		inline Timestamp (Timestamp const & v)	: m_sec(v.m_sec),	m_sub_microsec(v.m_sub_microsec) {}
		inline Timestamp (Day const & d, int hour=0, int minute=0, int sec=0, int millisec=0)
		{
			set_YMDHMSmu(d.get_year(),d.get_month(),d.get_day(),hour,minute,sec,millisec);
		}
		inline Timestamp (time_t sec, unsigned int millisec) : m_sec (sec), m_sub_microsec(millisec*1000) {}
		inline Timestamp (std::string const & str) : m_sec (0), m_sub_microsec (0) { set_from_string(str); }

		inline Timestamp const & operator= (Timestamp const & v)
		{
			m_sec=v.m_sec;
			m_sub_microsec=v.m_sub_microsec;
			return *this;
		}
		
		inline bool operator== (Timestamp const &	v) const
		{
			return (m_sec==v.m_sec) && (m_sub_microsec==v.m_sub_microsec);
		}

		inline bool operator!= (Timestamp const &	v) const { return !operator==(v); }

		inline bool operator<  (Timestamp const &	v) const
		{
			if (m_sec<v.m_sec)	return true;
			if (m_sec>v.m_sec)	return false;
			return (m_sub_microsec<v.m_sub_microsec);
		}

		inline bool operator>  (Timestamp const &	v) const
		{
			if (m_sec>v.m_sec)	return true;
			if (m_sec<v.m_sec)	return false;
			return (m_sub_microsec>v.m_sub_microsec);
		}

		inline bool operator<= (Timestamp const &	v) const	{ return (*this == v) || (*this < v); }
		inline bool operator>= (Timestamp const &	v) const	{ return (*this == v) || (*this > v); }


		/** @name set_string_flavour
		  * expects "YYYY-MM-DD HH:MM:SS:mmm.uuu" or "null" or "now"
		  * @nb "HH:MM:SS", ":mmm" and ".uuu" are optional. Defaults to 0
		  */
		//@{

		/** return true if parsing was successfull */
		bool set_from_string (std::string const & str);
		
		bool set_from_stringYYYYMMDD (std::string const & str);

		inline void operator << (std::string const & s)				{ set_from_string (s); }

		inline Timestamp const & operator= (std::string const & s)	{ set_from_string (s); return *this; }

		//@}


		

		/** @name accessors
		*
		* - year   [1900..2027]
		* - month  [1..12]
		* - day    [1..31]
		* - hour   [0..23]
		* - minute [0..59]
		* - second [0..59]
		* - milli  [0..999]
		* - micro  [0..999]
		*
		* - weekday [0..6]   0=sunday
		*/
		//@{

		inline void set_YMD (int year, int month, int day)
		{
			m_sec = build_time_t (year, month, day, 0, 0, 0);
			m_sub_microsec = 0;
		}

		inline void set_YMDHMSmu (int year, int month, int day, int hour=0, int minute=0, int sec=0, int millisec=0, int microsec=0)
		{
			m_sec = build_time_t (year, month, day, hour, minute, sec);
			m_sub_microsec = millisec * 1000 + microsec;
		}

		inline void set_YMDHMSm (int year, int month, int day, int hour=0, int minute=0, int sec=0, int millisec=0)
		{
			m_sec = build_time_t (year, month, day, hour, minute, sec);
			internal_set_millisec (millisec);
		}
#if FEEDOS_DATE_COMPATIBILITY_ACCESSORS
		inline void set (int year, int month, int day, int hour=0, int minute=0, int sec=0, int millisec=0)
		{
			return set_YMDHMSm (year, month, day, hour, minute, sec, millisec);
		}
#endif

		inline void set_YMDHMS (int year, int month, int day, int hour=0, int minute=0, int sec=0)
		{
			m_sec = build_time_t (year, month, day, hour, minute, sec);
			m_sub_microsec = 0;
		}


		typedef enum {
			Weekday_Sunday,
			Weekday_Monday,
			Weekday_Tuesday,
			Weekday_Wednesday,
			Weekday_Thursday,
			Weekday_Friday,
			Weekday_Saturday
		} Weekday;

		static char const * weekday2str (Weekday v);
		static bool str2weekday (char const * s, Weekday & v);

		/// get the weekday
		inline Weekday weekday () const
		{
			int year,month,day,hour,minute,sec;
			Weekday weekday;
			split_time_t (m_sec, year, month, day, hour, minute, sec, weekday);
			return weekday;
		}

		/// get, short flavour: year/mon/day/h/m/s/weekday
		inline void get_YMDHMSmW (int & year, int & month, int & day, int & hour, int & minute, int & sec, int & millisec, Weekday & weekday) const
		{
			split_time_t (m_sec, year, month, day, hour, minute, sec, weekday);
			millisec=internal_get_millisec();
		}

		/// get, short flavour: year/mon/day/h/m/s/milli/micro
		inline void get_YMDHMSmu (int & year, int & month, int & day, int & hour, int & minute, int & sec, int & millisec, int & microsec) const
		{
			Weekday weekday;
			split_time_t (m_sec, year, month, day, hour, minute, sec, weekday);
			millisec=m_sub_microsec/1000;
			microsec=m_sub_microsec%1000;
		}

		/// get, short flavour: year/mon/day/h/m/s/milli
		inline void get_YMDHMSm (int & year, int & month, int & day, int & hour, int & minute, int & sec, int & millisec) const
		{
			Weekday weekday;
			split_time_t (m_sec, year, month, day, hour, minute, sec, weekday);
			millisec=internal_get_millisec();
		}
#if FEEDOS_DATE_COMPATIBILITY_ACCESSORS
		inline void get (int & year, int & month, int & day, int & hour, int & minute, int & sec, int & millisec) const
		{
			return get_YMDHMSm (year, month, day, hour, minute, sec, millisec);
		}
#endif
		
		/// get, short flavour: year/mon/day/h/m/s
		inline void get_YMDHMS (int & year, int & month, int & day, int & hour, int & minute, int & sec) const
		{
			Weekday weekday;
			split_time_t (m_sec, year, month, day, hour, minute, sec, weekday);
		}
#if FEEDOS_DATE_COMPATIBILITY_ACCESSORS
		inline void get (int & year, int & month, int & day, int & hour, int & minute, int & sec) const
		{
			return get_YMDHMS (year, month, day, hour, minute, sec);
		}
#endif
		
		/// get, short flavour: year/mon/day
		inline void get_YMD (int & year, int & month, int & day) const
		{
			int hour, minute, sec;
			Weekday weekday;
			split_time_t (m_sec, year, month, day, hour, minute, sec, weekday);
		}
#if FEEDOS_DATE_COMPATIBILITY_ACCESSORS
		inline void get (int & year, int & month, int & day) const
		{
			return get_YMD (year, month, day);
		}
#endif
		
		/// get "internal" flavour
		inline void get_timet (uint32 & sec, uint16 & millisec) const
		{
			sec=(uint32)m_sec;
			millisec = static_cast<uint16> (internal_get_millisec());
		}

		inline void get_timet (unsigned int & sec, unsigned int & millisec) const
		{
			sec=(unsigned int)m_sec;
			millisec=internal_get_millisec();
		}

		inline void get_timet (unsigned int & sec, unsigned int & millisec, unsigned int & microsec) const
		{
			sec=(unsigned int)m_sec;
			millisec=m_sub_microsec/1000;
			microsec=m_sub_microsec%1000;
		}

		inline void get_Smu(uint32 & sec, uint16 & millisec, uint16 & microsec) const
		{
			sec = static_cast<uint32>(m_sec);
			millisec = static_cast<uint16>(m_sub_microsec / 1000);
			microsec = static_cast<uint16>(m_sub_microsec % 1000);
		}

		inline void get_sec_microsec(time_t & sec, unsigned int & microsec) const
		{
			sec = m_sec;
			microsec = m_sub_microsec;
		}

		inline uint64 get_as_micro_sec() const
		{
			return static_cast<uint64>(m_sec) * 1000000 + m_sub_microsec;
		}

		/// set "internal" flavour
		/*
		inline void set (uint32 sec, uint16 millisec)
		{
			m_sec=(time_t)sec; m_millisec=millisec;
		}
		*/
		inline void set_timet (time_t sec, unsigned int millisec)
		{
			m_sec=sec;
			internal_set_millisec (millisec);
		}
#if FEEDOS_DATE_COMPATIBILITY_ACCESSORS
		/// set "internal" flavour
		inline void set (uint32 sec, uint16 millisec)
		{
			set_timet ((time_t)sec, millisec);
		}
#endif

		inline void set_timet (time_t sec, unsigned int millisec, unsigned int microsec)
		{
			m_sec=sec;
			m_sub_microsec = millisec * 1000 + microsec;
		}

		/// get "internal" TIME_T flavour
		inline time_t get_timet () const { return m_sec; }

		/// set "internal" TIME_T flavour
		inline void set_timet (time_t sec) { m_sec=sec; m_sub_microsec=0; }
		//@}

		inline void set_sec_microsec(time_t sec, unsigned int microsec)
		{
			m_sec = sec;
			m_sub_microsec = microsec;
		}

		inline void set_from_micro_sec (uint64 as_micro_sec)
		{
			m_sec = as_micro_sec / 1000000;
			m_sub_microsec = static_cast<uint32>(as_micro_sec % 1000000);
		}

		/// return the current UTC time
		inline static Timestamp now_utc()
		{
			Timestamp now; now.set_to_now_utc();
			return now;
		}

#ifdef TARGET_PLATFORM_WIN32
		static bool isMicroSecPrecisionAvailable()
		{
			return getMicroSecTimeFunction() != (MicroSecTimeFunction)NULL;
		}

		static ULONGLONG getNbNanoSecondCentsSinceEpoch()
		{
			static MicroSecTimeFunction timeFunc = getMicroSecTimeFunction();
			static ULONGLONG const s_epoch = 116444736000000000LL;

			FILETIME systemTime;
			timeFunc(&systemTime);

			ULARGE_INTEGER systemTimeValue;
			systemTimeValue.HighPart = systemTime.dwHighDateTime;
			systemTimeValue.LowPart = systemTime.dwLowDateTime;

			return systemTimeValue.QuadPart - s_epoch;
		}
#endif
		/// reset to "now" value (UTC)
		inline void set_to_now_utc ()
		{
#ifdef TARGET_PLATFORM_WIN32
			static bool const computeMicroSecTs = isMicroSecPrecisionAvailable();
			if (computeMicroSecTs)
			{
				ULONGLONG const nb_100_nano_since_epoch = getNbNanoSecondCentsSinceEpoch();
	
				m_sec = (time_t)(nb_100_nano_since_epoch / 10000000) ;
				m_sub_microsec = (unsigned int)( (nb_100_nano_since_epoch % 10000000) / 10 );
			}
			else
			{
				struct timeb ts; ftime(&ts); set_timet((unsigned int)ts.time,(unsigned int)ts.millitm);
			}
#else
			struct timeval n;   
			::gettimeofday(&n, NULL);
			m_sec			=n.tv_sec;
			m_sub_microsec	=static_cast<unsigned int> (n.tv_usec);
#endif
		}


		/// return a "null" date (beginning of time)
		inline static Timestamp const & null() { return s_null; }

		/// return an "unknown" date
		inline static Timestamp const & unknown() { return s_unknown; }

		/// return true if the string is a valid formated date (format: YYYY-MM-DD HH:MM:SS)
		static bool is_valid(std::string const &);


		/// return true if the instance is null (i.e. beginning-of-time)
		/** the instance has been built using default constructor, or assigned using Timestamp::null()
		 */
		inline bool is_null () const { return (m_sec==0) && (m_sub_microsec==0); }


		/// reset to "null" value
		inline void set_to_null () { set_timet(0,0); }

		
		/// return the date in string format
		/** "null" or "YYYY-MM-DD HH:MM:SS:mmm" (where "HH:MM:SS" and "mmm" are optional, i.e not printed if 0) */
		void dump (std::ostream & os) const;
		std::string str () const;

		/// return the date in [fixed] string format
		/** "null" or "YYYY-MM-DD HH:MM:SS:mmm" */
		int str_full23 (char buffer[24]) const;
		std::string str_full () const;

		/// return the date in [fixed] string format
		/** "null" or "YYYY-MM-DD HH:MM:SS:mmm.uuu" */
		std::string str_full_force_microsec () const;

		/// return the date in string format
		/** "null" or "YYYY-MM-DD HH:MM:SS:mmm[.uuu]" */
		std::string str_full_allow_microsec () const;
		void dump_full_allow_microsec (std::ostream & s) const;

		/// return the date in [fixed] string format
		/** "null" or "YYYY-MM-DD HH:MM:SS" */
		std::string str_full_no_millisec () const;

		/// return the Timestamp in [fixed,compact] string format
		/** "null" or "YYYYMMDDHHMMSSmmm" */
		std::string str_compact () const;
		int str_compact18 (char buffer[18]) const;

		/// return the Timestamp in [fixed] string format
		/** "null" or "YYYYMMDDHHMMSS" */
		std::string str_compact_no_millisec () const;

		/// return true if the TIME part is "null" (set to 00:00:00)
		bool has_null_time () const { return (0==(m_sec%(24*60*60))) && (0==m_sub_microsec); }

		/// set the hour/minute/second/millisec to 0 (midnight)
		inline void reset_time() { m_sub_microsec=0; m_sec /= 24*60*60; m_sec *= 24*60*60; }

		/// set milliseconds to 0
		inline void reset_millisec() { m_sub_microsec=0; }

		/// set microseconds to 0
		inline void reset_microsec() { m_sub_microsec-=(m_sub_microsec%1000); }

		/** @name increment_decrement_methods */
		//@{
		inline void add_microsec (int64 microsec)
		{
			if (0!=microsec) {
				int64 new_microsec = m_sub_microsec + microsec;
				int seconds = static_cast<int>(new_microsec/(1000*1000));
				int remaining_microsec = static_cast<int>(new_microsec%(1000*1000));
				if (new_microsec>0) {
					add_seconds (seconds);
					m_sub_microsec = remaining_microsec;
				} else {
					if (remaining_microsec == 0) {
						add_seconds (seconds);
						m_sub_microsec = 0;
					} else {
						add_seconds (seconds-1);
						m_sub_microsec = 1000*1000 + remaining_microsec;
					}
				}
			}
		}

		inline void add_millisec (int millisec)
		{
			add_microsec (1000*static_cast<int64>(millisec));
		}

		inline void add_seconds(int seconds)	{ m_sec += seconds; }
		inline void add_minutes(int minutes)	{ m_sec += minutes*60; }
		inline void add_hours	(int hours)		{ m_sec += hours*60*60; }
		inline void add_days	(int days)		{ m_sec += days*60*60*24; }

		inline void set_to_beginning_of_month	()
		{
			int year,  month,  day;
			get_YMD (year,  month,  day);
			set_YMD(year,month,1);
		}
		inline void set_to_beginning_of_next_month	()
		{
			int year,  month,  day;
			get_YMD (year,  month,  day);
			if (++month==13)
			{
				++year;
				month=1;
			}
			set_YMD(year,month,1);
		}
		inline void set_to_end_of_month	()
		{
			set_to_beginning_of_next_month();
			add_seconds (-1);
		}
		//@}


		/** @name compare_dates (positive result if the given date is oldest) */
		//@{
		inline int64 diff_microsec(Timestamp const & v) const	{ return ((static_cast<int64>(m_sec) - static_cast<int64>(v.m_sec)) * 1000 * 1000 + ( static_cast<int>(m_sub_microsec) - static_cast<int>(v.m_sub_microsec)) ); }
		inline int64 diff_millisec(Timestamp const & v) const	{ return (static_cast<int64>(m_sec) - static_cast<int64>(v.m_sec)) * 1000 + ( internal_get_millisec() - v.internal_get_millisec()); }
		inline int diff_seconds (Timestamp const & v) const	{ return (((int)m_sec - (int)v.m_sec)); }
		inline int diff_minutes (Timestamp const & v) const	{ return diff_seconds(v) / 60; }
		inline int diff_hours	(Timestamp const & v) const	{ return diff_minutes(v) / 60; }
		inline int diff_days	(Timestamp const & v) const	{ return diff_hours(v) / 24; }

		inline double fdiff_microsec(Timestamp const & v) const	{ return static_cast<double>(diff_microsec(v)); }
		inline double fdiff_millisec(Timestamp const & v) const	{ return fdiff_microsec(v) / 1000.; }
		inline double fdiff_seconds (Timestamp const & v) const	{ return ((double)m_sec + ((double)internal_get_millisec())/1000.) - ((double)v.m_sec + ((double)v.internal_get_millisec())/1000.); }
		inline double fdiff_minutes (Timestamp const & v) const	{ return fdiff_seconds(v) / 60.; }
		inline double fdiff_hours	(Timestamp const & v) const	{ return fdiff_minutes(v) / 60.; }
		inline double fdiff_days	(Timestamp const & v) const	{ return fdiff_hours(v) / 24.; }
		inline double fdiff_years	(Timestamp const & v) const	{ return fdiff_days(v) / 365.; }
		//@}

		/// build a number of seconds since 1970 from "struct tm"
		static time_t MKTIME (struct tm *t);

		static void pretty_print_nb_seconds (std::ostream & s, int nb_sec);

	private:
		time_t			m_sec;			// number of seconds since 1970-01-01
		unsigned int	m_sub_microsec;	// 0..999999 microseconds

		inline int		internal_get_millisec() const { return m_sub_microsec/1000; }
		inline void		internal_set_millisec(int m) { m_sub_microsec=m*1000; }

		static void check_values (int year, int month, int day, int hour, int minute, int sec);

		/// build a number of seconds since 1970 from y/m/d/h/m/s
		inline static time_t build_time_t (int year, int month, int day, int hour=0, int minute=0, int sec=0)
		{
#ifdef _DEBUG
			check_values (year, month, day, hour, minute, sec);
#endif
			struct tm t;
			t.tm_year=year-1900;
			t.tm_mon=month-1;
			t.tm_mday=day;
			t.tm_hour=hour;
			t.tm_min=minute;
			t.tm_sec=sec;
			return MKTIME(&t);
		}

#ifdef TARGET_PLATFORM_WIN32
		typedef void (WINAPI *MicroSecTimeFunction)(LPFILETIME lpSystemTimeAsFileTime);
		static MicroSecTimeFunction getMicroSecTimeFunction()
		{
			return (MicroSecTimeFunction)GetProcAddress(GetModuleHandle(TEXT("Kernel32.dll")), "GetSystemTimePreciseAsFileTime");
		}
#endif

		/// split a number of seconds since 1970 into y/m/d/h/m/s
		static bool split_time_t (time_t tsec, int & year, int & month, int & day, int & hour, int & minute, int & sec, Weekday & weekday);

		/// global "null" object
		static Timestamp s_null;

		/// global "unknown" object
		static Timestamp const s_unknown;

		/// global "null" struct tm
		static struct tm s_null_struct_tm;
	};


	// TODO improve this (subclass, add/move specific methods)
	typedef Timestamp UTCTimestamp;
	typedef Timestamp LocalTimestamp;


}



/// stream output operator
inline std::ostream & operator<< (std::ostream &os, FeedOS::Timestamp const & v)
{
	v.dump (os);
	return os;
}


/// stream input operator
inline std::istream & operator>> (std::istream &is, FeedOS::Timestamp & v);



#endif
