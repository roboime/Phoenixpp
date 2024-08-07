//
// Created by ebert on 7/18/2024.
//

#include "Phoenixpp/vision/ssl_vision.h"
#include "Phoenixpp/io/udp_handler.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include <iostream>
#include <memory>

namespace phoenixpp {
namespace vision {
using std::cout, std::endl;

SSLVision::SSLVision() {
    std::string multicastAddress = "224.5.23.2";
    int port = 10020;
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
    messaging::Environment newEnv = environment;
    newEnv.ball[0].valid = true;
    newEnv.ball[0].position += std::complex<double>{1,1};
    SSL_WrapperPacket packet;
    // std::unique_lock lock(bufferQueue_mtx, std::defer_lock);
    std::pair<char*, int> buffer;
    char * buffer_ptr;
    int size;
    // for(int i = 0; i < 4; i++) {
    //     lock.lock();
    //     if(bufferQueue.empty()){
    //         continue;
    //     }
    //     buffer = bufferQueue.front(); bufferQueue.pop();
    //     // cout << "queue size: " << (int)bufferQueue.size() << endl;
    //     buffer_ptr = buffer.first;
    //     size = buffer.second;
    //     // for(int i=0;i<size;i++) cout << i << " " << (int)buffer_ptr[i] << endl;
    //     // packet.Clear();
    //     // packet.ParseFromArray(buffer_ptr, size);
    //     delete[] buffer_ptr;
    //     lock.unlock();
    //     // Process packet
    // }
    distributeEnvironment(newEnv);
}

} // vision
} // phoenixpp