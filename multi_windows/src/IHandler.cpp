#include "IHandler.h"

namespace message_channel {

void IHandler::deliverMessage(const std::shared_ptr<IMessage> &msg) {
    this->onMessageReceived(msg);
}
} // namespace message_channel
