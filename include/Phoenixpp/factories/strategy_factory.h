//
// Created by ebert on 7/23/2024.
//

#ifndef STRATEGY_FACTORY_H
#define STRATEGY_FACTORY_H

#include <Phoenixpp/ai/strategy.h>

#include "agent_factory.h"

namespace phoenixpp {
namespace factories {

class StrategyFactory final : public AgentFactory {
public:
    explicit StrategyFactory(std::string type);
    ~StrategyFactory() override = default;
    core::AgentPtr createAgent(const std::string &implementation) override;
private:
    std::shared_ptr<ai::Strategy> _createAgent(const std::string &implementation);
    std::string type;
    messaging::EnvironmentPtr environment;
    messaging::FoulsPtr fouls;
    messaging::RobotsFeedbackPtr robotsFeedback;
};

} // factories
} // phoenixpp

#endif //STRATEGY_FACTORY_H
