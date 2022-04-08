#ifndef _IHANDLER_H_
#define _IHANDLER_H_

#include "ILooper.h"

namespace message_channel {

struct IMessage;

struct IHandler {
private:
    friend struct IMessage;
    friend struct ILooperRoster;

    ILooper::handle_id     mID;
    std::weak_ptr<ILooper> mLooper;

    inline void setID(ILooper::handle_id id, const std::weak_ptr<ILooper> &looper) {
        this->mID = id;
        this->mLooper = looper;
    }

    void deliverMessage(const std::shared_ptr<IMessage> &msg);

public:
    IHandler() :
        mID(0) {
    }

    ILooper::handle_id id() const {
        return this->mID;
    }

protected:
    virtual void onMessageReceived(const std::shared_ptr<IMessage> &msg) = 0;
};
} // namespace message_channel

#endif /* _IHANDLER_H_ */