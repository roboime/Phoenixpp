#ifndef CLI_H
#define CLI_H
#include <atomic>
#include <memory>
#include <unordered_map>
#include "../base_ui.h"
#include "../../factories/component_factory.h"

using namespace std;
using json = nlohmann::json;

class Cli : public BaseUi{
private:
    void showRawEnvironment();
    void showEnvironment();
    void showRobotCommands();
    void eloMecTester(unique_lock<mutex> &components_lock);
public:
    Cli();
    void execute() override;
    void loop();
    ~Cli() {}
};

#endif // CLI_H
