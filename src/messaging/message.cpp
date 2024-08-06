//
// Created by ebert on 7/17/2024.
//

#include "Phoenixpp/messaging/message.h"
#include "Phoenixpp/messaging/listener.h"

#include <iostream>

namespace phoenixpp {
namespace messaging {

void Message::logWarning(const std::string& listener) {
    std::cerr << "Warning: " << listener << " listener not overridden!";
}
void Message::forwardTo(EnvironmentListener *listener) {
    logWarning("Environment");
}
void Message::forwardTo(FoulsListener *listener) {
    logWarning("Fouls");
}
void Message::forwardTo(RobotsDecisionListener *listener) {
    logWarning("RobotsDecision");
}
void Message::forwardTo(RobotsFeedbackListener *listener) {
    logWarning("RobotsFeedback");
}
void Message::forwardTo(RobotsCommandsListener *listener) {
    logWarning("RobotsCommands");
}
void Message::forwardTo(RobotsPathListener *listener) {
    logWarning("RobotsPath");
}
void Message::forwardTo(RobotsOutputListener *listener) {
    logWarning("RobotsOutput");
}

void EnvironmentWrapper::forwardTo(EnvironmentListener *listener) {
    listener->updateEnvironment(this);
}

void FoulsWrapper::forwardTo(FoulsListener *listener) {
    listener->updateFouls(this);
}

void RobotsFeedbackWrapper::forwardTo(RobotsFeedbackListener *listener) {
    listener->updateRobotsFeedback(this);
}

void RobotsDecisionWrapper::forwardTo(RobotsDecisionListener *listener) {
    listener->updateRobotsDecision(this);
}

void RobotsPathWrapper::forwardTo(RobotsPathListener *listener) {
    listener->updateRobotsPath(this);
}

void RobotsCommandsWrapper::forwardTo(RobotsCommandsListener *listener) {
    listener->updateRobotsCommands(this);
}

void RobotsOutputWrapper::forwardTo(RobotsOutputListener *listener) {
    listener->updateRobotsOutput(this);
}

} // messaging
} // phoenixpp