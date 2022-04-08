#include "Thread.h"

Thread::Thread() :
    _thread(nullptr),
    _pauseFlag(false),
    _stopFlag(false),
    _state(THREAD_STATE::STOPED) {
}

Thread::~Thread() {
    this->stop();
}

Thread::THREAD_STATE Thread::state() const {
    return this->_state;
}

void Thread::start() {
    if (this->_thread == nullptr) {
        this->_thread = std::make_shared<std::thread>(new std::thread(&Thread::run, this));
        this->_pauseFlag = false;
        this->_stopFlag = false;
        this->_state = THREAD_STATE::RUNNING;
    }
}

void Thread::pause() {
    if (this->_thread != nullptr) {
        this->_pauseFlag = true;
        this->_state = THREAD_STATE::PAUSED;
    }
}

void Thread::stop() {
    if (this->_thread != nullptr) {
        this->_pauseFlag = false;
        this->_stopFlag = true;
        this->_condition.notify_all();
        this->_thread->join();

        this->_thread.reset();
        this->_thread = nullptr;
        this->_state = THREAD_STATE::STOPED;
    }
}

void Thread::pause() {
    if (this->_thread != nullptr) {
        this->_pauseFlag = true;
        this->_state = THREAD_STATE::PAUSED;
    }
}

void Thread::resume() {
    if (this->_thread != nullptr) {
        this->_pauseFlag = false;
        this->_condition.notify_all();
        this->_state = THREAD_STATE::RUNNING;
    }
}

void Thread::run() {
    while (!this->_stopFlag) {
        this->threadLoop();
        if (this->_pauseFlag) {
            std::unique_lock<std::mutex> locker(this->_mutex);
            while (this->_pauseFlag) {
                this->_condition.wait(locker);
            }
            locker.unlock();
        }
    }
    this->_pauseFlag = false;
    this->_stopFlag = false;

    // exit thread
}