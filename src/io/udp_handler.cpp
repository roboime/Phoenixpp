//
// Created by ebert on 8/6/2024.
//

#include "Phoenixpp/io/udp_handler.h"

#include <iostream>
#include <string.h>

namespace phoenixpp {
namespace io {

UdpHandler::UdpHandler(const UdpData &data)
    : data(data), received(false),
    buffer(new char[data.packetMaxSize]), udpSocket(new QUdpSocket(this)),
    timersThread(new QThread(this))
    {
    connect(
        udpSocket,
        &QUdpSocket::readyRead,
        this,
        &UdpHandler::processPendingDatagrams
    );
    connect(
        udpSocket,
        QOverload<QAbstractSocket::SocketError>::of(&QUdpSocket::errorOccurred),
        this,
        &UdpHandler::handleError
    );
    timersThread->start();
    this->moveToThread(timersThread);
    QMetaObject::invokeMethod(this, "initializeTimers", Qt::QueuedConnection);
    connect(this, &UdpHandler::startRetryTimer, this, &UdpHandler::onStartRetryTimer);
    connect(this, &UdpHandler::stopRetryTimer, this, &UdpHandler::onStopRetryTimer);
    connect(this, &UdpHandler::startTimeoutTimer, this, &UdpHandler::onStartTimeoutTimer);
    connect(this, &UdpHandler::stopTimeoutTimer, this, &UdpHandler::onStopTimeoutTimer);
}

void UdpHandler::initializeTimers() {
    retryTimer = new QTimer(this);
    retryTimer->setInterval(500);
    timeoutTimer = new QTimer(this);
    timeoutTimer->setInterval(500);
    connect(retryTimer, &QTimer::timeout, this, &UdpHandler::retryConnection);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, [this]() {
        handleError(QAbstractSocket::SocketTimeoutError);
    });
    retryTimer->start();
}

void UdpHandler::processPendingDatagrams() {
    emit startTimeoutTimer();
    while (udpSocket->hasPendingDatagrams()) {
        QHostAddress sender;
        quint16 senderPort;
        qint64 datagramSize = udpSocket->pendingDatagramSize();
        datagramSize = std::min(datagramSize, static_cast<qint64>(data.packetMaxSize));
        udpSocket->readDatagram(buffer, datagramSize, &sender, &senderPort);
        emit startTimeoutTimer();
        std::unique_lock lock(data.ringBuffer_mtx);
        data.ringBuffer.push_back(std::string(buffer, datagramSize));
        lock.unlock();
        received.store(true);
    }
}

void UdpHandler::handleError(QAbstractSocket::SocketError socketError) {
    std::cerr << "Udp Receiving Error: " << socketError << std::endl;
    received.store(false);
    udpSocket->abort();
    emit startRetryTimer();
}

void UdpHandler::retryConnection() {
    if (received.load()) {
        emit stopRetryTimer();
        return;
    }
    if (udpSocket->bind(QHostAddress::AnyIPv4, data.port, QUdpSocket::ShareAddress)) {
        if (!udpSocket->joinMulticastGroup(data.multicastAddress)) {
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
    if(timeoutTimer->isActive()) emit stopTimeoutTimer();
    if(retryTimer->isActive()) emit stopRetryTimer();
    QMetaObject::invokeMethod(retryTimer, "stop", Qt::QueuedConnection);
    QMetaObject::invokeMethod(timeoutTimer, "stop", Qt::QueuedConnection);

    timersThread->quit();
    timersThread->wait();
    if (udpSocket->state() == QAbstractSocket::ConnectedState) {
        udpSocket->leaveMulticastGroup(
            QHostAddress(data.multicastAddress));
    }
    delete[] buffer;
}

void UdpHandler::onStartRetryTimer() {
    retryTimer->start();
}

void UdpHandler::onStopRetryTimer() {
    retryTimer->stop();
}

void UdpHandler::onStartTimeoutTimer() {
    timeoutTimer->start();
}

void UdpHandler::onStopTimeoutTimer() {
    timeoutTimer->stop();
}
} // io
} // phoenixpp