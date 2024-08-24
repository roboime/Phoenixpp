//
// Created by ebert on 7/18/2024.
//

#ifndef REFEREE_H
#define REFEREE_H
#include <Phoenixpp/core/agent.h>

namespace phoenixpp {
namespace referee {

class Referee : public core::Agent {
public:
    Referee(const int &fps);
    ~Referee() override = default;
    void execute() override;
};

} // referee
} // phoenixpp

#endif //REFEREE_H
