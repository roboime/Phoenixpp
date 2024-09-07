//
// Created by ebert on 7/18/2024.
//

#ifndef VISION_H
#define VISION_H

#include <messages_robocup_ssl_wrapper.pb.h>

#include "filter.h"
#include "Phoenixpp/core/agent.h"
#include "Phoenixpp/messaging/environment.h"

namespace phoenixpp {
namespace vision {

class Vision : public core::Agent{
public:
    explicit Vision(const int &fps);
    ~Vision() override;
    void execute() override;
protected:
    void processPacket(SSL_WrapperPacket &packet);
    void distributeEnvironment(const messaging::Environment &env);
    messaging::RawEnvironment rawEnv;
    FilterPtr filter;
};

} // vision
} // phoenixpp

#endif //VISION_H
