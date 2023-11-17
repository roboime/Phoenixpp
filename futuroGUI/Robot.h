// Robot.h
#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>
#include <QPixmap>

class Robot : public QGraphicsItem {
public:
    Robot(int id, int team, qreal x, qreal y, qreal vx, qreal vy, qreal orientationX, qreal orientationY);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int id;
    int team;
    qreal posX;
    qreal posY;
    qreal velX;
    qreal velY;
    qreal orientationX;
    qreal orientationY;
};

#endif // ROBOT_H
