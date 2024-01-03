#ifndef FIELD_H
#define FIELD_H

#include<QGraphicsView>
#include "Ball.h"
#include "Robot.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QScreen>
#include <QPixmap>

class Field : public QGraphicsView {
public:
    Field(float windowWidth, float windowHeight);

    void addObjectToField(QGraphicsItem *object, float x, float y);
    void addBolaToCenter(Ball *bola);

    void addRobosToSides(Robot *robot, int numRobos);

private:
    QGraphicsScene *scene;
};
#endif
