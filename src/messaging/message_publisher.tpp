//
// Created by ebert on 6/1/2024.
//

#include <Phoenixpp/messaging/message_wrapper.h>

#include <utility>

#include "Phoenixpp/messaging/message_publisher.h"

namespace roboime {
namespace messaging {

template<typename T>
void MessagePublisher<T>::notifyListeners(T message) {
    MessageWrapper<T> messageWrapper(message);
    for(const auto& listener : listeners) {
        listener.second->update(messageWrapper);
    }
}
template<typename T>
void MessagePublisher<T>::subscribe(const std::string& key, std::shared_ptr<MessageListener> listener) {
    listeners[key] = std::move(listener);
}
template<typename T>
void MessagePublisher<T>::unsubscribe(const std::string& key) {
    if(listeners.contains(key)) {
        listeners.erase(key);
    }
}



} // messaging
} // roboime