//
// Created by 24crickenbach on 3/26/2024.
//

#include "Menu.h"

#include <iostream>

Menu::Menu(StateMachine &sm, sf::RenderWindow &window) : State(sm, window), m_startButton(sf::Vector2f(400,250), "Start")
{
    std::cout << "Menu!\n";
    m_titleLabel.setFont(GlobalResources::BlockFont);
    m_titleLabel.setCharacterSize(140);
    m_titleLabel.setFillColor(sf::Color::White);
    m_titleLabel.setString("Tetritime");
    m_titleLabel.setOrigin(System::CenterTextOrigin(m_titleLabel));
    m_titleLabel.setPosition(System::WIDTH / 2, 75);

    m_startButton.setPosition(System::WIDTH/2, System::HEIGHT/2);
    m_startButton.setColor(sf::Color::Red);

    m_startButton.callback = [this] { StartGame(); };
    m_buttons.push_back(m_startButton);
}

void Menu::StartGame()
{
    p_stateMachine->SwitchState(GAME);
}

void Menu::Render()
{
    p_window->clear();
    p_window->draw(m_titleLabel);
    for(auto& button : m_buttons) p_window->draw(button);
    p_window->display();
}

void Menu::HandleKeyboardInput(sf::Keyboard::Key keyCode)
{
    if(keyCode == sf::Keyboard::Enter)
    {
        p_stateMachine->SwitchState(GAME);
    }
}

void Menu::HandleEvents()
{
    for(sf::Event event{}; p_window->pollEvent(event);)
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                p_window->close();
            break;
            case sf::Event::KeyPressed:
                //Key repeat enabled
                    HandleKeyboardInput(event.key.code);
            break;
            case sf::Event::MouseMoved:
                for(auto& button : m_buttons)button.ButtonUpdate(sf::Vector2i(event.mouseMove.x,event.mouseMove.y));
                break;
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    for(auto& button : m_buttons)button.Activate();
                }


        }
    }
}

void Menu::Update()
{
    HandleEvents();
    Render();
}


