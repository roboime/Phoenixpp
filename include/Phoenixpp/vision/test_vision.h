//
// Created by ebert on 7/23/2024.
//

#ifndef TEST_VISION_H
#define TEST_VISION_H
#include "vision.h"

namespace phoenixpp {
namespace vision {

class TestVision : public Vision {
public:
    TestVision() = default;
    ~TestVision() override = default;
    void execute() override;
};

} // vision
} // phoenixpp

#endif //TEST_VISION_H
