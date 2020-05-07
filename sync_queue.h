/**********************************************************************

Copyright(c) 欧博科技软件部

    文件名称：sync_queue.h
    文件描述：同步队列（类模板）
    当前版本：1.2 v
    作    者：Squall（朱一）
    末次修改：2017-11-27

               功能描述：

               1、带有同步等待功能的，线程安全的队列。
               2、即：push() 在队列满时被阻塞，pop() 在队列空时被阻塞。
               3、提供中断阻塞的功能。
               4、应用场合：解决多线程下的“生产者与消费者的问题”。

               背景介绍：

               std::queue						stl 的标准队列，线程不安全
               concurrency::concurrent_queue	线程安全的队列（并行模式库中）
               concurrency::unbounded_buffer	带同步功能的线程安全队列（异步代理库中）

               std::queue 功能最完善，但线程不安全。
               concurrency::concurrent_queue 有点鸡肋，因为只要涉及多线程读写，都有同步需求，
               仅仅满足线程安全是不够的。
               concurrency::unbounded_buffer 终于支持同步了，但功能太弱。首先队列不能定义上限，
               即 push 不支持阻塞，另外不支持 try_push ，另外不能中断同步，不能获取 size()，
               另外只支持单点唤醒，不支持全部唤醒。我的总结是：unbounded_buffer 仅适合有限任务关联，
               不适合无限循环任务关联。

               sync_queue 的实现是对 unbounded_buffer 的强化和改进。用它来实现管道任务连接非常合适。
               最关键的，sync_queue 使用“条件变量”来实现同步，不仅实现了下限等待，还实现了上限等待；
               这个特性使得：管道不仅能控制总任务量，还可以控制各环节的分任务量（通过设定队列最大长度）。


************************************************************************/

#ifndef SYNC_QUEUE_H
#define SYNC_QUEUE_H


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
			:m_MaxQueueSize(MaxLength)
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

#endif // SYNC_QUEUE_H
