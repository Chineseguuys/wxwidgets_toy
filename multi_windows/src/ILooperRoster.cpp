#include "ILooperRoster.h"
#include "IHandler.h"

namespace message_channel {
ILooperRoster::ILooperRoster() :
    mNextHandlerID(1) {
}

ILooper::handle_id ILooperRoster::registerHandler(
    const std::shared_ptr<ILooper>  &looper,
    const std::shared_ptr<IHandler> &handler) {
    HandlerInfo info;
    info.mLooper = looper;
    info.mHandler = handler;
    ILooper::handle_id handleID = mNextHandlerID++;
    this->mHandlers.insert({handleID, info});

    handler->setID(handleID, looper);
    return handleID;
}

void ILooperRoster::unregisterHandler(ILooper::handle_id id) {
    // 暂时
}

} // namespace message_channel