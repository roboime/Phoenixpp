//
// Created by ebert on 7/22/2024.
//

#include <Phoenixpp/factories/listener_factory.h>

namespace phoenixpp {
namespace factories {

messaging::ListenerPtr ListenerFactory::createListener(messaging::EnvironmentPtr &environment) {
    return std::make_shared<messaging::EnvironmentListener>(environment);
}
messaging::ListenerPtr ListenerFactory::createListener(messaging::FoulsPtr &fouls) {
    return std::make_shared<messaging::FoulsListener>(fouls);
}
messaging::ListenerPtr ListenerFactory::createListener(messaging::RobotsFeedbackPtr &robotsFeedback) {
    return std::make_shared<messaging::RobotsFeedbackListener>(robotsFeedback);
}
messaging::ListenerPtr ListenerFactory::createListener(messaging::RobotsDecisionPtr &robotsDecision) {
    return std::make_shared<messaging::RobotsDecisionListener>(robotsDecision);
}
messaging::ListenerPtr ListenerFactory::createListener(messaging::RobotsPathPtr &robotsPath) {
    return std::make_shared<messaging::RobotsPathListener>(robotsPath);
}
messaging::ListenerPtr ListenerFactory::createListener(messaging::RobotsCommandsPtr &robotsCommands) {
    return std::make_shared<messaging::RobotsCommandsListener>(robotsCommands);
}
messaging::ListenerPtr ListenerFactory::createListener(messaging::RobotsOutputPtr &robotsOutput) {
    return std::make_shared<messaging::RobotsOutputListener>(robotsOutput);
}

} // factories
} // phoenixpp