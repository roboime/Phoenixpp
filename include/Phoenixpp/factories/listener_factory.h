//
// Created by ebert on 7/22/2024.
//

#ifndef LISTENER_FACTORY_H
#define LISTENER_FACTORY_H

#include <Phoenixpp/messaging/listener.h>
#include <Phoenixpp/messaging/environment.h>
#include <memory>
namespace phoenixpp {
namespace factories {

class ListenerFactory {

public:
    static messaging::ListenerPtr createListener(messaging::EnvironmentPtr &environment);
    static messaging::ListenerPtr createListener(messaging::FoulsPtr &fouls);
    static messaging::ListenerPtr createListener(messaging::RobotsFeedbackPtr &robotsFeedback);
    static messaging::ListenerPtr createListener(messaging::DecisionsStorePtr &decisionsStore);
    static messaging::ListenerPtr createListener(messaging::RobotsPathPtr &robotsPath);
    static messaging::ListenerPtr createListener(messaging::RobotsCommandsPtr &robotsCommands);
    static messaging::ListenerPtr createListener(messaging::RobotsOutputPtr &robotsOutput);
};

} // factories
} // phoenixpp

#endif //LISTENER_FACTORY_H
