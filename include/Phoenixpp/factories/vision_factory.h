//
// Created by ebert on 7/18/2024.
//

#ifndef VISION_FACTORY_H
#define VISION_FACTORY_H

#include "Phoenixpp/factories/agent_factory.h"

namespace phoenixpp {
namespace factories {

class VisionFactory : public AgentFactory{
public:
    ~VisionFactory() override = default;
    core::AgentPtr createAgent(const std::string &implementation) override;
};

} // vision
} // phoenixpp

#endif //VISION_FACTORY_H
