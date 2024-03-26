//
// Created by minri on 3/25/2024.
//

#include "StateMachine.hpp"

#include <iostream>



StateMachine::StateMachine() :m_window {sf::VideoMode(System::WIDTH, System::HEIGHT), "Tetris", sf::Style::Close}
{
    std::cout<<"Starting state machine\n";

    //
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
    switch(name)
    {
        case GAME:
            std::cout<<"Adding game state\n";
            Game* game = new Game(*this, m_window);
            m_states.emplace_back(game);
    }

}

void StateMachine::SwitchState(StateName state)
{
    std::cout<<"Switching to state " << state << "\n";
    //Allows the game to be run without the menu state being added
    //after the menustate is added, remove this.
    std::cout<<"State manually set to 0 for debugging purposes\n";
    state = static_cast<StateName>(0);
    p_currentState = m_states[state];
}
