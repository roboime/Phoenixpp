//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_OUTPUT_H
#define ROBOTS_OUTPUT_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsOutput {
};
class RobotsOutputWrapper : public Message{
public:
    void forwardTo(RobotsOutputListener *listener) override;
    RobotsOutput getRobotsOutput() const {return robotsOutput;}
private:
    RobotsOutput robotsOutput;
};
using RobotsOutputWrapperPtr = std::shared_ptr<RobotsOutputWrapper>;
using RobotsOutputPtr = std::shared_ptr<boost::atomic<RobotsOutput>>;
} // messaging
} // phoenixpp

#endif //ROBOTS_OUTPUT_H
