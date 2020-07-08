/**********************************************************************

Copyright(c) 欧博科技软件部

文件名称：sync_event.h
文件描述：事件
当前版本：1.0 v
作    者：Squall（朱一）
末次修改：2017-10-16

功能描述：完全模仿 windows 核心对象 Event 来实现事件通知。

1、自动重置情况下：set()仅激活一个挂起的等待；调用 wait() 会自动重置；
2、手动重置情况下：set()激活所有挂起的等待；调用 wait() 不会重置；

************************************************************************/

#pragma once

#include <exception>
#include <mutex>
#include <condition_variable>


namespace squall
{
	class sync_event
	{
	public:
		enum EvnetType
		{
			LGH_WAIT_OBJECT_0,
			LGH_WAIT_TIMEOUT,
			LGH_WAIT_FAILED
		};

		sync_event(bool AutoReset = true)
		{
			m_AutoReset = AutoReset;
			m_SignalStatus = false;
		}

		~sync_event()
		{

		}

		void set()
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);
			m_SignalStatus = true;

			if (m_AutoReset)
			{
				m_Signal.notify_one();
			}
			else
			{
				m_Signal.notify_all();
			}
		}

		void reset()	//自动重置模式下，无需调用该函数。
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);
			m_SignalStatus = false;
		}

		void wait()
		{
			//自动重置下，任何时候调用 wait() 都会让信号状态变为无效。

			std::unique_lock<std::mutex> Lg(m_Mutex);

			while (m_SignalStatus == false)
			{
				m_Signal.wait(Lg);
			}

			if (m_AutoReset)
			{
				m_SignalStatus = false;
			}
		}
		EvnetType wait(int millisecond)
		{
			std::unique_lock<std::mutex> Lg(m_Mutex);

			EvnetType  type = LGH_WAIT_OBJECT_0;
			while (m_SignalStatus == false)
			{
				if (std::cv_status::timeout == m_Signal.wait_for(Lg, std::chrono::milliseconds(millisecond)))
				{
					type = LGH_WAIT_TIMEOUT;
					break;
				}
			}

			if (m_AutoReset)
			{
				m_SignalStatus = false;
			}
			return  type;
		}

	private:
		bool m_AutoReset;
		bool m_SignalStatus;
		std::mutex m_Mutex;
		std::condition_variable m_Signal;
	};

}