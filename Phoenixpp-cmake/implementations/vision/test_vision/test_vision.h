#ifndef TEST_VISION_H
#define TEST_VISION_H

#include <mutex>
#include <atomic>
#include <thread>
#include "../../../utils/interfaces/vision.h"
#include "../../../utils/structs/environment.h"

class TestVision : public Vision {
private:
    std::mutex mtx;
    Environment environment;
    std::atomic<bool>& stop;

public:
    TestVision(std::atomic<bool>& stop);
    void startReceiving() override;
    Environment getEnvironment() override;
    void setFilter(std::string filter) override;
    ~TestVision();
};

#endif // TEST_VISION_H
