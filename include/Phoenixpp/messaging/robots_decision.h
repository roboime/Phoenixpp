//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_DECISION_H
#define ROBOTS_DECISION_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsDecision : Message{
    void forwardTo(RobotsDecisionListener *listener) override;
    void store(const RobotsDecision& other){}
};
using RobotsDecisionPtr = std::shared_ptr<RobotsDecision>;
} // messaging
} // phoenixpp

#endif //ROBOTS_DECISION_H
