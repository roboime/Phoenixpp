#include "test_vision.h"
#include <random>

TestVision::TestVision(atomic<bool>& stop, double fps) : BaseComponent("testvision", stop, fps) {
    message.field_lenght = 0;
}

void TestVision::start(){
}

Environment TestVision::update(){
    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<double> dist(0,1);

    Environment environment;
    environment.ball.x = dist(rng);
    environment.ball.y = dist(rng);
    environment.field_lenght = dist(rng);
    environment.field_width = dist(rng);
    return environment;
}