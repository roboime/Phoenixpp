//
// Created by ebert on 6/1/2024.
//

#ifndef MESSAGE_WRAPPER_H
#define MESSAGE_WRAPPER_H
#include "message.h"

namespace roboime {
namespace messaging {

template<typename T>
class MessageWrapper final : public Message{
private:
    T message;
public:
    explicit MessageWrapper(T message);
    void accept(MessageListener *listener) override;
    T getMessage();
    ~MessageWrapper() override;
};

} // messaging
} // roboime
#include "../../../src/messaging/message_wrapper.tpp"
#endif //MESSAGE_WRAPPER_H
