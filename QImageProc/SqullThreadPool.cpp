//#include "stdafx.h"
#include "SquallThreadPool.h"

#ifdef WIN64

#elif __linux__
#include <pthread.h>
#endif

using namespace squall;

CSquallThreadPool::CSquallThreadPool()
{
	m_ExitSign = true;

	m_MaxThreadSize = std::thread::hardware_concurrency();	//获取cpu硬件线程数量

	m_TaskQueue.SetMaxLength(SUGGESTED_TASK_QUEUE_SIZE);
}

CSquallThreadPool::~CSquallThreadPool()
{
	if (!m_ExitSign)
	{
		DestroyPool();
	}
}

void CSquallThreadPool::SetErrFunction(TaskError f)
{
	m_ErrOutputFunction = f;
}

void CSquallThreadPool::CreatePool(int MaxThreadNum)
{
	if (MaxThreadNum > 0) m_MaxThreadSize = MaxThreadNum;

	m_ExitSign = false;

	for (size_t i = 0; i < m_MaxThreadSize; i++)
	{
		m_vecThreads.push_back(std::thread(&CSquallThreadPool::WorkThread, this));
	}

}

void CSquallThreadPool::DestroyPool(void)
{
	m_ExitSign = true;

	m_TaskQueue.cancel_pending();

	for (auto &Thread : m_vecThreads)
	{
		if (Thread.joinable())
		{
			Thread.join();
		}
	}
}

void CSquallThreadPool::SetMaxTaskSize(int MaxTaskNum)
{
	if (MaxTaskNum > 0) m_TaskQueue.SetMaxLength(MaxTaskNum);
}



#ifdef WIN64
void CSquallThreadPool::SetThreadPriority(int nPriority)
{
	for (auto &Thread : m_vecThreads)
	{
		if (Thread.joinable())
		{
			::SetThreadPriority(Thread.native_handle(), nPriority);		//windows API 函数
		}
	}
}
#elif __linux__

void CSquallThreadPool::SetThreadPriority(int nPriority)
{
	for (auto &Thread : m_vecThreads)
	{
		if (Thread.joinable())
		{
			pthread_setschedprio(Thread.native_handle(), nPriority);
		}
	}
}

#endif

bool CSquallThreadPool::TryPushTask(TaskFunction f)
{
	return m_TaskQueue.try_push(f);
}

void CSquallThreadPool::PushTask(TaskFunction f)
{
	m_TaskQueue.push(f);
}

int CSquallThreadPool::GetTaskSize()
{
	return (int)m_TaskQueue.size();
}

void CSquallThreadPool::WorkThread(void)
{
	while (1)
	{
		TaskFunction task;

		if (m_TaskQueue.pop(task))
		{
			try
			{
				task();
			}
			catch (std::exception &err)
			{
				std::string ErrMsg(err.what());
				if (m_ErrOutputFunction) m_ErrOutputFunction(ErrMsg);
			}
			catch (...)
			{
				std::string ErrMsg("Task 未知错误");
				if (m_ErrOutputFunction) m_ErrOutputFunction(ErrMsg);
			}
		}

		if (m_ExitSign)
		{
			return;
		}
	}

}
