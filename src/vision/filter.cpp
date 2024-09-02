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
        env.blueRobots[i].positionX.store(rawEnv.blueRobots[i].positionX);
        env.blueRobots[i].positionY.store(rawEnv.blueRobots[i].positionY);
        env.blueRobots[i].id.store(rawEnv.blueRobots[i].id);
        env.blueRobots[i].radius.store(rawEnv.blueRobots[i].radius);
        env.blueRobots[i].height.store(rawEnv.blueRobots[i].height);
        env.blueRobots[i].orientation.store(rawEnv.blueRobots[i].orientation);
        env.blueRobots[i].kickerDistance.store(rawEnv.blueRobots[i].kickerDistance);
        env.blueRobots[i].color.store(rawEnv.blueRobots[i].color);
        env.blueRobots[i].valid.store(rawEnv.blueRobots[i].valid);
    }

    for (int i = 0; i < messaging::MAX_ROBOTS; i++) {
        env.yellowRobots[i].positionX.store(rawEnv.yellowRobots[i].positionX);
        env.yellowRobots[i].positionY.store(rawEnv.yellowRobots[i].positionY);
        env.yellowRobots[i].id.store(rawEnv.yellowRobots[i].id);
        env.yellowRobots[i].radius.store(rawEnv.yellowRobots[i].radius);
        env.yellowRobots[i].height.store(rawEnv.yellowRobots[i].height);
        env.yellowRobots[i].orientation.store(rawEnv.yellowRobots[i].orientation);
        env.yellowRobots[i].kickerDistance.store(rawEnv.yellowRobots[i].kickerDistance);
        env.yellowRobots[i].color.store(rawEnv.yellowRobots[i].color);
        env.yellowRobots[i].valid.store(rawEnv.yellowRobots[i].valid);
    }
    env.field.store(rawEnv.field);
    return env;
}
} // vision
} // phoenixpp