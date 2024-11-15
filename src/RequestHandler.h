#ifndef REQUESTHANDER_H
#define REQUESTHANDER_H

#include "ThreadPool.h"

class RequestHandler {
public:
    RequestHandler();
    ~RequestHandler();

    //шаблонная функция может принимать шаблон с типом F и шаблон Args с переменным числом параметров.
    template<typename F, typename... Args>
    void push_task(F&& f, Args&&... args);

private:
    ThreadPool m_pool;
};

#endif

//шаблонные функции реализуются в файле .h ??
template <typename F, typename... Args>
inline void RequestHandler::push_task(F &&f, Args &&...args) {
    m_pool.push_task(std::forward<F>(f), std::forward<Args>(args)...);
}
