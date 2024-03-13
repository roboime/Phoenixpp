#include "base_ui.h"
#include <vector>
#include <thread>

using namespace std;

BaseUi::BaseUi(double fps) : stop(false), fps(fps), factory(stop) {}

void BaseUi::start(){
    vector<thread> threads;
    for (const auto& pair : components){
        if (pair.second == nullptr) continue;
        threads.push_back(thread([this, &pair]() { loopComponent(pair.first, 70); }));
    }
    cerr << "number of threads: " << threads.size() << endl;
    long long period = (long long)(1000.0 / fps);
    while (!stop.load()){
        execute();
        this_thread::sleep_for(chrono::milliseconds(period));
    }
    {
        lock_guard<mutex> lock(component_mtx);
        components.clear();
    }
    for (auto& thread : threads) {
        if(thread.joinable()) thread.join();
    }
}

void BaseUi::setComponent(string key, shared_ptr<BaseComponent> new_component){
    unique_lock<mutex> lock(component_mtx);
    //cout << "ui component_mtx locked"<< e0ndl;
    cout << "count: " << components[key].use_count() << endl;
    if (!components.count(key)){
        cerr << "component not found\n";
        return;
    }
    cerr << "setting derived components of the old component into the new...\n";
    // setting derived components of the old component into the new
    if (components[key] != nullptr && new_component != nullptr){
        for(auto& pair : components[key]->getComponents()){
            new_component->setComponent(pair.first, pair.second);
        }
    }
    cout << "count: " << components[key].use_count() << endl;
    cerr << "updating component pointer in other components...\n";
    // updating component pointer in other components
    for (const auto& pair : components){
        if(pair.first != key && pair.second != nullptr && pair.second->isComponentPresent(key)){
            pair.second->setComponent(key, new_component);
            cout << "count: " << components[key].use_count() << endl;
        }
    }
    cerr << "setting new component on map...\n";
    cout << "count: " << components[key].use_count() << endl;
    //components.erase(key);
    components[key] = new_component;
    cout << "count: " << components[key].use_count() << endl;
    cerr << "setting done\n";
    new_component->start();
    //cout << "ui component_mtx unlocked"<< endl;
}

bool BaseUi::componentIsValid(string key){
    return components.count(key) && components[key] != nullptr;
}

void BaseUi::loopComponent(string key, double fps){
    unique_lock<mutex> lock(component_mtx);
    //cout << "ui component_mtx locked"<< endl;
    if(components.count(key)){
        components[key]->start();
    }
    lock.unlock();
    //cout << "ui component_mtx unlocked"<< endl;
    long long period = fps > 0 || key != "vision" ? (long long)(1000.0 / fps) : 0;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();

    while (!stop.load()) {
        {
            end = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            if(elapsed > period){
                start = chrono::high_resolution_clock::now();
                lock.lock();
                //cout << "ui component_mtx locked"<< endl;
                if(componentIsValid(key)){
                    components[key]->execute();
                }
                else{
                    cerr << "Component not valid\n";
                }
                lock.unlock();
                //cout << "ui component_mtx unlocked"<< endl;
            }
        }
    }
    cerr << "stop called looop component\n";
}

BaseUi::~BaseUi() {}
