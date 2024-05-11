#ifndef REAL_GAME_VISION_H
#define REAL_GAME_VISION_H

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <iostream>
#include <memory>
#include <queue>
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/NObserver.h"
#include "Poco/Observer.h"
#include "../../../../../proto/protobuf_files.h"
#include "../../../../utils/udp_receiver.h"
#include "../../../base_component.h"
#include "../../../messages/raw_environment.h"

class RealGameVision : public TBaseComponent<RawEnvironment>{
private:
    shared_ptr<UdpReceiver> udpReceiver;
    queue<pair<char*,int>> bufferQueue;
    mutex bufferQueue_mtx;
public:
    RealGameVision(std::atomic<bool>& stop, double fps);
    RawEnvironment update(RawEnvironment message) override;
    void start() override;
    ~RealGameVision();
};

#endif // REAL_GAME_VISION_H
