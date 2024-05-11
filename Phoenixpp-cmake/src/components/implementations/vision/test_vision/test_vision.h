#ifndef TEST_VISION_H
#define TEST_VISION_H

#include <mutex>
#include <atomic>
#include <thread>
#include <random>
#include "../../../base_component.h"
#include "../../../messages/raw_environment.h"

class TestVision : public TBaseComponent<RawEnvironment> {
public:
    TestVision(std::atomic<bool>& stop, double fps);
    RawEnvironment update(RawEnvironment message) override;
    void start() override;
    ~TestVision();
};

#endif // TEST_VISION_H
