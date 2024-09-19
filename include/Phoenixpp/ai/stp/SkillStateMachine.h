//
// Created by lucas on 30/08/2024.
//

#ifndef SKILLSTATEMACHINE_H
#define SKILLSTATEMACHINE_H

#include <functional>
#include <iostream>
#include <unordered_map>

namespace phoenixpp::ai {
    class SkillStateMachine {
    public:
        using StateAction = std::function<void()>;

        // Add a new state with an action
        void addState(const std::string& stateName, StateAction action) {
            states[stateName] = action;
        }

        // Add a transition between two states
        void addTransition(const std::string& fromState, const std::string& toState) {
            transitions[fromState] = toState;
        }

        // Set the initial state
        void setInitialState(const std::string& stateName) {
            currentState = stateName;
        }

        // Trigger the transition to the next state
        void nextState() {
            if (transitions.contains(currentState)) {
                currentState = transitions[currentState];
                executeState();
            } else {
                std::cerr << "No transition from current state: " << currentState << std::endl;
            }
        }

        // Execute the current state's action
        void executeState() const {
            if (states.contains(currentState)) {
                std::cout << "Executing state: " << currentState << std::endl;
                states.at(currentState)();
            } else {
                std::cerr << "State not found: " << currentState << std::endl;
            }
        }

    private:
        std::unordered_map<std::string, StateAction> states;   // Map of state names to actions
        std::unordered_map<std::string, std::string> transitions;  // Map of transitions (fromState -> toState)
        std::string currentState;  // Current active state
    };
}

#endif //SKILLSTATEMACHINE_H
