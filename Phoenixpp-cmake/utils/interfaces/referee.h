#ifndef REFEREE_H
#define REFEREE_H
#include "../structs/referee_commands.h"

class Referee{
public:
    virtual void startReceiving() = 0;
    virtual RefereeCommands getRefereeCommands() = 0;
    virtual ~Referee() {}
};

#endif // REFEREE_H
