/**********************************************************************

Copyright(c) ŷ���Ƽ������

�ļ����ƣ�sync_event.h
�ļ��������¼�
��ǰ�汾��1.0 v
��    �ߣ�Squall����һ��
ĩ���޸ģ�2017-10-16

������������ȫģ�� windows ���Ķ��� Event ��ʵ���¼�֪ͨ��

1���Զ���������£�set()������һ������ĵȴ������� wait() ���Զ����ã�
2���ֶ���������£�set()�������й���ĵȴ������� wait() �������ã�

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

		void reset()	//�Զ�����ģʽ�£�������øú�����
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);
			m_SignalStatus = false;
		}

		void wait()
		{
			//�Զ������£��κ�ʱ����� wait() �������ź�״̬��Ϊ��Ч��

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