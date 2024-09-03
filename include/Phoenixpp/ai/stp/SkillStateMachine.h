//
// Created by lucas on 30/08/2024.
//

#ifndef SKILLSTATEMACHINE_H
#define SKILLSTATEMACHINE_H

#include <iostream>
#include <map>

namespace phoenixpp::ai {
    // enum class State {
    //     IDLE,
    //     RUNNING,
    //     COMPLETED,
    //     FAILED,
    // };

    template <typename State>
    class SkillStateMachine {
    public:
        explicit SkillStateMachine(State initialState) {
            setState(initialState);
        }

        State getCurrentState() const {
            return currentState;
        }

    protected:
        void setState(const State newState) {
            currentState = newState;
        }

        void addTransition(const State fromState, const State toState) {
            transitions[fromState] = toState;
        }

    private:
        State currentState;
        std::map<State, State> transitions;
    };
}

#endif //SKILLSTATEMACHINE_H
