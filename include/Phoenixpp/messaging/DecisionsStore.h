//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_DECISION_H
#define ROBOTS_DECISION_H

#include "environment.h"
#include "message.h"
#include "Phoenixpp/messaging/RobotDecision.h"


namespace phoenixpp::messaging {
struct DecisionsStore : Message{
    DecisionsStore()= default;
    DecisionsStore(const DecisionsStore& other) { store(other); };
    DecisionsStore(DecisionsStore&& other) noexcept { store(other); }
    RobotDecision robotsDecisions[MAX_ROBOTS];
    void forwardTo(DecisionsStoreListener *listener) override;
    void storeRobot(const RobotDecision& newRobotDecision) {
        robotsDecisions[newRobotDecision.id].store(newRobotDecision);
    }
    void store(const DecisionsStore& other) {
        for(int i=0;i<MAX_ROBOTS;i++) {
            robotsDecisions[i].store(other.robotsDecisions[i]);
        }
    }
};
using DecisionsStorePtr = std::shared_ptr<DecisionsStore>;
} // messaging
// phoenixpp

#endif //ROBOTS_DECISION_H
