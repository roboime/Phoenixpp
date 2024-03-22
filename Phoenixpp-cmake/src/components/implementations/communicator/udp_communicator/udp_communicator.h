#ifndef UDP_COMMUNICATOR_H
#define UDP_COMMUNICATOR_H

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <iostream>
#include <memory>
#include <queue>
#include "../../../../../proto/protobuf_files.h"
#include "../../../../utils/udp_sender.h"
#include "../../../base_component.h"
#include "../../../messages/robot_commands.h"

class UdpCommunicator: public TBaseComponent<TransmittedCommands>{
private:
    int bufferSizeMax;
    int queueSizeMax;
    shared_ptr<UdpSender> udpSender;
    queue<pair<char*,int>> bufferQueue;
    mutex bufferQueue_mtx;
    void pushRobotCommand(string logic);
public:
    UdpCommunicator(std::atomic<bool>& stop, double fps);
    TransmittedCommands update(TransmittedCommands transmittedCommands) override;
    void start() override;
    ~UdpCommunicator();
};

#endif // UDP_COMMUNICATOR_H
