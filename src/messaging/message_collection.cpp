//
// Created by ebert on 8/6/2024.
//

#include "Phoenixpp/messaging/message_collection.h"

#include <Phoenixpp/factories/listener_factory.h>

namespace phoenixpp {
namespace messaging {

MessageCollection::MessageCollection() :
    environment(std::make_shared<std::atomic<Environment>>()),
    fouls(std::make_shared<std::atomic<Fouls>>()),
    robotsFeedback(std::make_shared<std::atomic<RobotsFeedback>>()),
    blueDecision(std::make_shared<std::atomic<RobotsDecision>>()),
    yellowDecision(std::make_shared<std::atomic<RobotsDecision>>()),
    robotsPath(std::make_shared<std::atomic<RobotsPath>>()),
    robotsCommands(std::make_shared<std::atomic<RobotsCommands>>()),
    robotsOutput(std::make_shared<std::atomic<RobotsOutput>>()){}

ListenerPtr MessageCollection::createListener(const std::string &key) {
    if(key == "vision") {
        return factories::ListenerFactory::createListener(environment);
    }
    if(key == "referee") {
        return factories::ListenerFactory::createListener(fouls);
    }
    if(key == "feedback") {
        return factories::ListenerFactory::createListener(robotsFeedback);
    }
    if(key == "blue_ai") {
        return factories::ListenerFactory::createListener(blueDecision);
    }
    if(key == "yellow_ai") {
        return factories::ListenerFactory::createListener(yellowDecision);
    }
    if(key == "path_planner") {
        return factories::ListenerFactory::createListener(robotsPath);
    }
    if(key == "controller") {
        return factories::ListenerFactory::createListener(robotsCommands);
    }
    if(key == "communicator") {
        return factories::ListenerFactory::createListener(robotsOutput);
    }
    return nullptr;
}

} // messaging
} // phoenixpp