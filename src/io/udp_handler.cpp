//
// Created by ebert on 8/6/2024.
//

#include "Phoenixpp/io/udp_handler.h"

#include <iostream>
#include <string.h>

namespace phoenixpp {
namespace io {

UdpHandler::UdpHandler(UdpData data) : data(data), received(false),
    buffer(new char[data.bufferSizeMax]), udpSocket(new QUdpSocket(this)),
    receiveThread(new QThread(this)), retryTimer(new QTimer(this)),
    receiveTimeoutTimer(new QTimer(this)) {
    connect(retryTimer, &QTimer::timeout, this, &UdpHandler::retryConnection);
    receiveTimeoutTimer->setInterval(500);
    receiveTimeoutTimer->setSingleShot(true);
    connect(receiveTimeoutTimer, &QTimer::timeout, this, [this]() {
        handleError(QAbstractSocket::SocketTimeoutError);
    });

    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpHandler::processPendingDatagrams);
    connect(udpSocket, QOverload<QAbstractSocket::SocketError>::of(&QUdpSocket::errorOccurred), this, &UdpHandler::handleError);
    moveToThread(receiveThread);
    receiveThread->start();
    retryTimer->moveToThread(receiveThread);
    QMetaObject::invokeMethod(this, "start", Qt::QueuedConnection);
}

void UdpHandler::start() {
    retryTimer->start(500);
}

void UdpHandler::processPendingDatagrams() {
    receiveTimeoutTimer->start();
    while (udpSocket->hasPendingDatagrams()) {
        QHostAddress sender;
        quint16 senderPort;
        qint64 datagramSize = udpSocket->pendingDatagramSize();
        datagramSize = std::min(datagramSize, static_cast<qint64>(data.bufferSizeMax));
        udpSocket->readDatagram(buffer, data.bufferSizeMax, &sender, &senderPort);
        receiveTimeoutTimer->start();
        received.store(true);
        auto buffer_ptr = new char[datagramSize];
        std::unique_lock lock(data.bufferQueue_mtx);
        if (static_cast<int>(data.bufferQueue.size()) <= data.queueSizeMax) {
            std::memcpy(buffer_ptr, buffer, static_cast<size_t>(datagramSize));
            data.bufferQueue.push(std::make_pair(buffer_ptr, datagramSize));
            lock.unlock();
        } else {
            lock.unlock();
            delete[] buffer_ptr;
        }
    }
}

void UdpHandler::handleError(QAbstractSocket::SocketError socketError) {
    std::cerr << "Udp Receiving Error: " << socketError << std::endl;
    received.store(false);
    if(udpSocket->state() == QAbstractSocket::ConnectedState) {
        udpSocket->abort();
    }
    retryTimer->start();
}

void UdpHandler::retryConnection() {
    if (received.load()) {
        retryTimer->stop();
        return;
    }
    if (udpSocket->bind(QHostAddress::AnyIPv4, data.port, QUdpSocket::ShareAddress)) {
        if (!udpSocket->joinMulticastGroup(QHostAddress(QString::fromStdString(data.multicastAddress)))) {
            std::cerr << "Failed to join multicast group." << std::endl;
        }
    } else {
        std::cerr << "Failed to bind socket." << std::endl;
    }
}


bool UdpHandler::getReceived() const {
    return received.load();
}

UdpHandler::~UdpHandler() {
    retryTimer->stop();
    receiveTimeoutTimer->stop();
    receiveThread->quit();
    receiveThread->wait();
    delete[] buffer;
    if (udpSocket->state() == QAbstractSocket::ConnectedState) {
        udpSocket->leaveMulticastGroup(QHostAddress(QString::fromStdString(data.multicastAddress)));
    }
    udpSocket->close();
    delete udpSocket;
    delete receiveThread;
    delete retryTimer;
    delete receiveTimeoutTimer;
}
} // io
} // phoenixpp