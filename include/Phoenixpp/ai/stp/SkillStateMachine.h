//
// Created by lucas on 30/08/2024.
//

#ifndef SKILLSTATEMACHINE_H
#define SKILLSTATEMACHINE_H

#include <iostream>

namespace phoenixpp::ai {
    enum class State {
        Idle,
        Move,
    };

    class SkillStateMachine {
    public:
        SkillStateMachine() : currentState(State::Idle) {}

        void setState(State newState) {
            currentState = newState;
            onEnterState(currentState);
        }

        void onEnterState(State state) {
            switch (state) {
                case State::Idle:
                    std::cout << "Entering Idle State.\n";
                break;
                case State::Move:
                    std::cout << "Entering Running State.\n";
                break;
            }
        }

        void processEvent(const std::string& event) {
            if (event == "move") {
                if (currentState == State::Idle) {
                    setState(State::Move);
                }
            } else if (event == "idle") {
                setState(State::Idle);
            } else {
                std::cout << "Unknown event: " << event << std::endl;
            }
        }

    private:
        State currentState;
    };
}

#endif //SKILLSTATEMACHINE_H
