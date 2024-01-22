#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include <string>
#include <memory>
#include "logic.h"

class Communicator{
public:
    virtual void startCommunicator() = 0;
    virtual void setLogic(std::string side, std::shared_ptr<Logic> newLogic) = 0; // "blue", "yellow"
    virtual ~Communicator() {}
};

#endif // COMMUNICATOR_H
