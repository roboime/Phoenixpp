//
// Created by ebert on 8/5/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Gui.h" resolved
#include <QTimer>
#include <QThread>
#include <atomic>
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
    messaging::Environment env = controller.getMessageCollection().environment->load();
    displayEnvironment(env);
}

void Gui::displayEnvironment(const messaging::Environment& env) {
    QString text;
    text += QString("Received: %1\n").arg(env.received ? "Yes" : "No");

    // Display balls
    text += "Balls:\n";
    for (const auto& ball : env.ball) {
        if(!ball.valid) continue;
        text += QString("ID: %1, Position: (%2, %3), Velocity: (%4, %5), Acceleration: (%6, %7), Radius: %8, Confidence: %9, Z: %10\n")
            .arg(ball.id)
            .arg(ball.position.real()).arg(ball.position.imag())
            .arg(ball.velocity.real()).arg(ball.velocity.imag())
            .arg(ball.acceleration.real()).arg(ball.acceleration.imag())
            .arg(ball.radius)
            .arg(ball.confidence)
            .arg(ball.z);
    }

    // Display robots
    text += "Robots:\n";
    for (const auto& robot : env.robot) {
        if(!robot.valid) continue;
        text += QString("ID: %1, Position: (%2, %3), Velocity: (%4, %5), Acceleration: (%6, %7), Radius: %8, Confidence: %9, Orientation: %10, Height: %11, Kicker Distance: %12\n")
            .arg(robot.id)
            .arg(robot.position.real()).arg(robot.position.imag())
            .arg(robot.velocity.real()).arg(robot.velocity.imag())
            .arg(robot.acceleration.real()).arg(robot.acceleration.imag())
            .arg(robot.radius)
            .arg(robot.confidence)
            .arg(robot.orientation)
            .arg(robot.height)
            .arg(robot.kickerDistance);
    }

    // Display field (assuming Field has a suitable representation)
    // text += "Field information here\n";

    ui->textBox->setText(text);
}

Gui::~Gui() {
    delete ui;
}
} // phoenixpp::qt
