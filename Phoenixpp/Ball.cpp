#include "Ball.h"
#include <QPainter>

Ball::Ball(qreal x, qreal y, qreal vx, qreal vy)
    : posX(x), posY(y), velX(vx), velY(vy)
{
    setPos(x, y);
}

QRectF Ball::boundingRect() const
{
    return QRectF(-5, -5, 10, 10); // Ajuste conforme necessário
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QColor(255,165,0));
    painter->drawEllipse(boundingRect());
}
