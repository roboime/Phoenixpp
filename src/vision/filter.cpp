//
// Created by ebert on 8/8/2024.
//

#include "Phoenixpp/vision/filter.h"

namespace phoenixpp {
namespace vision {
messaging::Environment Filter::execute(messaging::RawEnvironment &rawEnv) {
    messaging::Environment env;
    for(int i = 0; i < rawEnv.balls.size(); i++) {
        env.balls[i].position = rawEnv.balls[i].position;
        env.balls[i].radius = rawEnv.balls[i].radius;
        env.balls[i].z = rawEnv.balls[i].z;
    }
    for(int i = 0; i < rawEnv.robots.size(); i++) {
        env.robots[i].position = rawEnv.robots[i].position;
        env.robots[i].id = rawEnv.robots[i].id;
        env.robots[i].radius = rawEnv.robots[i].radius;
        env.robots[i].height = rawEnv.robots[i].height;
        env.robots[i].orientation = rawEnv.robots[i].orientation;
        env.robots[i].kickerDistance = rawEnv.robots[i].kickerDistance;
    }
    env.field = rawEnv.field;
    env.received = rawEnv.received;
    return env;
}
} // vision
} // phoenixpp