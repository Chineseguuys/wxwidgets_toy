#ifndef _ILOOPER_H_
#define _ILOOPER_H_

#include "refbase.h"
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <stdint.h>

namespace message_channel {

struct IHandler;
struct IMessage;

struct ILooper : public std::enable_shared_from_this<ILooper> {
    typedef int32_t event_id;
    typedef int32_t handle_id;

    ILooper();

    void      setName(const char *name);
    handle_id register_handler(const std::shared_ptr<IHandler> &handler);
    void      unregister_handler(handle_id handerID);

    int            start();
    static int64_t GetNowUs();

private:
    friend struct IMessage;
    struct Event {
        int64_t                   mWhenUs;
        std::shared_ptr<IMessage> mMessage;
    };

    struct LooperThread;

    std::string mName; // Looper 拥有自己的名字

    std::mutex              mLock;
    std::condition_variable mQueueChangedCondition;

    std::list<Event>              mEventQueue;
    std::shared_ptr<LooperThread> mThread;

    void post(const std::shared_ptr<IMessage> &msg, int64_t delayUs);
    bool loop(); /*线程实际执行函数*/
};

} /* namespace message_channel */

#endif /* _ILOOPER_H_ */