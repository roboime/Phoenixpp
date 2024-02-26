#include "udp_vision.h"

UdpVision::UdpVision(atomic<bool>& stop, double fps) : BaseComponent("udpvision", stop, fps) {
    message.field_lenght = 0;
}

void UdpVision::start(){
    QUdpSocket udpSocket;
    if (!udpSocket.bind(QHostAddress("224.5.23.2"), 10020)) {
        cerr << "Failed to bind:" << udpSocket.errorString().toStdString();
    }
    if (!udpSocket.joinMulticastGroup(QHostAddress("224.5.23.2"))) {
        cerr << "Failed to join multicast group:" << udpSocket.errorString().toStdString();
    }
    QObject::connect(&udpSocket, &QUdpSocket::readyRead, [&]() {
        while (udpSocket.hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket.pendingDatagramSize());
            udpSocket.readDatagram(datagram.data(), datagram.size());

            if (udpSocket.error() != QAbstractSocket::UnknownSocketError) {
                cerr << "Socket error:" << udpSocket.errorString().toStdString();
            } else {
                char* in_buffer = datagram.data();
                int length = datagram.size();
                {
                    std::lock_guard<std::mutex> lock(this->message_mtx);
                    this->message.rawData = string(in_buffer);
                }
                /*
                SSL_WrapperPacket wrapperPacket;
                if (wrapperPacket.ParseFromArray(in_buffer, length)) {
                    printFrame(wrapperPacket);
                } else {
                    cerr << "Failed to parse SSL_WrapperPacket";
                }
                */
            }
        }
    });
}

Environment UdpVision::update(){
    return message;
}
/*
void printFrame(SSL_WrapperPacket wrapperPacket){
    SSL_DetectionFrame detection = wrapperPacket.detection();
    cout << "-----Received Wrapper Packet---------------------------------------------\n";
    double t_now = GetTimeSec();
    cerr << "Camera ID=" << detection.camera_id() << "FRAME=" << detection.frame_number() << " T_CAPTURE=" << detection.t_capture() << endl;
    ui->listWidget->addItem(
        QString("SSL-Vision Processing Latency                   %1fms")
            .arg((detection.t_sent() - detection.t_capture()) * 1000.0));

    ui->listWidget->addItem(
        QString("Network Latency (assuming synched system clock) %1fms")
            .arg((t_now - detection.t_sent()) * 1000.0));

    ui->listWidget->addItem(
        QString("Total Latency   (assuming synched system clock) %1fms")
            .arg((t_now - detection.t_capture()) * 1000.0));

    // Ball info:
    int balls_n = detection.balls_size();
    for (int i = 0; i < balls_n; i++) {
        const SSL_DetectionBall& ball = detection.balls(i);
        ui->listWidget->addItem(
            QString("-Ball (%1/%2): CONF=%3 POS=<%4,%5> Z=%6 RAW=<%7,%8>")
                .arg(i + 1)
                .arg(balls_n)
                .arg(ball.confidence())
                .arg(ball.x())
                .arg(ball.y())
                .arg(ball.has_z() ? ball.z() : -1.0)
                .arg(ball.pixel_x())
                .arg(ball.pixel_y()));
    }

    // Blue robot info:
    int robots_blue_n = detection.robots_blue_size();
    for (int i = 0; i < robots_blue_n; i++) {
        const SSL_DetectionRobot& robot = detection.robots_blue(i);
        ui->listWidget->addItem(QString("-Robot(B) (%1/%2): ").arg(i + 1).arg(robots_blue_n));
        printRobotInfo(robot);  // You may implement printRobotInfo similarly
    }

    // Yellow robot info:
    int robots_yellow_n = detection.robots_yellow_size();
    for (int i = 0; i < robots_yellow_n; i++) {
        const SSL_DetectionRobot& robot = detection.robots_yellow(i);
        ui->listWidget->addItem(QString("-Robot(Y) (%1/%2): ").arg(i + 1).arg(robots_yellow_n));
        printRobotInfo(robot);  // You may implement printRobotInfo similarly
    }
}
    */