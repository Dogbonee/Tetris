//
// Created by minri on 3/25/2024.
//

#include "StateMachine.h"

#include <iostream>

#include "DailyGame.h"
#include "Menu.h"


StateMachine::StateMachine() :m_window {sf::VideoMode(System::WIDTH, System::HEIGHT), "Tetris", sf::Style::Close}
{
    std::cout<<"Starting state machine\n";
}

StateMachine::~StateMachine()
{
    for(auto* state : m_states)
    {
        delete state;
    }
}


void StateMachine::UpdateState()
{
    //Only updates one state at any given point: the current state selected. Rendering and
    //Event handling are each handled separately by each state, not in the state machine.
    if(p_currentState != nullptr)
    {
        p_currentState->Update();
    }
}


void StateMachine::Run()
{
    std::cout<<"Game setup successful. Running...\n";
    m_window.setFramerateLimit(60);
    while(m_window.isOpen())
    {
        UpdateState();
    }
}

void StateMachine::AddState()
{
    //All possible states should be added here
    Menu* menu = new Menu(*this, m_window);
    m_states.emplace_back(menu);
    Game* game = new Game(*this, m_window);
    m_states.emplace_back(game);
    DailyGame* dailyGame = new DailyGame(*this, m_window);
    m_states.emplace_back(dailyGame);
}

void StateMachine::SwitchState(StateName state)
{
    //get a pointer to the selected state and set it as the current state
    std::cout<<"Switching to state " << state << "\n";
    p_currentState = m_states[state];
}
