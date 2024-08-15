#include <Phoenixpp/core/agent_controller.h>
#include "Phoenixpp/qt/gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    phoenixpp::core::AgentController agentController;
    QApplication app(argc, argv);
    phoenixpp::qt::Gui window(agentController);
    window.show();
    return app.exec();
}
