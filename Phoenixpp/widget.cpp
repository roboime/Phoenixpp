#include "ui_widget.h"
#include "widget.h"
#include <chrono>
#include <ctime>

double Widget::GetTimeSec() {
    // Get the current time point
    auto currentTimePoint = std::chrono::system_clock::now();

    // Convert the time point to a time_t
    std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);

    // Use difftime to calculate the difference in seconds
    double secondsSinceEpoch = std::difftime(currentTime, 0);

    return secondsSinceEpoch;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QUdpSocket(this);
    if (!mSocket->bind(QHostAddress::AnyIPv4, 10020)) {
        qDebug() << "Failed to bind:" << mSocket->errorString();
    }
    if (!mSocket->joinMulticastGroup(QHostAddress("224.5.23.2"))) {
        qDebug() << "Failed to join multicast group:" << mSocket->errorString();
    }
    ui->listWidget->addItem(QString("oi"));

    connect(mSocket, &QUdpSocket::readyRead, [this]() {
        while (mSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(mSocket->pendingDatagramSize());
            mSocket->readDatagram(datagram.data(), datagram.size());

            if (mSocket->error() != QAbstractSocket::UnknownSocketError) {
                qDebug() << "Socket error:" << mSocket->errorString();
            } else {
                char* in_buffer = datagram.data();
                int length = datagram.size();
                SSL_WrapperPacket wrapperPacket;
                if (wrapperPacket.ParseFromArray(in_buffer, length)) {
                    printFrame(wrapperPacket);
                } else {
                    qDebug() << "Failed to parse SSL_WrapperPacket";
                }
            }
        }
    });
}

void Widget::printRobotInfo(const SSL_DetectionRobot& robot) {
    QString robotInfo;
    robotInfo += QString("CONF=%1 ").arg(robot.confidence(), 0, 'f', 2);

    if (robot.has_robot_id()) {
        robotInfo += QString("ID=%1 ").arg(robot.robot_id(), 3);
    } else {
        robotInfo += "ID=N/A ";
    }

    robotInfo += QString(" HEIGHT=%1 POS=<%2,%3> ")
                     .arg(robot.height(), 0, 'f', 2)
                     .arg(robot.x(), 9, 'f', 2)
                     .arg(robot.y(), 9, 'f', 2);

    if (robot.has_orientation()) {
        robotInfo += QString("ANGLE=%1 ").arg(robot.orientation(), 6, 'f', 3);
    } else {
        robotInfo += "ANGLE=N/A ";
    }

    robotInfo += QString("RAW=<%1,%2>").arg(robot.pixel_x(), 8, 'f', 2)
                     .arg(robot.pixel_y(), 8, 'f', 2);

    ui->listWidget->addItem(robotInfo);
}

void Widget::printFrame(SSL_WrapperPacket wrapperPacket){
    SSL_DetectionFrame detection = wrapperPacket.detection();
    ui->listWidget->addItem("-----Received Wrapper Packet---------------------------------------------");
    double t_now = GetTimeSec();
    // Frame info:
    ui->listWidget->addItem(
        QString("Camera ID=%1 FRAME=%2 T_CAPTURE=%3")
            .arg(detection.camera_id())
            .arg(detection.frame_number())
            .arg(QString::number(detection.t_capture(), 'f', 4)));

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


Widget::~Widget()
{
    mSocket->leaveMulticastGroup(QHostAddress("224.5.23.2"));
    delete ui;
}

