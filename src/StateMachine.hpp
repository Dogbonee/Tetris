//
// Created by minri on 3/25/2024.
//

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP
#include "State.hpp"
#include "Game.h"
#include <vector>


enum StateName : int{

    MENU = 0,
    GAME

};



class StateMachine {

    State* p_currentState;
    std::vector<State*> m_states;
    sf::RenderWindow m_window;
    void UpdateState();

public:
    StateMachine();
    ~StateMachine();
    void Run();
    void SwitchState(StateName state);
    void AddState(StateName name);



};



#endif //STATEMACHINE_HPP
