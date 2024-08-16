//
// Created by ebert on 8/8/2024.
//

#include "Phoenixpp/vision/filter.h"

namespace phoenixpp {
namespace vision {
messaging::Environment Filter::execute(messaging::RawEnvironment &rawEnv) {
    messaging::Environment env;
    env.received = rawEnv.received;
    for(int i=0;i<messaging::MAX_BALLS;i++) {
        env.balls[i].positionX.store(rawEnv.balls[i].positionX);
        env.balls[i].positionY.store(rawEnv.balls[i].positionY);
        env.balls[i].radius.store(rawEnv.balls[i].radius);
        env.balls[i].z.store(rawEnv.balls[i].z);
        env.balls[i].valid.store(rawEnv.balls[i].valid);
    }
    for (int i = 0; i < messaging::MAX_ROBOTS; i++) {
        env.robots[i].positionX.store(rawEnv.robots[i].positionX);
        env.robots[i].positionY.store(rawEnv.robots[i].positionY);
        env.robots[i].id.store(rawEnv.robots[i].id);
        env.robots[i].radius.store(rawEnv.robots[i].radius);
        env.robots[i].height.store(rawEnv.robots[i].height);
        env.robots[i].orientation.store(rawEnv.robots[i].orientation);
        env.robots[i].kickerDistance.store(rawEnv.robots[i].kickerDistance);
        env.robots[i].color.store(rawEnv.robots[i].color);
        env.robots[i].valid.store(rawEnv.robots[i].valid);
    }
    env.field.store(rawEnv.field);
    return env;
}
} // vision
} // phoenixpp