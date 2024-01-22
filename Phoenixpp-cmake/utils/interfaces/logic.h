#ifndef LOGIC_H
#define LOGIC_H
#include <string>
#include <memory>
#include <any>
#include "vision.h"
#include "../structs/robot_commands.h"

class Logic{
public:
    virtual void startLogic() = 0;
    virtual RobotCommands getRobotCommands() = 0;
    virtual void setVision(std::shared_ptr<Vision> newVision) = 0;
    virtual void setParameter(std::string key, std::any value) = 0;
    virtual ~Logic() {}
};

#endif // LOGIC_H
