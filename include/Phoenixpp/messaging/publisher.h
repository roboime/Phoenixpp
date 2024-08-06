//
// Created by ebert on 7/17/2024.
//

#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "listener.h"
#include <unordered_set>

namespace phoenixpp {
namespace messaging {

class Publisher {
public:
    Publisher() = default;
    void addListener(const ListenerPtr &listener);
    void removeListener(const ListenerPtr &listener);
    void distribute(const MessagePtr &message) const;
    ~Publisher() = default;
private:
    std::unordered_set<ListenerPtr> listeners;
};

} // messaging
} // phoenixpp

#endif //PUBLISHER_H
