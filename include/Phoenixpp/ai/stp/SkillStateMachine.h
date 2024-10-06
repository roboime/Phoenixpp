//
// Created by lucas on 30/08/2024.
//

#ifndef SKILLSTATEMACHINE_H
#define SKILLSTATEMACHINE_H

#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <Phoenixpp/messaging/RobotDecision.h>

namespace phoenixpp::ai {
    class SkillStateMachine {
    public:
        using StateAction = std::function<void(const messaging::EnvironmentPtr, std::shared_ptr<messaging::DecisionsStore> message)>;
        using TransitionCondition = std::function<bool(const messaging::EnvironmentPtr)>;

        // Add a new state with an action
        void addState(const std::string& stateName, StateAction action) {
            states[stateName] = std::move(action);
        }

        struct Transition {
            std::string toState;
            TransitionCondition condition;
        };

        // Add a transition between two states
        void addTransition(const std::string& fromState, const std::string& toState, TransitionCondition condition) {
            transitions[fromState].push_back({ toState, std::move(condition) });
        }

        // Set the initial state
        void setInitialState(const std::string& stateName) {
            SkillStateMachine::currentState = stateName;
        }

        void update(const messaging::EnvironmentPtr env, std::shared_ptr<messaging::DecisionsStore> message) {
            // Check for transitions
            if (transitions.contains(currentState)) {
                for (const auto& transition : transitions[currentState]) {
                    if (transition.condition(env)) {
                        std::cout << "Transitioning from " << currentState << " to " << transition.toState << std::endl;
                        currentState = transition.toState;
                        break; // Transitioned, so exit the loop
                    }
                }
            }

            // Execute the current state's action and return RobotDecision
            executeState(env, message);
        }

        // Execute the current state's action
        void executeState(const messaging::EnvironmentPtr env, std::shared_ptr<messaging::DecisionsStore> message) const {
            if (states.contains(currentState)) {
                states.at(currentState)(env, message);
            } else {
                std::cerr << "State not found: " << currentState << std::endl;
            }
        }

    private:
        std::unordered_map<std::string, StateAction> states;   // Map of state names to actions
        std::unordered_map<std::string, std::vector<Transition>> transitions;  // Map of transitions (fromState -> toState)
        std::string currentState = "DEFAULT";  // Current active state
    };
}

#endif //SKILLSTATEMACHINE_H
