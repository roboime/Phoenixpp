#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>

class Ball : public QGraphicsItem
{
public:
    Ball(qreal x, qreal y, qreal vx, qreal vy);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal posX;
    qreal posY;
    qreal velX;
    qreal velY;
};

#endif // BALL_H
