#include "ThreadPool.h"

void ThreadPool::start() {
    m_work = true;
    for(int i = 0; i < 4; ++i) {
        m_threads.push_back(std::thread(&ThreadPool::threadFunc, this));
    }
}

void ThreadPool::stop() {
    m_work = false;
    m_event_holder.notify_all();
    for (auto& t : m_threads) {
        t.join();
    }
}

void ThreadPool::threadFunc() {
     while (true) {
        std::function<void()> task_to_do;
        {
            std::unique_lock<std::mutex> l(m_mutex);
            if (m_task_queue.empty() && !m_work)
                return;
            if (m_task_queue.empty()) {
                m_event_holder.wait(l, [&]() {return !m_task_queue.empty() || !m_work; });
            }
            if (!m_task_queue.empty()) {
                task_to_do = m_task_queue.front();
                m_task_queue.pop();
            }
        }
        if (task_to_do) 
            task_to_do();
    }
}
