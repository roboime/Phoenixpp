// robots.cpp
#include "Robot.h"
#include <QPainter>

Robot::Robot(int id, int team, qreal x, qreal y, qreal vx, qreal vy, qreal orientationX, qreal orientationY)
    : id(id), team(team), posX(x), posY(y), velX(vx), velY(vy), orientationX(orientationX), orientationY(orientationY)
{
    setPos(x, y);
}

QRectF Robot::boundingRect() const
{
    return QRectF(-25, -25, 50, 50); // Adjust the bounding rectangle as needed
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Customize the appearance of the robot
    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect());
    painter->drawLine(0, 0, 15 * orientationX, 15 * orientationY);

    // Optionally, you can add more details to the robot's appearance
    // For example, drawing an ID or team information
    painter->drawText(boundingRect(), Qt::AlignCenter, QString("%1").arg(id));
}
