#include "mainwindow.h"
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
#include<SoccerField.h>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // Obtenha o tamanho da tela
    QScreen *screen = a.primaryScreen();
    QRect screenGeometry = screen->geometry();

    // Use o tamanho da tela para criar um campo responsivo
    float windowWidth = screenGeometry.width() * 0.8;
    float windowHeight = screenGeometry.height() * 0.8;

    SoccerField soccerField(windowWidth, windowHeight);
    Ball bola(windowWidth/2,windowHeight/2,2,1);

    Robot robot(1,1,20,20,1,1,1);

    soccerField.addBolaToCenter(&bola);
    soccerField.addRobosToSides(&robot, 6); // Adiciona 6 robôs de cada lado



    //soccerField.addObjectToField(&bola, 0, 0);
    //soccerField.addObjectToField(&robot,50,50);

    soccerField.show();

    return a.exec();
}
