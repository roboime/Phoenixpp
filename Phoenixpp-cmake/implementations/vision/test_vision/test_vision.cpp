#include "test_vision.h"
#include <random>

TestVision::TestVision(atomic<bool>& stop) : stop(stop) {
    environment.field_lenght = 0;
}

void TestVision::startReceiving() {
    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<double> dist(0,1);
    while (!stop.load()) {
        Environment environment;
        environment.ball.x = dist(rng);
        environment.ball.y = dist(rng);
        environment.field_lenght = dist(rng);
        environment.field_width = dist(rng);
        {
            lock_guard<mutex> lock(mtx);
            this->environment = environment;
        }
        this_thread::sleep_for(chrono::milliseconds(60));
    }
}

Environment TestVision::getEnvironment() {
    lock_guard<mutex> lock(mtx);
    return environment;
}

void TestVision::setFilter(string filter) {
    // Implementation for setFilter
}

TestVision::~TestVision() {
    // Destructor implementation
}
