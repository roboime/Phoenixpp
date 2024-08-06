//
// Created by ebert on 7/18/2024.
//

#ifndef AGENT_FACTORY_REGISTRY_H
#define AGENT_FACTORY_REGISTRY_H
#include "Phoenixpp/factories/agent_factory.h"
#include <unordered_map>
#include <memory>
#include <string>
namespace phoenixpp {
namespace factories {

class AgentFactoryRegistry {
public:
    AgentFactoryRegistry();
    std::shared_ptr<AgentFactory> getFactory(const std::string &key);
private:
    std::unordered_map<std::string, std::shared_ptr<AgentFactory>> agentFactoryMap;
};

} // factories
} // phoenixpp

#endif //AGENT_FACTORY_REGISTRY_H
