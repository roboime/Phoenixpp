#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "gui.h"

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Gui gui;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAIN_WINDOW_H
