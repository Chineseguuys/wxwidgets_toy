#ifndef _THREAD_H_
#define _THREAD_H_

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <memory>

class Thread {
public:
    Thread();
    virtual ~Thread();

    enum THREAD_STATE {
        STOPED,
        RUNNING,
        PAUSED
    };

    THREAD_STATE state() const;
    void         start();
    void         stop();
    void         pause();
    void         resume();

protected:
    // 子类实现该函数作为线程的执行函数
    virtual bool threadLoop() {
    }

public:
    void run();

private:
    std::shared_ptr<std::thread> _thread;
    std::mutex                   _mutex;
    std::condition_variable      _condition;
    std::atomic_bool             _pauseFlag;
    std::atomic_bool             _stopFlag;
    THREAD_STATE                 _state;
};

#endif /* _THREAD_H_ */