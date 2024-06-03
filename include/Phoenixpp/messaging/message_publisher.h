//
// Created by ebert on 6/1/2024.
//

#ifndef MESSAGE_PUBLISHER_H
#define MESSAGE_PUBLISHER_H
#include <unordered_map>

#include "message_listener.h"

namespace roboime {
namespace messaging {

template<typename T>
class MessagePublisher {
private:
    std::unordered_map<std::string, std::shared_ptr<MessageListener>> listeners;
public:
    void notifyListeners(T message);
    void subscribe(const std::string& key, std::shared_ptr<MessageListener>);
    void unsubscribe(const std::string& key);

};
} // messaging
} // roboime
#include "../../../src/messaging/message_publisher.tpp"
#endif //MESSAGE_PUBLISHER_H
