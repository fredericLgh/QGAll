/***************************************************************************

	Copyright(c) ŷ���Ƽ������

	�ļ����ƣ�SquallThreadPool.h
	�ļ��������̳߳�
	��ǰ�汾��1.5 v
	��    �ߣ�Squall (��һ)
	������ڣ�2016-12-29
	ĩ���޸ģ�2017-11-27
	����˵����ʵ���̳߳ع��ܡ�����ʱ������Ҫ���ٴ����̣߳�����Ҫ�õ��̳߳أ�
			  
	
	���÷�����

	class CApp
	{
		CSquallThreadPool m_threadPool;

		void Init();
		void customer1(int a, int b, int c);					//��Ա����
		static void customer2(int a, int b, int c);				//��̬��Ա����

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
		//��Ա������ bind ����
		TaskFunction task = std::bind(&CApp::customer1, this, a, b, c);
		m_ThreadPool.PushTask(task);

		//��̬��Ա������ bind ����
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

#define  SUGGESTED_TASK_QUEUE_SIZE			20			//����������������

using TaskFunction = std::function<void()>;					//����������ص�����������std::bind()��ʵ�֡����в������޲����İ󶨡���
using TaskError = std::function<void(const std::string)>;	//�����˴�����ص�����

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



