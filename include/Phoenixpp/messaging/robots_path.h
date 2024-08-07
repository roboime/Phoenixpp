//
// Created by ebert on 6/1/2024.
//

#ifndef ROBOTS_PATH_H
#define ROBOTS_PATH_H

#include "message.h"

namespace phoenixpp {
namespace messaging {
struct RobotsPath {
};
class RobotsPathWrapper : public Message{
public:
    void forwardTo(RobotsPathListener *listener) override;
    RobotsPath getRobotsPath() const {return robotsPath;}
private:
    RobotsPath robotsPath;
};
using RobotsPathWrapperPtr = std::shared_ptr<RobotsPathWrapper>;
using RobotsPathPtr = std::shared_ptr<boost::atomic<RobotsPath>>;
} // messaging
} // phoenixpp

#endif //ROBOTS_PATH_H
