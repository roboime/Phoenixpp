#include "Phoenixpp/messaging/listener.h"

#include <memory>
#include <atomic>

namespace phoenixpp {
namespace messaging {

EnvironmentListener::EnvironmentListener(const EnvironmentPtr &env) : environment(env) {}

void EnvironmentListener::update(MessagePtr const message) {
    message->forwardTo(this);
}

void EnvironmentListener::updateEnvironment(EnvironmentWrapper *newEnvironment) const{
    environment->store(newEnvironment->getEnvironment());
}

FoulsListener::FoulsListener(const FoulsPtr &fouls) : fouls(fouls) {}

void FoulsListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void FoulsListener::updateFouls(FoulsWrapper * newFouls) const{
    fouls->store(newFouls->getFouls());
}

RobotsFeedbackListener::RobotsFeedbackListener(const RobotsFeedbackPtr &feedback) : robotsFeedback(feedback) {}

void RobotsFeedbackListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsFeedbackListener::updateRobotsFeedback(RobotsFeedbackWrapper *newFeedback) const{
    robotsFeedback->store(newFeedback->getRobotsFeedback());
}

RobotsDecisionListener::RobotsDecisionListener(const RobotsDecisionPtr &decision) : robotsDecision(decision) {}

void RobotsDecisionListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsDecisionListener::updateRobotsDecision(RobotsDecisionWrapper *newDecision) const{
    robotsDecision->store(newDecision->getRobotsDecision());
}

RobotsPathListener::RobotsPathListener(const RobotsPathPtr &path) : robotsPath(path) {}

void RobotsPathListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsPathListener::updateRobotsPath(RobotsPathWrapper *newPath) const {
    robotsPath->store(newPath->getRobotsPath());
}

RobotsCommandsListener::RobotsCommandsListener(const RobotsCommandsPtr &commands) : robotsCommands(commands) {}

void RobotsCommandsListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsCommandsListener::updateRobotsCommands(RobotsCommandsWrapper *newCommands) const{
    robotsCommands->store(newCommands->getRobotsCommands());
}

RobotsOutputListener::RobotsOutputListener(const RobotsOutputPtr &output) : robotsOutput(output) {}

void RobotsOutputListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsOutputListener::updateRobotsOutput(RobotsOutputWrapper *newOutput) const{
    robotsOutput->store(newOutput->getRobotsOutput());
}

} // messaging
} // phoenixpp
