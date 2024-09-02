//
// Created by ebert on 8/5/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved
#include <QTimer>
#include <QThread>
#include <atomic>
#include "Phoenixpp/qt/gui.h"
#include "ui_Gui.h"
#include "Phoenixpp/qt/field_widget.h"
#include <QKeyEvent>

namespace phoenixpp::qt {
Gui::Gui(core::AgentController &controller, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Gui), controller(controller) {
    ui->setupUi(this);
    this->showMaximized();
    QTimer *fieldTimer = new QTimer(this);
    connect(fieldTimer, &QTimer::timeout, this, &Gui::updateField);
    fieldTimer->start(7);
}

void Gui::updateField() {
    ui->fieldWidget->updateField(controller.getMessageCollection().environment);
}

void Gui::displayEnvironment(const messaging::Environment& env) {
    QString text;
    text += QString("Received: %1\n").arg(env.received.load() ? "Yes" : "No");
    text += "Balls:\n";
    for(int i=0;i<messaging::MAX_BALLS;i++) {
        if(!env.balls[i].valid) continue;
        text += QString("Position: (%1, %2), Velocity: (%3, %4), Acceleration: (%5, %6), Radius: %7, Confidence: %8, Z: %9\n")
            .arg(QString::number(env.balls[i].positionX.load(), 'f', 2))
            .arg(QString::number(env.balls[i].positionY.load(), 'f', 2))
            .arg(QString::number(env.balls[i].velocityX.load(), 'f', 2))
            .arg(QString::number(env.balls[i].velocityY.load(), 'f', 2))
            .arg(QString::number(env.balls[i].accelerationX.load(), 'f', 2))
            .arg(QString::number(env.balls[i].accelerationY.load(), 'f', 2))
            .arg(QString::number(env.balls[i].radius.load(), 'f', 2))
            .arg(QString::number(env.balls[i].confidence.load(), 'f', 2))
            .arg(QString::number(env.balls[i].z.load(), 'f', 2));
    }
    text += "Robots:\n";
    for (const auto& robotGroup : {std::ref(env.blueRobots), std::ref(env.yellowRobots)}) {
        for (const auto& robot : robotGroup.get()) {
            if(!robot.valid) continue;
            text += QString("ID: %1, Position: (%2, %3), Velocity: (%4, %5), Acceleration: (%6, %7), Radius: %8, Confidence: %9, Orientation: %10, Height: %11, Kicker Distance: %12\n")
                .arg(robot.id)
                .arg(QString::number(robot.positionX, 'f', 2))
                .arg(QString::number(robot.positionY, 'f', 2))
                .arg(QString::number(robot.velocityX, 'f', 2))
                .arg(QString::number(robot.velocityY, 'f', 2))
                .arg(QString::number(robot.accelerationX, 'f', 2))
                .arg(QString::number(robot.accelerationY, 'f', 2))
                .arg(QString::number(robot.radius, 'f', 2))
                .arg(QString::number(robot.confidence, 'f', 2))
                .arg(QString::number(robot.orientation, 'f', 2))
                .arg(QString::number(robot.height, 'f', 2))
                .arg(QString::number(robot.kickerDistance, 'f', 2));
        }
    }
    // ui->textBox->setText(text);
}

void Gui::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_F11) {
        toggleFullScreen();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void Gui::toggleFullScreen() {
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}
Gui::~Gui() {
    delete ui;
}
} // phoenixpp::qt
