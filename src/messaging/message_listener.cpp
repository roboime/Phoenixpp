//
// Created by ebert on 6/1/2024.
//

#include "Phoenixpp/messaging/message_listener.h"


namespace roboime::messaging {

void MessageListener::overrideWarning(const std::string& messageType){
    std::cerr << "Visit to " << messageType <<  "message not overriden!\n";
}
void MessageListener::update(const std::shared_ptr<Message>& message){
    message->accept(this);
}
void MessageListener::updateVisit(Environment){
    overrideWarning("Environment");
}
void MessageListener::updateVisit(Fouls){
    overrideWarning("Fouls");
}
void MessageListener::updateVisit(RobotsFeedback){
    overrideWarning("RobotsFeedback");
}
void MessageListener::updateVisit(RobotsDecision){
    overrideWarning("RobotsDecision");
}
void MessageListener::updateVisit(RobotsPath){
    overrideWarning("RobotsPath");
}
void MessageListener::updateVisit(RobotsCommands){
    overrideWarning("RobotsCommands");
}
void MessageListener::updateVisit(RobotsOutput){
    overrideWarning("RobotsOutput");
}
MessageListener::~MessageListener() = default;

} // messaging
// roboime