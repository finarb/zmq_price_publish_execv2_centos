
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse           **/
/************************************/


namespace FeedOS {

	// defined int date.cpp
	extern int unix_clock_gettime(timespec & ts);

	/// an exclusive lock
	ExclusiveLock::ExclusiveLock ()
	{
		pthread_mutexattr_t		mutexattr;
		pthread_mutexattr_init			(&mutexattr);
		pthread_mutexattr_settype		(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
// CRASH on solaris8			pthread_mutexattr_setprotocol	(&mutexattr, PTHREAD_PRIO_INHERIT);
//			pthread_mutexattr_getpshared	(&mutexattr, PTHREAD_PROCESS_PRIVATE);	// this is the default
		pthread_mutex_init(&m_lock, &mutexattr);
		pthread_mutexattr_destroy	(&mutexattr);
	}

	ExclusiveLock::~ExclusiveLock ()
	{
		pthread_mutex_destroy	(&m_lock); 
	}

	NonRecursiveReadWriteLock::NonRecursiveReadWriteLock  ()
	{
//			pthread_rwlockattr_t	rwlockattr;
//			pthread_rwlockattr_init			(&rwlockattr);
//			pthread_rwlockattr_setpshared	(&rwlockattr, PTHREAD_PROCESS_PRIVATE);	// this is the default

		pthread_rwlock_init(&m_lock,0/*&rwlockattr*/);

//			pthread_rwlockattr_destroy	(&rwlockattr);
	}

	NonRecursiveReadWriteLock::~NonRecursiveReadWriteLock ()	
	{
		pthread_rwlock_destroy(&m_lock); 
	}

	ConditionalVariable::ConditionalVariable ()
	{ 
		pthread_cond_init(&m_cond, NULL);
	}

	ConditionalVariable::~ConditionalVariable  ()
	{
		pthread_cond_destroy(&m_cond);
	}

	void ConditionalVariable::signal(bool bAll)
	{
		FEEDOS_SCOPER (Lock, "ConditionalVariable::signal()");
		if (bAll) {
			pthread_cond_broadcast(&m_cond);
		} else {
			pthread_cond_signal(&m_cond);
		}
	}

	WaitRC ConditionalVariable::wait_with_rc(long int timeout_ms)
	{
		FEEDOS_LOG (Lock, Debug, "ConditionalVariable::wait(BEGIN) timeout_ms="<<timeout_ms);
		if (-1 == timeout_ms){
			FEEDOS_SCOPER (Lock, "ConditionalVariable::wait() infinite");
			int ret = pthread_cond_wait(&m_cond, &m_lock);
			if (0 != ret) {
				FEEDOS_LOG (Lock, Critical, "ConditionalVariable::wait() pthread_cond_wait failed, err="<<ret);
				return WaitError;
			}
			FEEDOS_LOG (Lock, Debug, "ConditionalVariable::wait(END)");
			return WaitSignaled;
		} else {
			FEEDOS_SCOPER (Lock, "ConditionalVariable::wait() with timeout");
			timespec ts;
			int err = unix_clock_gettime(ts);
			if (0 != err) {
				FEEDOS_LOG (Lock, Critical, "ConditionalVariable::wait() clock_gettime failed, err="<<err);
				return WaitError;
			}
			time_t sec = timeout_ms/1000;
			ts.tv_sec += sec;
			ts.tv_nsec += (timeout_ms%1000)*1000*1000;
			if (ts.tv_nsec >= 1000*1000*1000) {
				ts.tv_nsec -= 1000*1000*1000;
				ts.tv_sec += 1;
			}
			int ret = pthread_cond_timedwait(&m_cond, &m_lock, &ts);
			switch (ret) {
			case 0:
				FEEDOS_LOG (Lock, Debug, "ConditionalVariable::wait(END) signaled");
				return WaitSignaled;
			case ETIMEDOUT:
				FEEDOS_LOG (Lock, Debug, "ConditionalVariable::wait(END) timed out");
				return WaitTimedOut;
			default:
				FEEDOS_LOG (Lock, Critical, "ConditionalVariable::wait(END) pthread_cond_timedwait failed, err="<<ret);
				return WaitError;
			}
		}
	}

	bool Semaphore::wait(long int /*timeout*/)
	{
		int err=0;
		do {
			err = sem_wait(&m_sem);		// TODO: timeout ?!
			if (-1 == err)
				err = errno;
		} while (EINTR == err);

		if (0 != err){
			m_state = semError;
			return true;
		}
		return false;
	}

}
