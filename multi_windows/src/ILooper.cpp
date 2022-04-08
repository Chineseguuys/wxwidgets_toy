#include "ILooper.h"
#include "Thread.h"
#include "ILooperRoster.h"
#include <chrono>

namespace message_channel {

ILooperRoster gLooperRoster;

struct ILooper::LooperThread : public Thread {
private:
    ILooper *mLooper;

protected:
    virtual bool threadLoop() {
        return this->mLooper->loop();
    }

public:
    LooperThread(ILooper *looper) :
        Thread(),
        mLooper(looper) {
    }

    virtual ~LooperThread() {
    }
};

// static
int64_t ILooper::GetNowUs() {
    std::chrono::system_clock::time_point time_point_now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration   duration_since_epoch = time_point_now.time_since_epoch();
    time_t                                microseconds_since_epoch = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch).count();
    return static_cast<int64_t>(microseconds_since_epoch);
}

ILooper::ILooper() {
}

void ILooper::setName(const char *name) {
    this->mName = name;
}

ILooper::handle_id ILooper::register_handler(const std::shared_ptr<IHandler> &handler) {
    // Todo 这种做法是正确的吗？
    return gLooperRoster.registerHandler(shared_from_this(), handler);
}

int ILooper::start() {
    std::lock_guard<std::mutex> locker(this->mLock);
    // Todo 一些错误的处理, 异常返回状态等
    this->mThread = std::make_shared<LooperThread>(new LooperThread(this));
    this->mThread->start();
    return 0;
}

bool ILooper::loop() {
    Event event;

    {
        std::unique_lock<std::mutex> autolock(this->mLock);
        if (this->mEventQueue.empty()) {
            this->mQueueChangedCondition.wait(autolock);
            return true;
        }

        int64_t whenUs = (*this->mEventQueue.begin()).mWhenUs;
        int64_t nowUs = GetNowUs();

        if (whenUs > nowUs) {
            int64_t delayUs = whenUs - nowUs;
            this->mQueueChangedCondition.wait_for(autolock, std::chrono::microseconds(delayUs));
            return true;
        }

        event = *this->mEventQueue.begin();
        this->mEventQueue.erase(this->mEventQueue.begin());
    }

    // 等待更新
    // event.mMessage->deliver();
    return true;
}

void ILooper::post(const std::shared_ptr<IMessage> &msg, int64_t delayUs) {
    std::unique_lock<std::mutex> autolock(this->mLock);
    int64_t                      whenUs;
    if (delayUs > 0) {
        int64_t nowUs = GetNowUs();
        whenUs = (delayUs > INT64_MAX - nowUs ? INT64_MAX : nowUs + delayUs);
    } else {
        whenUs = GetNowUs();
    }

    std::list<Event>::iterator it = this->mEventQueue.begin();
    while (it != this->mEventQueue.end() && (*it).mWhenUs <= whenUs) {
        ++it;
    }
    Event event;
    event.mWhenUs = whenUs;
    event.mMessage = msg;
    if (it == mEventQueue.begin()) {
        this->mQueueChangedCondition.notify_all();
    }
    this->mEventQueue.insert(it, event);
}

} // namespace message_channel