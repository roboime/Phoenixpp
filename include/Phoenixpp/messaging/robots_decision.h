//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_DECISION_H
#define ROBOTS_DECISION_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsDecision {

};
class RobotsDecisionWrapper : public Message{
public:
    void forwardTo(RobotsDecisionListener *listener) override;
    RobotsDecision getRobotsDecision() const {return robotsDecision;}
private:
    RobotsDecision robotsDecision;
};
using RobotsDecisionWrapperPtr = std::shared_ptr<RobotsDecisionWrapper>;
using RobotsDecisionPtr = std::shared_ptr<boost::atomic<RobotsDecision>>;
} // messaging
} // phoenixpp

#endif //ROBOTS_DECISION_H
