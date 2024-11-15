#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <future>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    ThreadPool() = default;
    void start();
    void stop();

    //шаблонная функция может принимать шаблон с типом F и шаблон Args с переменным числом параметров.
    template<typename F, typename... Args>
    void push_task(F&& f, Args&&... args);

    void threadFunc();
private:
    //вектор потоков
    std::vector<std::thread> m_threads;
    // очередь задач
    std::queue<std::function<void()>> m_task_queue;
    //мьютекс и условная переменная
    std::mutex m_mutex;
    std::condition_variable m_event_holder;
    volatile bool m_work;
};

#endif

//шаблонные функции реализуются в файле .h ??
template <typename F, typename... Args>
inline void ThreadPool::push_task(F &&f, Args &&...args) {
    {
        std::lock_guard<std::mutex> l(m_mutex);
        m_task_queue.push(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    }
    m_event_holder.notify_one();
}
