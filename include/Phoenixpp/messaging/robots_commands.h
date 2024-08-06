//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_COMMANDS_H
#define ROBOTS_COMMANDS_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsCommands {

};
class RobotsCommandsWrapper : public Message {
public:
    void forwardTo(RobotsCommandsListener *listener) override;
    RobotsCommands getRobotsCommands() const {return robotsCommands;}
private:
    RobotsCommands robotsCommands;
};
using RobotsCommandsWrapperPtr = std::shared_ptr<RobotsCommandsWrapper>;
using RobotsCommandsPtr = std::shared_ptr<std::atomic<RobotsCommands>>;
} // messaging
} // phoenixpp

#endif //ROBOTS_COMMANDS_H
