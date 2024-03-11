#ifndef UDP_RECEIVER_H
#define UDP_RECEIVER_H

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <iostream>
#include <memory>
#include <queue>
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/MulticastSocket.h"
//#include "Poco/Net/SocketAddress.h"
//#include "Poco/Net/SocketReactor.h"
//#include "Poco/Net/SocketNotification.h"
//#include "Poco/Net/SocketAcceptor.h"
//#include "Poco/NObserver.h"
//#include "Poco/Observer.h"

using namespace std;

class UdpReceiver{
private:
    atomic<bool> received, &stop, stopReceiver;
    Poco::Net::MulticastSocket socket;
    string multicastAddress, port;
    char * buffer;
    int bufferSizeMax, queueSizeMax;
    queue<pair<char*,int>> &bufferQueue;
    mutex &bufferQueue_mtx;
    thread receiveThread, reactorThread;
    void receivePacket();
    void reconnect();
public:
    UdpReceiver(atomic<bool>& stop, queue<pair<char*,int>> &bufferQueue, mutex &bufferQueue_mtx,
                string multicastAddress, string port, int bufferSizeMax, int queueSizeMax);
    void start();
    bool getReceived();
    ~UdpReceiver();
};

#endif // UDP_RECEIVER_H
