#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsPixmapItem>

class Robot : public QGraphicsPixmapItem {
public:
    Robot(const QPixmap &pixmap, qreal diameter, qreal x, qreal y, QGraphicsItem *parent = nullptr);
};

#endif // ROBOT_H
