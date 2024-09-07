//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/vision/ssl_vision.h"
#include "Phoenixpp/io/udp_handler.h"
#include <iostream>
#include <memory>
#include <messages_robocup_ssl_wrapper.pb.h>

namespace phoenixpp {
namespace vision {
using std::cout, std::endl;

SSLVision::SSLVision(const int &fps) : Vision(fps){
    //temporary values
    QHostAddress multicastAddress("224.5.23.2");
    unsigned short port = 10020;
    int packetMaxSize = 2048;
    int ringBufferSize = 32;
    ringBuffer.set_capacity(ringBufferSize);
    io::UdpData data{
        ringBuffer,
        ringBuffer_mtx,
        multicastAddress,
        port,
        packetMaxSize
    };
    udpReceiver = std::make_shared<io::UdpHandler>(data);
}

void SSLVision::execute() {
    SSL_WrapperPacket packet;
    std::unique_lock lock(ringBuffer_mtx, std::defer_lock);
    bool ok = true;
    unsigned int frameNumber = 0;
    unsigned int id = 0;
    lock.lock();
    if(ringBuffer.size() <= NUM_CAMERAS) {
        ok = false;
    }
    while(ok && id < NUM_CAMERAS) {
        packet.MergeFromString(ringBuffer.front());
        if(!packet.has_detection()) {
            ok = false;
            continue;
        }
        SSL_DetectionFrame detection = packet.detection();
        if(detection.camera_id() != id) {
            ok= false;
            while(!ringBuffer.empty() &&
                (!packet.has_detection() || packet.detection().camera_id() != 0)) {
                ringBuffer.pop_front();
                packet.MergeFromString(ringBuffer.front());
            }
            continue;
        }
        if(id == 0) frameNumber = detection.frame_number();
        else if(detection.frame_number() != frameNumber) {
            ok = false;
            continue;
        }
        ringBuffer.pop_front();
        id++;
    }
    if(!ok) {
        return;
    }
    lock.unlock();
    processPacket(packet);
    rawEnv.received = udpReceiver->getReceived();
    Vision::execute();
}

SSLVision::~SSLVision() {
    std::cout << "Destroying SSL Vision" << std::endl;
}

} // vision
} // phoenixpp