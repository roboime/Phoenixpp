//
// Created by ebert on 7/17/2024.
//

#ifndef AGENT_FACTORY_H
#define AGENT_FACTORY_H
#include "Phoenixpp/core/agent.h"

namespace phoenixpp {
namespace factories {

class AgentFactory {
public:
    virtual ~AgentFactory() = default;
    virtual core::AgentPtr createAgent(const std::string &implementation, const int &fps) = 0;
};

} // core
} // phoenixpp

#endif //AGENT_FACTORY_H
