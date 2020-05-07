#ifndef SQUALLTHREADPOOL_H
#define SQUALLTHREADPOOL_H

#include <functional>
#include <atomic>
#include <thread>
#include <vector>
#include "Sync_queue.h"

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
#ifdef WIN64
    void SetThreadPriority(int nPriority = THREAD_PRIORITY_NORMAL);
#elif __linux__
    void SetThreadPriority(int nPriority = SCHED_OTHER);
#endif
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

#endif // SQUALLTHREADPOOL_H


