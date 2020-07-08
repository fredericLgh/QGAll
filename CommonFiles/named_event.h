/**********************************************************************

Copyright(c) ŷ���Ƽ������

�ļ����ƣ�named_event.h
�ļ������������¼�
��ǰ�汾��1.1 v
��    �ߣ�Squall����һ��
ĩ���޸ģ�2018-12-20

�������������ڽ��̼�֪ͨ��ע������ͬʱ֪ͨ����ȴ�����

************************************************************************/

#pragma once
#include <exception>
#include <Windows.h>


namespace squall
{

	class named_event
	{
	public:
		HANDLE m_hEvent;

		named_event(LPCWSTR Name)
		{
			//LPSECURITY_ATTRIBUTES   lpEventAttributes,
			//BOOL     bManualReset,
			//BOOL     bInitialState,
			//LPCTSTR  lpName

			//If the function succeeds, the return value is a handle to the event object. 
			//If the named event object existed before the function call, the function returns a handle to the existing object 
			//and GetLastError returns ERROR_ALREADY_EXISTS.
			//If the function fails, the return value is NULL.To get extended error information, call GetLastError.

			//���� CreateEvent ʱ���ں˶����ʹ�ü�����һ��
			m_hEvent = CreateEventW(NULL, TRUE, FALSE, Name);
			if (m_hEvent == NULL)
			{
				throw std::exception("Create Named Event Error.");
			}

		}

		~named_event()
		{
			//����CloseHandleʱ���ں˶����ʹ�ü�����һ�����ں˶����ʹ�ü�����Ϊ0���ں˳����ö���
			CloseHandle(m_hEvent);
			m_hEvent = INVALID_HANDLE_VALUE;
		}

		void pulse()
		{
			::PulseEvent(m_hEvent);		//ʹ�¼��и����ݣ�����Ч����Ч���ٵ���Ч���������̾���ԭ���ԣ�������
		}

		void set()
		{
			::SetEvent(m_hEvent);		//ʹ�¼���Ϊ���ź�״̬
		}

		void reset()
		{
			::ResetEvent(m_hEvent);		//ʹ�¼���Ϊ���ź�״̬
		}

		//�ȵ����źŷ���true����ʱ����false��
		bool wait(DWORD tm = INFINITE)
		{
			DWORD dwWaitResult = WaitForSingleObject(m_hEvent, tm);

			if (dwWaitResult == WAIT_OBJECT_0)
			{
				return true;
			}
			else if (dwWaitResult == WAIT_TIMEOUT)
			{
				return false;
			}
			else
			{
				throw std::exception("WaitForSingleObject Error.");
				return false;
			}

		}
	};

}

