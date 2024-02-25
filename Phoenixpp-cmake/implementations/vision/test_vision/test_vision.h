#ifndef TEST_VISION_H
#define TEST_VISION_H

#include <mutex>
#include <atomic>
#include <thread>
#include "../../../utils/components/base_component.h"
#include "../../../utils/messages/environment.h"

class TestVision : public BaseComponent<Environment> {
public:
    TestVision(std::atomic<bool>& stop, double fps);
    Environment update() override;
    void start() override;
    ~TestVision(){};
};

#endif // TEST_VISION_H
