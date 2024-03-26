//
// Created by 24crickenbach on 3/26/2024.
//

#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <SFML/Graphics.hpp>
#include "ResourceLoader.h"



class GameOver : public sf::Drawable{


    sf::Text m_gameoverText;
    sf::Text m_scoreText;

public:
    GameOver();
    void SetGameOverScore(unsigned long score);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;



};



#endif //GAMEOVER_H
