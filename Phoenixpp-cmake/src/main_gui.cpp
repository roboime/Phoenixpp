#include "user_interfaces/graphical_ui/main_window.h"
#include <fstream>
#include <iostream>
#include <QApplication>

using json = nlohmann::json;
using namespace std;

int main(int argc, char**argv){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
