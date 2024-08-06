//
// Created by ebert on 7/18/2024.
//

#ifndef SSL_VISION_H
#define SSL_VISION_H

#include "vision.h"

namespace phoenixpp {
namespace vision {

class SSLVision : public Vision{
public:
    SSLVision();
    ~SSLVision() override = default;
    void execute() override;
};

} // vision
} // phoenixpp

#endif //SSL_VISION_H
