//
// Created by ebert on 6/1/2024.
//

#include "Phoenixpp/messaging/message_listener.h"
#include "Phoenixpp/messaging/message_wrapper.h"

namespace roboime {
namespace messaging {

template<typename T>
MessageWrapper<T>::MessageWrapper(T message) {

}
template<typename T>
void MessageWrapper<T>::accept(MessageListener *listener) {
    T message = getMessage();
    listener->updateVisit(message);
}
template<typename T>
T MessageWrapper<T>::getMessage() {
    return message;
}
template<typename T>
MessageWrapper<T>::~MessageWrapper() = default;

} // messaging
} // roboime