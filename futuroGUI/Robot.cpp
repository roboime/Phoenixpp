#include "Robot.h"

Robot::Robot(const QPixmap &pixmap, qreal diameter, qreal x, qreal y, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap.scaled(diameter, diameter), parent) {
    setPos(x, y);
    // Configurar propriedades do robô, se necessário
}
