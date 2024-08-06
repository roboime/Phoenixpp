//
// Created by ebert on 8/5/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved
#include <QTimer>
#include <QThread>
#include "Phoenixpp/qt/gui.h"
#include "ui_Gui.h"

namespace phoenixpp::qt {
Gui::Gui(core::AgentController &controller, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Gui), controller(controller) {
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gui::updateEnvironmentValue);
    timer->start(100);
}

void Gui::updateEnvironmentValue() {
    int value = controller.getMessageCollection().environment->load().a;
    ui->textBox->setText(QString::number(value));
}

Gui::~Gui() {
    delete ui;
}
} // phoenixpp::qt
