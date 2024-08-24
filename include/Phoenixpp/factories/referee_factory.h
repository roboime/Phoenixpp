//
// Created by ebert on 7/18/2024.
//

#ifndef REFEREE_FACTORY_H
#define REFEREE_FACTORY_H

#include "agent_factory.h"

namespace phoenixpp {
namespace factories {

class RefereeFactory : public AgentFactory {
public:
    ~RefereeFactory() override = default;
    core::AgentPtr createAgent(const std::string &implementation, const int &fps) override;
};

} // factories
} // phoenixpp

#endif //REFEREE_FACTORY_H
