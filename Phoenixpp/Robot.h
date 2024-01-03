// Robot.h
#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>
#include <QPixmap>


class Robot : public QGraphicsItem {
public:
    Robot(int id, int team, qreal x, qreal y, qreal vx, qreal vy, qreal orientation);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setPos(qreal newPosX, qreal newPosY, qreal newOrientation);
    void setVel(qreal newVelX, qreal newVelY);


    qreal getPos() const;

    qreal getVel() const;

    qreal getPosX() const;

    qreal getPosY() const;

    qreal getVelX() const;

    qreal getVelY() const;

    qreal getOrientation() const;

private:
    int id;
    int team;
    qreal posX;
    qreal posY;
    qreal velX;
    qreal velY;
    qreal orientation;
};

#endif // ROBOT_H
