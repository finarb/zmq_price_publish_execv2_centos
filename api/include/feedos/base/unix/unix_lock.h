
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2003-2005 **/
/** Author: Denery Fenouil         **/
/************************************/

/** @file
 *
 *  Unix implementation
 *
 */


#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <errno.h>

/*
#ifndef PTHREAD_MUTEX_RECURSIVE
#	define PTHREAD_MUTEX_RECURSIVE	PTHREAD_MUTEX_RECURSIVE_NP
#endif
*/

 
namespace FeedOS {

//	extern pthread_mutexattr_t  g_lockinterface_mutexattr;
//	extern pthread_rwlockattr_t g_lockinterface_rwlockattr;
//	void init_lock_interface ();

	/// an exclusive lock
	class ExclusiveLock
	{
		ExclusiveLock  (ExclusiveLock const &)  {}
		void operator= (ExclusiveLock const &)  {}
	public:
		ExclusiveLock ();
		~ExclusiveLock ();

		inline void acquire ()	const		{ pthread_mutex_lock	(&m_lock); }
		inline void release ()	const		{ pthread_mutex_unlock	(&m_lock); }

	protected:
		mutable pthread_mutex_t m_lock;
	};


	// TODO: use "atomic.h" when availables
	class LockedCounter
	{
	public:
		typedef uint32 UnderlyingType;
		
		inline LockedCounter	(UnderlyingType v=0)		: m_data (v)		{}
		inline LockedCounter	(const LockedCounter &c)	: m_data (c.get())	{}
		inline ~LockedCounter() {}
		
		inline LockedCounter const  & operator=(UnderlyingType v) { set(v); return *this; }
		
		inline LockedCounter const  & operator+=(UnderlyingType v)	
		{ 
			m_lock.acquire();	m_data += v;		m_lock.release();
			return *this;
		}
		
		inline LockedCounter const & operator-=(UnderlyingType v)		
		{ 
			m_lock.acquire();	m_data -= v;		m_lock.release();
			return *this;
		}
		
		inline UnderlyingType		operator++()	
		{ 
			UnderlyingType ret;	
			m_lock.acquire();		ret = ++m_data;		m_lock.release();
			return ret;
		}

		inline UnderlyingType		operator--()		
		{ 
			UnderlyingType ret;	
			m_lock.acquire();		ret = --m_data;		m_lock.release();
			return ret;
		}

		inline UnderlyingType		operator++(int)		
		{ 
			UnderlyingType ret;	
			m_lock.acquire();		ret = m_data++;		m_lock.release();
			return ret;
		}

		inline UnderlyingType		operator--(int)		
		{ 
			UnderlyingType ret;		
			m_lock.acquire();		ret = m_data--;		m_lock.release();
			return ret;
		}
		
		inline void				inc()				
		{ 
			m_lock.acquire();		++m_data;		m_lock.release();
		}

		inline void				dec()		
		{ 
			m_lock.acquire();		--m_data;		m_lock.release();
		}

		inline UnderlyingType	get		() const
		{ 
			UnderlyingType ret;			
			m_lock.acquire();		ret=m_data;			m_lock.release();
			return ret;
		}

		inline UnderlyingType	reset	(UnderlyingType v=0)	{ 
			UnderlyingType ret;
			m_lock.acquire();		ret = m_data;		m_data = v;		m_lock.release();
			return ret;
		}
		
		inline void			set		(UnderlyingType v)		
		{        
			m_lock.acquire();		m_data = v;			m_lock.release();
		}
		
		inline operator UnderlyingType () const				{ return get();}
		
	private:
		ExclusiveLock	m_lock;
		mutable UnderlyingType	m_data;
	};

	/// a "shared read access, 1 write access" lock
	class NonRecursiveReadWriteLock
	{
	public:
		NonRecursiveReadWriteLock  ();
		~NonRecursiveReadWriteLock ();

//?useless!		void acquire				() const { acquire_write_access(); }
		void release_read_access	() const { pthread_rwlock_unlock (&m_lock); }
		void release_write_access	() const { pthread_rwlock_unlock (&m_lock); }
		void acquire_read_access	() const { pthread_rwlock_rdlock (&m_lock); }
		void acquire_write_access	() const { pthread_rwlock_wrlock (&m_lock); }

	protected:
		mutable pthread_rwlock_t m_lock;
	};



#define ReadWriteLock GenericReadWriteLock



	class Semaphore
	{
	public:
		enum e_semaphoreState { semNonInit, semInit, semError };
		
		Semaphore() :
			m_state (semNonInit)
		{}
		
		Semaphore(int initialCount):
			m_state (semNonInit)
		{
			init(initialCount);
		}
		
		virtual ~Semaphore()
		{
			sem_destroy(&m_sem);
		}
		
		void init (int initialCount = 0)
		{
			if (m_state == semInit)
			{	// If semaphore was already init. we destroy it an create a new one with new parameters
				sem_destroy(&m_sem);
			}
			
			if (-1 != sem_init(&m_sem, PTHREAD_PROCESS_PRIVATE, initialCount))	{
				m_state = semInit;
			} else {
				m_state = semError;
			}
		}
		
		// State should be checked after any call to an object method
		bool isStateOk() { return m_state==semInit; }
		
		// Return true if timeout has elapsed
		bool wait(long int timeout=-1);

		// Default post increments semaphore by 1
		void post(unsigned int nToInc = 1)
		{
			for(unsigned int i=0; i<nToInc; ++i){
				if (0 != sem_post(&m_sem))
					m_state = semError;
			}
		}
		
		
	private:
		e_semaphoreState	m_state;
		sem_t				m_sem;
	};

	class ConditionalVariable : public ExclusiveLock
	{
	public:
		ConditionalVariable ();
		~ConditionalVariable  ();

		// Return true if timer elapsed before the variable is signalled
		bool wait (long int timeout_ms=-1) { return (wait_with_rc(timeout_ms) != WaitSignaled); }

		WaitRC wait_with_rc(long int timeout_ms = -1);

		// is bAll is true, we broadcast the signal, else we just signal the variable once
		void signal(bool bAll=false) ;

		void broadcast()
		{
			signal(true);
		}

	private:
		pthread_cond_t	m_cond;
	};

}

/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2003-2005 **/
/** Author: Denery Fenouil         **/
/************************************/

