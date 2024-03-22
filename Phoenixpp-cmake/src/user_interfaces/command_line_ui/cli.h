#ifndef CLI_H
#define CLI_H
#include <atomic>
#include <memory>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "../base_ui.h"
#include "../../factories/component_factory.h"

using namespace std;
using json = nlohmann::json;

class Cli : public BaseUi{
private:
    json config;
    void showEnvironment();
    void showRobotCommands();
    void eloMecTester(unique_lock<mutex> &components_lock);
public:
    Cli(json config, double fps);
    void execute() override;
    ~Cli() {}
};

#endif // CLI_H
