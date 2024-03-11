#include "test_vision.h"
#include <random>

TestVision::TestVision(atomic<bool>& stop, double fps) : BaseComponent("testvision", stop, fps) {
    message.field.field_length = 0;
}

void TestVision::start(){
}

Environment TestVision::update(Environment message){
    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<double> dist(0,1);

    Environment environment;
    environment.ball.x = dist(rng);
    environment.ball.y = dist(rng);
    environment.field.field_length = dist(rng);
    environment.field.field_width = dist(rng);
    return environment;
}
TestVision::~TestVision(){
    //BaseComponent::~BaseComponent();
}
