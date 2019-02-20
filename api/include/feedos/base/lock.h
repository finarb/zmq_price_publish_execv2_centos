
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_LOCK_H
#define FEEDOS_BASE_LOCK_H

#ifndef FEEDOS_BASE_BASE_H
#  include "base.h"
#endif

namespace FeedOS {

	enum WaitRC	{
		WaitSignaled,
		WaitTimedOut,
		WaitError
	};
}

#  if defined TARGET_PLATFORM_WIN32
#    include "win32/win32_lock.h"
#  else
#    include "unix/unix_lock.h"
#  endif



namespace FeedOS {

	class GenericReadWriteLock
	{
		static void trace_write_write_condition();
		static void trace_read_write_condition();
		static void trace_release_read_access_error();
		static void trace_release_write_access_error();

	public:
		GenericReadWriteLock  () :
			nb_readers (0),
			nb_writers (0),
#if FEEDOS_ENABLE_PARANOID_CHECKS
			m_paranoid_checks_enabled (true)
#else
			m_paranoid_checks_enabled (false)
#endif
		{}

		void acquire_read_access() const
		{
			w.acquire();
			r.acquire();
			if (++nb_readers==1) {
				l.acquire();
			}
			r.release();
			w.release();
		}

		void acquire_write_access() const
		{
			w.acquire();
			l.acquire();
			if (m_paranoid_checks_enabled) {
				++nb_writers;
				if (nb_readers>0) trace_read_write_condition();
				if (nb_writers>1) trace_write_write_condition();
			}
		}

		void release_read_access() const
		{
			r.acquire();
			if (m_paranoid_checks_enabled) {
				if (nb_readers<=0) trace_release_read_access_error();
			}
			if (--nb_readers==0) {
				l.release();
			}
			r.release();
		}

		void release_write_access() const
		{
			if (m_paranoid_checks_enabled) {
				if (nb_writers<=0) trace_release_write_access_error();
				--nb_writers;
			}
			l.release();
			w.release();
		}

	private:
		mutable ExclusiveLock w;
		mutable ExclusiveLock r;
		mutable ExclusiveLock l;
		mutable int nb_readers;
		mutable int nb_writers;
		bool const	m_paranoid_checks_enabled;
	};


	class DummyExclusiveLock
	{
	public:
		inline void acquire ()	const {}
		inline void release ()	const {}
	};

	class DummyReadWriteLock
	{
	public:
		inline void acquire_read_access() const {}		
		inline void acquire_write_access() const {}
		inline void release_read_access() const {}		
		inline void release_write_access() const {}
	};





	/** @name auto_lock_objects */
	//@{
	class rwlock_auto_read
	{
	public:
		inline rwlock_auto_read(ReadWriteLock const & l) : lock(l)	{ lock.acquire_read_access(); }
		inline ~rwlock_auto_read()									{ lock.release_read_access(); }
	private:
		ReadWriteLock const & lock;
	};

	class rwlock_auto_write
	{
	public:
		inline rwlock_auto_write(ReadWriteLock const & l) : lock(l)	{ lock.acquire_write_access(); }
		inline ~rwlock_auto_write()									{ lock.release_write_access(); }
	private:
		ReadWriteLock const & lock;
	};

	class exlock_auto
	{
	public:
		inline exlock_auto(ExclusiveLock const & l) : lock(l)	{ lock.acquire(); }
		inline ~exlock_auto()									{ lock.release(); }
	private:
		ExclusiveLock const & lock;
	};

	class condlock_auto
	{
	public:
		inline condlock_auto(ConditionalVariable const & l) : lock(l)	{ lock.acquire(); }
		inline ~condlock_auto()											{ lock.release(); }
	private:
		ConditionalVariable const & lock;
	};

#	define SCOPE_AUTO_READ_LOCK(name,l)	FeedOS::rwlock_auto_read	lock_##name(l);
#	define SCOPE_AUTO_WRITE_LOCK(name,l)FeedOS::rwlock_auto_write	lock_##name(l);
#	define SCOPE_AUTO_LOCK(name,l)		FeedOS::exlock_auto			lock_##name(l);
#	define SCOPE_AUTO_CONDLOCK(name,l)	FeedOS::condlock_auto		lock_##name(l);

	//@}

	class LockedBool
	{
	public:
		explicit LockedBool(bool v = false) { m_Data = v ? 1 : 0; }
		LockedBool(LockedBool const & l) { m_Data = (l.get() != 0) ? 1 : 0; }

		bool get() const { return m_Data.get() != 0; }
		void set(bool v = true) { m_Data = v ? 1 : 0; }
		void reset() { set(false); }

		// We do NOT like implicit casts.
		//operator bool() const { return get(); }
		//bool operator!() const { return !get(); }

		LockedBool & operator= (bool v) { set(v); return *this; }

	private:
		LockedCounter m_Data;
	};

	/**
	 * An object allowing to sleep and still be prematurely woken if necessary.
	 */
	class InterruptibleSleep
	{
	public:
		enum SleepReturnCode
			{
				SleepError    = -1,
				PrematureWake =  0,
				NormalWake    =  1,
				SkippedSleep  =  2
			};

		enum WakeReturnCode
			{
				SleeperWake   =  0,
				SkippedWake   =  1
			};

	public:
		/**
		 * Create a new interruptible sleep object.
		 */
		InterruptibleSleep();

		/**
		 * Put the caller thread to sleep for a specific number of milliseconds.
		 * @param milliseconds The number of milliseconds for which the thread should sleep.
		 * @return A return code describing the outcome of the sleep.
		 */
		SleepReturnCode sleep(unsigned int milliseconds);

		/**
		 * Signal the thread sleeping on the interruptible sleep object to prematurely wakeup.
		 * @return A return code describing the outcome of the wake.
		 */
		WakeReturnCode signal();

	private:
		ConditionalVariable m_cond;
		bool m_sleeping;
		bool m_signaled;
	};
}

#endif
