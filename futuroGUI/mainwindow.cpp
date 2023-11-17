// mainwindow.cpp
#include "mainwindow.h"
#include "Ball.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a QGraphicsScene
    scene = new QGraphicsScene(this);

    // Create a Ball and add it to the scene
    Ball *ball = new Ball(100, 100, 2, 1);
    scene->addItem(ball);

    // Access QGraphicsView directly from ui
    //ui->centralwidget->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
