
/*****************************************/
/** FeedOS C++ Client API			 	**/
/**									 	**/
/** copyright QuantHouse 2005-2009		**/
/**										**/
/*****************************************/

#ifndef FEEDOS_IPCSHAREDMEMORY_OPTIONS_H
#define FEEDOS_IPCSHAREDMEMORY_OPTIONS_H

#ifndef FEEDOS_BASE_BASE_H
#  include "../../base/base.h"
#endif

namespace FeedOS
{

	class IPCSharedMemoryOptions
	{
		/*! Security margin is the minimal distance (in msg) that should be kept
		 * if the reader is too slow, in that case the buffer is copied instead
		 * of returning the SHM pointer.
		 * 0 means pointer to SHM will always be returned.
		 * Default value is 10.
		 */
		uint32 m_MsgSecurityMargin;

		/*! Duration of the spin loop (no wait time between shared memory read)
		 * If no successful read occurs during this time, the sleep loop is entered.
		 *
		 * Default is 10 usec.
		 */
		uint32 m_SpinDuration; // usec
	
		/*! Sets initial and increment value of the sleep time after the spin loop
		 * returned unsuccessfully:
		 * First sleeps, then checks if data are there and goes back to sleep for n
		 * loops.
		 * Once the n loops are elapsed sleep time is incremented until the max sleep
		 * time is reached.
		 *
		 * Default is 1 usec.
		 */
		uint32 m_SleepTime; // usec

		/*! Sets the max sleep time after which the idle loop is entered.
		 *
		 * Default is 100 usec.
		 */
		uint32 m_MaxSleepTime; // usec

		/*! Number of read call that will be performed before incrementing the sleep
		 * time.
		 * Default is 100.
		 */
		uint32 m_IntermediateLoopCount;
		
		/*! After the max sleep time is reached, a sleep is performed between each read
		 * call.
		 * Default is 100 usec.
		 */
		uint32 m_IdleSleepTime; // usec

	public:
		IPCSharedMemoryOptions()
			: m_MsgSecurityMargin(10)
			, m_SpinDuration(10)
			, m_SleepTime(1)
			, m_MaxSleepTime(100)
			, m_IntermediateLoopCount(100)
			, m_IdleSleepTime(100)
		{
		}

		void setMsgSecurityMargin(uint32 s)
		{
			m_MsgSecurityMargin = s;
		}

		uint32 getMsgSecurityMargin() const
		{
			return m_MsgSecurityMargin;
		}

		void setSpinDuration(uint32 s)
		{
			m_SpinDuration = s;
		}

		uint32 getSpinDuration() const
		{
			return m_SpinDuration;
		}

		void setSleepTime(uint32 s)
		{
			m_SleepTime = s;
		}

		uint32 getSleepTime() const
		{
			return m_SleepTime;
		}

		void setMaxSleepTime(uint32 s)
		{
			m_MaxSleepTime = s;
		}

		uint32 getMaxSleepTime() const
		{
			return m_MaxSleepTime;
		}

		void setIntermediateLoopCount(uint32 s)
		{
			m_IntermediateLoopCount = s;
		}

		uint32 getIntermediateLoopCount() const
		{
			return m_IntermediateLoopCount;
		}

		void setIdleSleepTime(uint32 s)
		{
			m_IdleSleepTime = s;
		}

		uint32 getIdleSleepTime() const
		{
			return m_IdleSleepTime;
		}

	};

} // namespace FeedOS

#endif // FEEDOS_IPCSHAREDMEMORY_OPTIONS_H
