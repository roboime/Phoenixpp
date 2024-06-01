//
// Created by ebert on 5/30/2024.
//

#include "Phoenixpp/base_ui.h"
#include <fstream>
#include <iostream>

using std::cerr, std::endl, std::cout;
namespace roboime {

BaseUi::BaseUi() : stop(false), fps(70)//, factory(stop){
{
    // try{
    //     std::ifstream file("../configurations/main_settings.json");
    //     json config;
    //     file >> config;
    //     this->config = config;
    //     shared_ptr<BaseComponent> component;
    //     string graph = config["graph"];
    //     vector<string> componentTypes = { "vision", "referee", "feedback", "blueLogic", "yellowLogic", "pathPlanning", "navigation", "communicator"};
    //     for (const auto &el : config["graphList"]){
    //         if(el["name"] != graph) continue;
    //         for(const auto &type : componentTypes){
    //             components[type] = factory.createComponent(type, config[type], 70);
    //             for(const auto &derived : el[type]){
    //                 components[type]->setComponent(derived, components[derived]);
    //             }
    //         }
    //         break;
    //     }
    // }
    // catch (std::exception ex){
    //     cerr << "Error instanciating components: " << ex.what() << endl;
    //     const std::type_info& typeInfo = typeid(ex);
    //     cerr << "Exception type: " << typeInfo.name() << endl;
    //     cerr << "Function: " << __PRETTY_FUNCTION__ << endl;
    // }
}

void BaseUi::start(){
    for (const auto& pair : components){
        if (pair.second == nullptr) continue;
        threads.push_back(thread([this, &pair]() { loopComponent(pair.first, 70); }));
    }
    cerr << "number of threads: " << threads.size() << endl;
}

void BaseUi::finish(){
    stop.store(true);
    std::lock_guard<mutex> lock(component_mtx);
    components.clear();
    for (auto& thread : threads) {
        if(thread.joinable()) thread.join();
    }
}

void BaseUi::setComponent(string key, shared_ptr<BaseComponent> new_component){
    // std::unique_lock<mutex> lock(component_mtx);
    // //cout << "ui component_mtx locked"<< e0ndl;
    // cout << "count: " << components[key].use_count() << endl;
    // if (!components.count(key)){
    //     cerr << "component not found\n";
    //     return;
    // }
    // cerr << "setting derived components of the old component into the new...\n";
    // // setting derived components of the old component into the new
    // if (components[key] != nullptr && new_component != nullptr){
    //
    //     for(auto& pair : components[key]->getComponents()){
    //         new_component->setComponent(pair.first, pair.second);
    //     }
    // }
    // cout << "count: " << components[key].use_count() << endl;
    // cerr << "updating component pointer in other components...\n";
    // // updating component pointer in other components
    // for (const auto& pair : components){
    //     if(pair.first != key && pair.second != nullptr && pair.second->isComponentPresent(key)){
    //         pair.second->setComponent(key, new_component);
    //         cout << "count: " << components[key].use_count() << endl;
    //     }
    // }
    // cerr << "setting new component on map...\n";
    // cout << "count: " << components[key].use_count() << endl;
    // //components.erase(key);
    // components[key] = new_component;
    // cout << "count: " << components[key].use_count() << endl;
    // cerr << "setting done\n";
    // new_component->start();
    // //cout << "ui component_mtx unlocked"<< endl;
}

bool BaseUi::componentIsValid(string key){
    return components.count(key) && components[key] != nullptr;
}

void BaseUi::loopComponent(string key, double fps){
    // unique_lock<mutex> lock(component_mtx);
    // //cout << "ui component_mtx locked"<< endl;
    // if(components.count(key)){
    //     components[key]->start();
    // }
    // lock.unlock();
    // //cout << "ui component_mtx unlocked"<< endl;
    // long long period = fps > 0 || key != "vision" ? (long long)(1000.0 / fps) : 0;
    // auto start = chrono::high_resolution_clock::now();
    // auto end = chrono::high_resolution_clock::now();
    //
    // while (!stop.load()) {
    //     {
    //         end = chrono::high_resolution_clock::now();
    //         auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    //         if(elapsed > period){
    //             start = chrono::high_resolution_clock::now();
    //             lock.lock();
    //             //cout << "ui component_mtx locked"<< endl;
    //             if(componentIsValid(key)){
    //                 components[key]->execute();
    //             }
    //             else{
    //                 cerr << "Component not valid\n";
    //             }
    //             lock.unlock();
    //             //cout << "ui component_mtx unlocked"<< endl;
    //         }
    //     }
    // }
    // cerr << "stop called looop component\n";
}

BaseUi::~BaseUi() {}


} // roboime