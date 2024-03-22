#ifndef PARAMETERS_MANAGER_H
#define PARAMETERS_MANAGER_H

#include <string>
#include <any>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <mutex>

using namespace std;

class ParametersManager {
private:
    mutex mtx;
    unordered_map<string, any> parameters;
    string component;

    nlohmann::json convertAnyToJson(const any& value);
    void recursiveJsonInsert(nlohmann::json& jsonData, const vector<string>& keys, const any& value);
    void recursiveJsonLoad(const nlohmann::json& jsonData, string currentKey);

public:
    ParametersManager(string component);
    void set(string key, any value);
    any get(string key);
    void save();
    void load();
};

#endif // PARAMETERS_MANAGER_H
