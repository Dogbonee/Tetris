//
// Created by 24crickenbach on 3/26/2024.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <functional>
#include <SFML/Graphics.hpp>
#include "System.h"

class Button : public sf::Drawable{


    sf::RectangleShape m_buttonShape;
    sf::Text m_buttonText;
    bool m_hovered;
    sf::Color m_buttonColor;

public:
    Button(sf::Vector2f size, sf::String text);


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setColor(sf::Color color);
    void setPosition(const sf::Vector2f& position);
    void setPosition(float x, float y);
    void ButtonUpdate(sf::Vector2i mousePos);
    void Activate();

    std::function<void()> callback;

};



#endif //BUTTON_H
