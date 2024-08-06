//
// Created by ebert on 7/18/2024.
//

#ifndef VISION_H
#define VISION_H

#include "Phoenixpp/core/agent.h"

namespace phoenixpp {
namespace vision {

class Vision : public core::Agent{
public:
    Vision();
    ~Vision() override;
    void execute() override;
protected:
    messaging::Environment environment;
    void distributeEnvironment(const messaging::Environment &env);
};

} // vision
} // phoenixpp

#endif //VISION_H
