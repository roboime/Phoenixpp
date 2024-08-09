//
// Created by ebert on 8/6/2024.
//

#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H
#include <mutex>
#include <queue>
#include <string>

namespace phoenixpp {
namespace io {

using std::queue, std::pair, std::mutex, std::string;
struct UdpData {
    queue<pair<char*,int>> &bufferQueue;
	mutex &bufferQueue_mtx;
    string multicastAddress;
	int port;
	int bufferSizeMax;
	int queueSizeMax;
};

class UdpHandler {
public:
    explicit UdpHandler(UdpData &data);
    bool getReceived();
    ~UdpHandler() = default;
    void execute();
private:
    UdpData &data;
};

} // io
} // phoenixpp

#endif //NETWORK_HANDLER_H
