//
// Created by 24crickenbach on 3/26/2024.
//

#ifndef MENU_H
#define MENU_H
#include "Button.h"
#include "StateMachine.h"


class Menu : public State{



    sf::Text m_titleLabel;

    std::vector<Button> m_buttons;
    Button m_standardButton;
    Button m_dailyButton;

    void StartStandardGame();
    void StartDailyGame();

protected:

    void Render() override;
    void HandleKeyboardInput(sf::Keyboard::Key keyCode) override;
    void HandleEvents() override;



public:
    Menu(StateMachine& sm, sf::RenderWindow& window);

    void Update() override;




};



#endif //MENU_H
