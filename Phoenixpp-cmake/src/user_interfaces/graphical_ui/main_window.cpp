#include "main_window.h"
#include "./ui_mainwindow.h"
#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), gui()
{
    ui->setupUi(this);
    gui.start();

}

MainWindow::~MainWindow(){
    gui.finish();
    delete ui;
}

