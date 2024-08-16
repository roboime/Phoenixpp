//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_PATH_H
#define ROBOTS_PATH_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsPath : Message{
    void forwardTo(RobotsPathListener *listener) override;
    void store(const RobotsPath& other){}
};
using RobotsPathPtr = std::shared_ptr<RobotsPath>;
} // messaging
} // phoenixpp

#endif //ROBOTS_PATH_H
