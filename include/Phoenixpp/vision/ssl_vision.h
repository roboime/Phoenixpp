//
// Created by ebert on 7/18/2024.
//

#ifndef SSL_VISION_H
#define SSL_VISION_H

#include <queue>
#include "Phoenixpp/io/udp_handler.h"
#include "vision.h"

namespace phoenixpp {
namespace vision {
constexpr int NUM_CAMERAS = 4;
class SSLVision : public Vision{
public:
    SSLVision();
    ~SSLVision() override;
    void execute() override;
private:
    std::shared_ptr<io::UdpHandler> udpReceiver;
    std::queue<std::pair<char*,int>> bufferQueue;
    std::mutex bufferQueue_mtx;
};

} // vision
} // phoenixpp

#endif //SSL_VISION_H
