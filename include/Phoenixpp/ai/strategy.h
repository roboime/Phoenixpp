//
// Created by ebert on 7/22/2024.
//

#ifndef STRATEGY_H
#define STRATEGY_H

#include "Phoenixpp/core/agent.h"
#include "Phoenixpp/messaging/message.h"
#include "Phoenixpp/messaging/environment.h"

namespace phoenixpp {
namespace ai {
using std::string;

class Strategy : public core::Agent{
public:
    explicit Strategy(const string &type);
    ~Strategy() override;
    void execute() override;
    messaging::ListenerPtr createListener(const string &type) override;
    void setEnvironment(const messaging::EnvironmentPtr &env) {environment = env;}
    void setFouls(const messaging::FoulsPtr &f) {fouls = f;}
    void setRobotsFeedback(const messaging::RobotsFeedbackPtr &rf) {robotsFeedback = rf;}
protected:
    messaging::EnvironmentPtr environment;
    messaging::FoulsPtr fouls;
    messaging::RobotsFeedbackPtr robotsFeedback;
};

} // ai
} // phoenix

#endif //STRATEGY_H
