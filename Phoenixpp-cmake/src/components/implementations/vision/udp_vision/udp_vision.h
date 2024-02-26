#ifndef UDP_VISION_H
#define UDP_VISION_H

#include <mutex>
#include <atomic>
#include <thread>
#include <iostream>
#include <QUdpSocket>

#include "../../../base_component.h"
#include "../../../messages/environment.h"

class UdpVision : public BaseComponent<Environment>{
public:
    UdpVision(std::atomic<bool>& stop, double fps);
    Environment update() override;
    void start() override;
    ~UdpVision(){};
};

#endif // UDP_VISION_H
