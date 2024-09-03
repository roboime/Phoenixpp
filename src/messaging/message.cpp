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
void Message::forwardTo(DecisionsStoreListener *listener) {
    logWarning("DecisionsStore");
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

void Environment::forwardTo(EnvironmentListener *listener) {
    listener->updateEnvironment(this);
}

void Fouls::forwardTo(FoulsListener *listener) {
    listener->updateFouls(this);
}

void RobotsFeedback::forwardTo(RobotsFeedbackListener *listener) {
    listener->updateRobotsFeedback(this);
}

void DecisionsStore::forwardTo(DecisionsStoreListener *listener) {
    listener->updateDecisionsStore(this);
}

void RobotsPath::forwardTo(RobotsPathListener *listener) {
    listener->updateRobotsPath(this);
}

void RobotsCommands::forwardTo(RobotsCommandsListener *listener) {
    listener->updateRobotsCommands(this);
}

void RobotsOutput::forwardTo(RobotsOutputListener *listener) {
    listener->updateRobotsOutput(this);
}

} // messaging
} // phoenixpp