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
    environment(std::make_shared<boost::atomic<messaging::Environment>>()),
    fouls(std::make_shared<boost::atomic<messaging::Fouls>>()),
    robotsFeedback(std::make_shared<boost::atomic<messaging::RobotsFeedback>>()){}

std::shared_ptr<ai::Strategy> StrategyFactory::_createAgent(const std::string &implementation) {
    if(implementation == "stp"){
        return std::make_shared<ai::STP>(type);
    }
    return std::make_shared<ai::Strategy>(type);
}
core::AgentPtr StrategyFactory::createAgent(const std::string &implementation) {
    std::shared_ptr<ai::Strategy> agent = _createAgent(implementation);
    agent->setEnvironment(environment);
    agent->setFouls(fouls);
    agent->setRobotsFeedback(robotsFeedback);
    return agent;
}

} // factories
} // phoenixpp