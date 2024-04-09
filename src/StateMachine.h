//
// Created by minri on 3/25/2024.
//

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP
#include "State.h"
#include "Game.h"
#include <vector>
#include <SFML/Audio.hpp>


enum StateName : int{

    MENU = 0,
    GAME,
    DAILY_GAME

};



class StateMachine {

    State* p_currentState;
    std::vector<State*> m_states;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    void UpdateState();




public:
    StateMachine();
    ~StateMachine();
    void Run();
    void SwitchState(StateName state);
    void AddState();



};



#endif //STATEMACHINE_HPP
