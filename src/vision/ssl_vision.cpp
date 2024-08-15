//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/vision/ssl_vision.h"
#include "Phoenixpp/io/udp_handler.h"
#include <iostream>
#include <memory>

namespace phoenixpp {
namespace vision {
using std::cout, std::endl;

SSLVision::SSLVision() {
    std::string multicastAddress = "224.5.23.2";
    unsigned short port = 10020;
    int bufferSizeMax = 2048;
    int queueSizeMax = 4;
    io::UdpData data{
        bufferQueue,
        bufferQueue_mtx,
        multicastAddress,
        port,
        bufferSizeMax,
        queueSizeMax
    };
    udpReceiver = std::make_shared<io::UdpHandler>(data);
}

void SSLVision::execute() {
    std::unique_lock lock(bufferQueue_mtx);
    for(int i = 0; i < NUM_CAMERAS; i++) {
        if(bufferQueue.empty()){
            continue;
        }
        auto [buffer_ptr, size] = bufferQueue.front();
        bufferQueue.pop();
        processPacket(buffer_ptr, size);
        delete[] buffer_ptr;
    }
    lock.unlock();
    rawEnv.received = udpReceiver->getReceived();
    Vision::execute();
}

SSLVision::~SSLVision() {
    std::cout << "Destroying SSL Vision" << std::endl;
    std::unique_lock lock(bufferQueue_mtx);
    while(!bufferQueue.empty()) {
        delete[] bufferQueue.front().first;
        bufferQueue.pop();
    }
    lock.unlock();
}

} // vision
} // phoenixpp