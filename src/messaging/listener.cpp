#include "Phoenixpp/messaging/listener.h"

#include <memory>

namespace phoenixpp {
namespace messaging {

EnvironmentListener::EnvironmentListener(const EnvironmentPtr &env) : environment(env) {}

void EnvironmentListener::update(MessagePtr const message) {
    message->forwardTo(this);
}

void EnvironmentListener::updateEnvironment(Environment *newEnvironment) const{
    environment->store(*newEnvironment);
}

FoulsListener::FoulsListener(const FoulsPtr &fouls) : fouls(fouls) {}

void FoulsListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void FoulsListener::updateFouls(Fouls * newFouls) const{
    fouls->store(*newFouls);
}

RobotsFeedbackListener::RobotsFeedbackListener(const RobotsFeedbackPtr &feedback) : robotsFeedback(feedback) {}

void RobotsFeedbackListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsFeedbackListener::updateRobotsFeedback(RobotsFeedback *newFeedback) const{
    robotsFeedback->store(*newFeedback);
}

RobotsDecisionListener::RobotsDecisionListener(const RobotsDecisionPtr &decision) : robotsDecision(decision) {}

void RobotsDecisionListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsDecisionListener::updateRobotsDecision(RobotsDecision *newDecision) const{
    robotsDecision->store(*newDecision);
}

RobotsPathListener::RobotsPathListener(const RobotsPathPtr &path) : robotsPath(path) {}

void RobotsPathListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsPathListener::updateRobotsPath(RobotsPath *newPath) const {
    robotsPath->store(*newPath);
}

RobotsCommandsListener::RobotsCommandsListener(const RobotsCommandsPtr &commands) : robotsCommands(commands) {}

void RobotsCommandsListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsCommandsListener::updateRobotsCommands(RobotsCommands *newCommands) const{
    robotsCommands->store(*newCommands);
}

RobotsOutputListener::RobotsOutputListener(const RobotsOutputPtr &output) : robotsOutput(output) {}

void RobotsOutputListener::update(MessagePtr message) {
    message->forwardTo(this);
}

void RobotsOutputListener::updateRobotsOutput(RobotsOutput *newOutput) const{
    robotsOutput->store(*newOutput);
}

} // messaging
} // phoenixpp
