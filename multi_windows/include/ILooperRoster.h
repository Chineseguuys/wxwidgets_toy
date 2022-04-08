#include "ILooper.h"
#include <map>

namespace message_channel {

struct ILooperRoster {
    ILooperRoster();
    ILooper::handle_id registerHandler(
        const std::shared_ptr<ILooper> &looper, const std::shared_ptr<IHandler> &handler);
    void unregisterHandler(ILooper::handle_id handlerID);

    struct HandlerInfo {
        std::weak_ptr<ILooper>  mLooper;
        std::weak_ptr<IHandler> mHandler;
    };

private:
    std::mutex                                mLock;
    std::map<ILooper::handle_id, HandlerInfo> mHandlers;
    ILooper::handle_id                        mNextHandlerID;
};
} // namespace message_channel