#include "Ball.h"
#include <QTimer>
#include <QGraphicsScene>


Ball::Ball()
{
    qreal ballCenterX = 0.0;
    qreal ballCenterY = 0.0;
    qreal ballRadius = 100.0;
    //drew the ball
    QGraphicsEllipseItem* ballItem = new QGraphicsEllipseItem(ballCenterX - ballRadius, ballCenterY - ballRadius, 2 * ballRadius, 2 * ballRadius);
    ballItem->setBrush(QColor(255,165,0)); // Definir a cor de preenchimento da bola


}

//void Ball:move(){
//    setPos
//}
