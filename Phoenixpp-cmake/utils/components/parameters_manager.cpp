#include "parameters_manager.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ParametersManager::ParametersManager(string component) : component(component) {}

void ParametersManager::set(string key, any value) {
    parameters[key] = value;
}

any ParametersManager::get(string key) {
    return parameters[key];
}

nlohmann::json ParametersManager::convertAnyToJson(const any& value) {
    try {
        if (value.type() == typeid(int)) {
            return std::any_cast<int>(value);
        } else if (value.type() == typeid(double)) {
            return std::any_cast<double>(value);
        } else if (value.type() == typeid(bool)) {
            return std::any_cast<bool>(value);
        } else if (value.type() == typeid(std::string)) {
            return std::any_cast<std::string>(value);
        } else if (value.type() == typeid(vector<double>)) {
            const vector<double>& doubleVector = std::any_cast<vector<double>>(value);
            nlohmann::json jsonArray;
            for (const double& element : doubleVector) {
                jsonArray.push_back(element);
            }
            return jsonArray;
        } else if (value.type() == typeid(vector<vector<double>>)) {
            const vector<vector<double>>& doubleMatrix = std::any_cast<vector<vector<double>>>(value);
            nlohmann::json jsonMatrix;
            for (const auto& row : doubleMatrix) {
                nlohmann::json jsonRow;
                for (const double& element : row) {
                    jsonRow.push_back(element);
                }
                jsonMatrix.push_back(jsonRow);
            }
            return jsonMatrix;
        } else {
            cerr << "Unsupported type: " << value.type().name() << endl;
            return nullptr;
        }
    } catch (const std::bad_any_cast& e) {
        cerr << "Error: " << e.what() << endl;
        return nullptr;
    }
}

void ParametersManager::recursiveJsonInsert(nlohmann::json& jsonData, const vector<string>& keys, const any& value) {
    if (keys.empty()) {
        return;
    }

    const string& currentKey = keys.front();
    vector<string> remainingKeys(keys.begin() + 1, keys.end());

    if (remainingKeys.empty()) {
        jsonData[currentKey] = convertAnyToJson(value);
    } else {
        if (!jsonData.contains(currentKey)) {
            jsonData[currentKey] = nlohmann::json::object();
        }
        recursiveJsonInsert(jsonData[currentKey], remainingKeys, value);
    }
}

void ParametersManager::save() {
    const char* homeDir = PROJECT_ROOT_DIR;

    if (homeDir == nullptr) {
        cerr << "Error: Could not determine the home directory." << endl;
        return;
    }

    string filePath = string(homeDir) + "/configurations/" + component + ".json";

    ofstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing: " << filePath << endl;
        return;
    }

    nlohmann::json jsonData;
    for (const auto& pair : parameters) {
        vector<string> keys;
        istringstream iss(pair.first);
        for (string key; getline(iss, key, '.');) {
            keys.push_back(key);
        }
        recursiveJsonInsert(jsonData, keys, pair.second);
    }

    file << setw(4) << jsonData << endl;

    cout << "Saved parameters to: " << filePath << endl;
}

void ParametersManager::recursiveJsonLoad(const nlohmann::json& jsonData, string currentKey) {
    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
        string combinedKey = currentKey.empty() ? it.key() : currentKey + "." + it.key();

        if (it.value().is_object()) {
            recursiveJsonLoad(it.value(), combinedKey);
        } else if (it.value().is_boolean()) {
            set(combinedKey, it.value().get<bool>());
        } else if (it.value().is_number_integer()) {
            set(combinedKey, it.value().get<int>());
        } else if (it.value().is_string()) {
            set(combinedKey, it.value().get<string>());
        } else if (it.value().is_number_float()) {
            set(combinedKey, it.value().get<double>());
        } else if (it.value().is_array()) {
            if (std::all_of(it.value().begin(), it.value().end(), [](const auto& element) {
                    return element.is_number_float();
                })) {
                set(combinedKey, it.value().get<std::vector<double>>());
            }
        }
    }
}

void ParametersManager::load() {
    const char* homeDir = PROJECT_ROOT_DIR;

    if (homeDir == nullptr) {
        cerr << "Error: Could not determine the home directory." << endl;
        return;
    }

    string filePath = string(homeDir) + "/configurations/" + component + ".json";

    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open file for reading: " << filePath << endl;
        return;
    }

    nlohmann::json jsonData;
    file >> jsonData;

    recursiveJsonLoad(jsonData, "");

    cout << "Loaded parameters from: " << filePath << endl;
}
