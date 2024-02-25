#ifndef PARAMETERS_MANAGER_H
#define PARAMETERS_MANAGER_H

#include <string>
#include <any>
#include <unordered_map>
#include <nlohmann/json.hpp>

class ParametersManager {
private:
    std::unordered_map<std::string, std::any> parameters;
    std::string component;

    nlohmann::json convertAnyToJson(const std::any& value);
    void recursiveJsonInsert(nlohmann::json& jsonData, const std::vector<std::string>& keys, const std::any& value);
    void recursiveJsonLoad(const nlohmann::json& jsonData, std::string currentKey);

public:
    ParametersManager(std::string component);
    void set(std::string key, std::any value);
    std::any get(std::string key);
    void save();
    void load();
};

#endif // PARAMETERS_MANAGER_H
