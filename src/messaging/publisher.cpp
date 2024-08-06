//
// Created by ebert on 7/17/2024.
//

#include "Phoenixpp/messaging/publisher.h"

namespace phoenixpp {
namespace messaging {

void Publisher::distribute(const MessagePtr &message) const{
    for (auto& listener : listeners) {
        listener->update(message);
    }
}

void Publisher::addListener(const ListenerPtr &listener) {
    listeners.insert(listener);
}
void Publisher::removeListener(const ListenerPtr &listener) {
    listeners.erase(listener);
}

} // messaging
} // phoenixpp