//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/factories/vision_factory.h"
#include <Phoenixpp/vision/ssl_vision.h>
#include <Phoenixpp/vision/test_vision.h>

namespace phoenixpp {
namespace factories {

std::shared_ptr<core::Agent> VisionFactory::createAgent(const std::string &implementation) {
    if(implementation == "ssl"){
        return std::make_shared<vision::SSLVision>();
    }
    if(implementation == "test"){
        return std::make_shared<vision::TestVision>();
    }
    return std::make_shared<vision::Vision>();
}

} // vision
} // phoenixpp