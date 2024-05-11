#include "test_vision.h"
#include <random>

TestVision::TestVision(atomic<bool>& stop, double fps) : TBaseComponent("testvision", stop, fps) {
    message.field.field_length = 0;
}

void TestVision::start(){
}

RawEnvironment TestVision::update(RawEnvironment message){
    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<double> dist(0,1);

    RawEnvironment environment;
    environment.balls[0].x = dist(rng);
    environment.balls[0].y = dist(rng);
    environment.field.field_length = dist(rng);
    environment.field.field_width = dist(rng);
    return environment;
}
TestVision::~TestVision(){
    //BaseComponent::~BaseComponent();
}
