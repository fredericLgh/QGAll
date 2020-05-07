/**********************************************************************

Copyright(c) ŷ���Ƽ������

�ļ����ƣ�sync_queue.h
�ļ�������ͬ�����У���ģ�壩
��ǰ�汾��1.2 v
��    �ߣ�Squall����һ��
ĩ���޸ģ�2017-11-27

����������

1������ͬ���ȴ����ܵģ��̰߳�ȫ�Ķ��С�
2������push() �ڶ�����ʱ��������pop() �ڶ��п�ʱ��������
3���ṩ�ж������Ĺ��ܡ�
4��Ӧ�ó��ϣ�������߳��µġ��������������ߵ����⡱��

�������ܣ�

std::queue						stl �ı�׼���У��̲߳���ȫ
concurrency::concurrent_queue	�̰߳�ȫ�Ķ��У�����ģʽ���У�
concurrency::unbounded_buffer	��ͬ�����ܵ��̰߳�ȫ���У��첽������У�

std::queue ���������ƣ����̲߳���ȫ��
concurrency::concurrent_queue �е㼦�ߣ���ΪֻҪ�漰���̶߳�д������ͬ������
���������̰߳�ȫ�ǲ����ġ�
concurrency::unbounded_buffer ����֧��ͬ���ˣ�������̫�������ȶ��в��ܶ������ޣ�
�� push ��֧�����������ⲻ֧�� try_push �����ⲻ���ж�ͬ�������ܻ�ȡ size()��
����ֻ֧�ֵ��㻽�ѣ���֧��ȫ�����ѡ��ҵ��ܽ��ǣ�unbounded_buffer ���ʺ��������������
���ʺ�����ѭ�����������

sync_queue ��ʵ���Ƕ� unbounded_buffer ��ǿ���͸Ľ���������ʵ�ֹܵ��������ӷǳ����ʡ�
��ؼ��ģ�sync_queue ʹ�á�������������ʵ��ͬ��������ʵ�������޵ȴ�����ʵ�������޵ȴ���
�������ʹ�ã��ܵ������ܿ������������������Կ��Ƹ����ڵķ���������ͨ���趨������󳤶ȣ���


************************************************************************/

#pragma once

#include <exception>
#include <mutex>
#include <condition_variable>
#include <list>
#include <queue>


namespace squall
{

	template <typename T>
	class sync_queue
	{
	public:
		sync_queue(size_t MaxLength = SIZE_MAX) : m_MaxQueueSize(MaxLength), m_Cancel(false)
		{
			_ASSERT(MaxLength > 0);
		}

		~sync_queue()
		{

		}

		void SetMaxLength(size_t MaxLength)			//���û��޸ġ������г��ȡ�
		{
			std::lock_guard<std::mutex> Lg(m_Mutex);
			_ASSERT(MaxLength > 0);
			m_MaxQueueSize = MaxLength;
		}

		bool push(T& v)	//������ֵ���ǳ�����ֵ
		{
			std::unique_lock<std::mutex> Lg(m_Mutex);

			//���� void wait (unique_lock<mutex>& lck, Predicate pred) ��˵����while (!pred()) wait(lck); 

			while (m_DataQueue.size() >= m_MaxQueueSize && !m_Cancel)
			{
				m_QueueNotFull.wait(Lg);
			}

			if (m_Cancel)
			{
				return false;
			}

			_ASSERT(m_DataQueue.size() < m_MaxQueueSize);
			m_DataQueue.push(v);
			m_QueueNotEmpty.notify_one();

			return true;
		}

		bool push(T&& v)	//�ǳ�����ֵ��������ֵ
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


		bool try_push(T& v)	//������ֵ���ǳ�����ֵ
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

		bool try_push(T&& v)	//�ǳ�����ֵ��������ֵ
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

			_ASSERT(!m_DataQueue.empty());

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

		bool m_Cancel;
		size_t m_MaxQueueSize;
	};


}
