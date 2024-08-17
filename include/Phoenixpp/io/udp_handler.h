//
// Created by ebert on 8/6/2024.
//

#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H

#include <boost/atomic.hpp>
#include <mutex>
#include <queue>
#include <string>
#include <QUdpSocket>
#include <QHostAddress>
#include <QThread>
#include <QTimer>

namespace phoenixpp {
namespace io {

using std::queue, std::pair, std::mutex, std::string;

struct UdpData {
    queue<pair<char*,int>> &bufferQueue;
	mutex &bufferQueue_mtx;
    string multicastAddress;
	unsigned short port;
	int bufferSizeMax;
	int queueSizeMax;
};

class UdpHandler : public QObject{
    Q_OBJECT
public:
    explicit UdpHandler(UdpData data);
    [[nodiscard]] bool getReceived() const;
    ~UdpHandler() override;
signals:
    void startRetryTimer();
    void stopRetryTimer();
    void startTimeoutTimer();
    void stopTimeoutTimer();
public slots:
    void initializeTimers();
    void processPendingDatagrams();
    void handleError(QAbstractSocket::SocketError socketError);
    void onStartRetryTimer();
    void onStopRetryTimer();
    void onStartTimeoutTimer();
    void onStopTimeoutTimer();
private:
    void retryConnection();
    UdpData data;
    std::atomic<bool> received;
    char * buffer;
    QUdpSocket *udpSocket;
    QThread *timersThread;
    QTimer *retryTimer, *timeoutTimer;
};

} // io
} // phoenixpp

#endif //NETWORK_HANDLER_H
