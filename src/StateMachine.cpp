//
// Created by minri on 3/25/2024.
//

#include "StateMachine.hpp"

#include <iostream>

#include "Menu.h"


StateMachine::StateMachine() :m_window {sf::VideoMode(System::WIDTH, System::HEIGHT), "Tetris", sf::Style::Close}
{
    std::cout<<"Starting state machine\n";

    //
}

StateMachine::~StateMachine()
{
    for(auto* state : m_states)
    {
        delete state;
    }
    m_states.clear();
}


void StateMachine::UpdateState()
{
    if(p_currentState != nullptr)
    {
        p_currentState->Update();
    }
}


void StateMachine::Run()
{
    std::cout<<"Game setup successful. Running...\n";
    while(m_window.isOpen())
    {
        UpdateState();
    }
}

void StateMachine::AddState(StateName name)
{
    std::cout<<"Adding game state\n";
    switch(name)
    {
        case MENU: {
            Menu* menu = new Menu(*this, m_window);
            m_states.emplace_back(menu);
        }
            break;
        case GAME: {
            Game* game = new Game(*this, m_window);
            m_states.emplace_back(game);
        }
            break;
    }

}

void StateMachine::SwitchState(StateName state)
{
    std::cout<<"Switching to state " << state << "\n";
    p_currentState = m_states[state];
}
