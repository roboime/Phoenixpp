//
// Created by ebert on 8/5/2024.
//

#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <Phoenixpp/core/agent_controller.h>

namespace phoenixpp::qt {
QT_BEGIN_NAMESPACE
namespace Ui { class Gui; }
QT_END_NAMESPACE

class Gui : public QMainWindow {
Q_OBJECT

public:
    Gui(core::AgentController &controller, QWidget *parent = nullptr);
    ~Gui() override;
    void updateEnvironmentValue();

private:
    void displayEnvironment(const messaging::Environment& env);
    core::AgentController &controller;
    Ui::Gui *ui;
};
} // phoenixpp::qt

#endif //GUI_H
