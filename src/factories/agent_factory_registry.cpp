//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/factories/agent_factory_registry.h"

#include <Phoenixpp/factories/referee_factory.h>
#include <Phoenixpp/factories/strategy_factory.h>
#include <Phoenixpp/factories/vision_factory.h>

namespace phoenixpp {
namespace factories {

AgentFactoryRegistry::AgentFactoryRegistry() {
    agentFactoryMap["vision"] = std::make_shared<VisionFactory>();
    agentFactoryMap["referee"] = std::make_shared<RefereeFactory>();
    agentFactoryMap["feedback"] = std::make_shared<RefereeFactory>();
    agentFactoryMap["blue_ai"] = std::make_shared<StrategyFactory>("blue_ai");
    agentFactoryMap["yellow_ai"] = std::make_shared<StrategyFactory>("yellow_ai");
    agentFactoryMap["path_planner"] = std::make_shared<RefereeFactory>();
    agentFactoryMap["controller"] = std::make_shared<RefereeFactory>();
    agentFactoryMap["communicator"] = std::make_shared<RefereeFactory>();
}

std::shared_ptr<AgentFactory> AgentFactoryRegistry::getFactory(const std::string &key) {
    const auto factoryIt = agentFactoryMap.find(key);
    if(factoryIt == agentFactoryMap.end()){
        throw std::invalid_argument("Agent Factory not found for key: " + key);
    }
    return factoryIt->second;
}

} // factories
} // phoenixpp