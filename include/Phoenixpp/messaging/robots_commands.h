//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_COMMANDS_H
#define ROBOTS_COMMANDS_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsCommands : Message{
    void forwardTo(RobotsCommandsListener *listener) override;
    void store(const RobotsCommands& other){}
};
using RobotsCommandsPtr = std::shared_ptr<RobotsCommands>;
} // messaging
} // phoenixpp

#endif //ROBOTS_COMMANDS_H
