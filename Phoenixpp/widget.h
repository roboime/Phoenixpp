#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <iostream>
//#include "protobuf_files.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QUdpSocket;

class Widget : public QWidget
{
    Q_OBJECT

public:
    double static GetTimeSec();
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //void printFrame(SSL_WrapperPacket wrapperPacket);
    //void printRobotInfo(const SSL_DetectionRobot& robot);

private:
    Ui::Widget *ui;
    QUdpSocket *mSocket;
    //SSL_WrapperPacket wrapperPacket;
};
#endif // WIDGET_H
