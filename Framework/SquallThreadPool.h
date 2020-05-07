/***************************************************************************

	Copyright(c) 欧博科技软件部

	文件名称：SquallThreadPool.h
	文件描述：线程池
	当前版本：1.5 v
	作    者：Squall (朱一)
	完成日期：2016-12-29
	末次修改：2017-11-27
	功能说明：实现线程池功能。（短时间内需要开辟大量线程，才需要用到线程池）
			  
	
	调用方法：

	class CApp
	{
		CSquallThreadPool m_threadPool;

		void Init();
		void customer1(int a, int b, int c);					//成员函数
		static void customer2(int a, int b, int c);				//静态成员函数

		void producer();
		void OnTaskError(const std::string err);
	}

	void CApp::Init()
	{
		m_threadPool.Create();
		TaskError Fun = std::bind(&CApp::OnTaskError, this, std::placeholders::_1);
		m_ThreadPool.SetErrFunction(Fun);
	}

	void CApp::producer()
	{
		//成员函数的 bind 方法
		TaskFunction task = std::bind(&CApp::customer1, this, a, b, c);
		m_ThreadPool.PushTask(task);

		//静态成员函数的 bind 方法
		TaskFunction task = std::bind(CApp::customer2, a, b, c);
		m_ThreadPool.PushTask(task);
	}
	
	void CApp::OnTaskError(const std::string msg)
	{
	}

	void CApp::customer1(int a, int b, int c)
	{
	}

	void CApp::customer2(int a, int b, int c)
	{
	}

*****************************************************************************/

#pragma once

#include <functional>
#include <atomic>
#include <thread>
#include <vector>
#include "sync_queue.h"

#define  SUGGESTED_TASK_QUEUE_SIZE			20			//建议的最大任务数量

using TaskFunction = std::function<void()>;					//定义了任务回调函数，可用std::bind()来实现“从有参数到无参数的绑定”。
using TaskError = std::function<void(const std::string)>;	//定义了错误处理回调函数

namespace squall
{
	class CSquallThreadPool
	{
	public:

		CSquallThreadPool();
		~CSquallThreadPool();

		void CreatePool(int MaxThreadNum = 0);
		void DestroyPool(void);
		void SetMaxTaskSize(int MaxTaskNum);
		void SetThreadPriority(int nPriority = THREAD_PRIORITY_NORMAL);
		bool TryPushTask(TaskFunction f);
		void PushTask(TaskFunction f);
		int GetTaskSize();

		void SetErrFunction(TaskError f);

	protected:

		void WorkThread(void);

		sync_queue<TaskFunction> m_TaskQueue;

		std::vector<std::thread> m_vecThreads;
		size_t m_MaxThreadSize;
		std::atomic_bool m_ExitSign;

		TaskError m_ErrOutputFunction;
	};
}



