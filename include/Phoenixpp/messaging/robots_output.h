//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_OUTPUT_H
#define ROBOTS_OUTPUT_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsOutput : Message{
    void forwardTo(RobotsOutputListener *listener) override;
    void store(const RobotsOutput& other){}
};
using RobotsOutputPtr = std::shared_ptr<RobotsOutput>;
} // messaging
} // phoenixpp

#endif //ROBOTS_OUTPUT_H
