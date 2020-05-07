#pragma once
#include <exception>
#include <mutex>
#include <condition_variable>
#include <list>
#include <queue>
#include <cassert>
namespace squall
{

	template <typename T>
	class sync_queue
	{
	public:
		sync_queue(size_t MaxLength = SIZE_MAX)
			: m_MaxQueueSize(MaxLength)
			, m_Cancel(false)
		{
			assert(MaxLength > 0);
		}

		~sync_queue()
		{

		}

		void SetMaxLength(size_t MaxLength)			//设置或修改“最大队列长度”
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);
			assert(MaxLength > 0);
			m_MaxQueueSize = MaxLength;
		}

		bool push(T& v)	//常量左值、非常量左值
		{
			std::unique_lock<std::mutex> Lg(m_Mutex);

			//关于 void wait (unique_lock<mutex>& lck, Predicate pred) 的说明：while (!pred()) wait(lck);

			while (m_DataQueue.size() >= m_MaxQueueSize && !m_Cancel)
			{
				m_QueueNotFull.wait(Lg);
			}

			if (m_Cancel)
			{
				return false;
			}

			assert(m_DataQueue.size() < m_MaxQueueSize);
			m_DataQueue.push(v);
			m_QueueNotEmpty.notify_one();

			return true;
		}

		bool push(T&& v)	//非常量右值、常量右值
		{
			std::unique_lock<std::mutex> Lg(m_Mutex);

			while (m_DataQueue.size() >= m_MaxQueueSize && !m_Cancel)
			{
				m_QueueNotFull.wait(Lg);
			}

			if (m_Cancel)
			{
				return false;
			}

			_ASSERT(m_DataQueue.size() < m_MaxQueueSize);
			m_DataQueue.push(std::forward<T>(v));
			m_QueueNotEmpty.notify_one();

			return true;
		}


		bool try_push(T& v)	//常量左值、非常量左值
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);

			if (m_DataQueue.size() < m_MaxQueueSize)
			{
				m_DataQueue.push(v);
				m_QueueNotEmpty.notify_one();
				return true;
			}
			else
			{
				return false;
			}
		}

		bool try_push(T&& v)	//非常量右值、常量右值
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);

			if (m_DataQueue.size() < m_MaxQueueSize)
			{
				m_DataQueue.push(std::forward<T>(v));
				m_QueueNotEmpty.notify_one();
				return true;
			}
			else
			{
				return false;
			}
		}

		bool pop(T& v)
		{
			std::unique_lock<std::mutex> Lg(m_Mutex);

			while (m_DataQueue.empty() && !m_Cancel)
			{
				m_QueueNotEmpty.wait(Lg);
			}

			if (m_Cancel)
			{
				return false;
			}

			assert(!m_DataQueue.empty());

			v = m_DataQueue.front();
			m_DataQueue.pop();

			m_QueueNotFull.notify_one();

			return true;
		}

		bool try_pop(T& v)
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);

			if (!m_DataQueue.empty())
			{
				v = m_DataQueue.front();
				m_DataQueue.pop();

				m_QueueNotFull.notify_one();

				return true;
			}
			else
			{
				return false;
			}
		}

		void cancel_pending()
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);

			m_Cancel = true;
			m_QueueNotFull.notify_all();
			m_QueueNotEmpty.notify_all();
		}

		size_t size()
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);
			return m_DataQueue.size();
		}

		bool empty()
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);
			return m_DataQueue.empty();
		}

		void clear()
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);

			while (!m_DataQueue.empty())
			{
				m_DataQueue.pop();
			}

			m_Cancel = false;
		}

	protected:
		std::queue<T, std::list<T>> m_DataQueue;

		std::mutex m_Mutex;
		std::condition_variable m_QueueNotEmpty;
		std::condition_variable m_QueueNotFull;

		size_t m_MaxQueueSize;
		bool   m_Cancel;
	};


}