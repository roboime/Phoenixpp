#ifndef ROBOTCOMMANDS_H
#define ROBOTCOMMANDS_H

#include <vector>
#include <cstdint>

struct RobotCommand {
    uint32_t id = 0;
    float kickspeedx = 0.0f;
    float kickspeedz = 0.0f;
    float veltangent = 0.0f;
    float velnormal = 0.0f;
    float velangular = 0.0f;
    bool spinner = false;
    bool wheelsspeed = false;
    float wheel1 = 0.0f;
    float wheel2 = 0.0f;
    float wheel3 = 0.0f;
    float wheel4 = 0.0f;
};

struct RobotCommands {
    double timestamp = 0.0;
    bool isteamyellow = false;
    std::vector<RobotCommand> robotCommands;
};


struct TransmittedCommands{
    bool transmitted;
};

#endif // ROBOTCOMMANDS_H
