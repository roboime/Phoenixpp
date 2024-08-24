//
// Created by ebert on 7/23/2024.
//

#include "Phoenixpp/factories/strategy_factory.h"

#include <memory>
#include <utility>
#include <Phoenixpp/ai/strategy.h>
#include <Phoenixpp/ai/stp/stp.h>

namespace phoenixpp {
namespace factories {

StrategyFactory::StrategyFactory(std::string type) : type(std::move(type)),
    environment(std::make_shared<messaging::Environment>()),
    fouls(std::make_shared<messaging::Fouls>()),
    robotsFeedback(std::make_shared<messaging::RobotsFeedback>()){}

std::shared_ptr<ai::Strategy> StrategyFactory::_createAgent(const std::string &implementation, const int &fps) {
    if(implementation == "stp"){
        return std::make_shared<ai::STP>(type, fps);
    }
    return std::make_shared<ai::Strategy>(type, fps);
}
core::AgentPtr StrategyFactory::createAgent(const std::string &implementation, const int &fps) {
    std::shared_ptr<ai::Strategy> agent = _createAgent(implementation, fps);
    agent->setEnvironment(environment);
    agent->setFouls(fouls);
    agent->setRobotsFeedback(robotsFeedback);
    return agent;
}

} // factories
} // phoenixpp