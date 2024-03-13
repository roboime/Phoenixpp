#ifndef ROBOTCOMMANDS_H
#define ROBOTCOMMANDS_H

#include <vector>
#include <cstdint>

struct RobotCommand {
    uint32_t id;
    float kickspeedx;
    float kickspeedz;
    float veltangent;
    float velnormal;
    float velangular;
    bool spinner;
    bool wheelsspeed;
    float wheel1;
    float wheel2;
    float wheel3;
    float wheel4;
};

struct RobotCommands {
    double timestamp;
    bool isteamyellow;
    std::vector<RobotCommand> robotCommands;
};

#endif // ROBOTCOMMANDS_H
