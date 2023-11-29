#include "widget.h"
#include <QApplication>

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
#include"fieldClass/Field.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Obtenha o tamanho da tela
    QScreen *screen = a.primaryScreen();
    QRect screenGeometry = screen->geometry();

    // Use o tamanho da tela para criar um campo responsivo
    float windowWidth = screenGeometry.width() * 0.8;
    float windowHeight = screenGeometry.height() * 0.8;

    Field field(windowWidth, windowHeight);
    Ball bola(windowWidth/2,windowHeight/2,2,1);

    Robot robot(0,0,0,0,0,0,0);

    field.addBolaToCenter(&bola);
    field.addRobosToSides(&robot, 6); // Adiciona 6 robôs de cada lado

    field.show();


    Widget w;
    w.show();
    return a.exec();
}
