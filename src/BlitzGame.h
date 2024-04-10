//
// Created by hunde on 4/9/2024.
//

#ifndef BLITZGAME_H
#define BLITZGAME_H
#include "Game.h"


class BlitzGame : public Game{

    sf::Text m_timeText;

    float m_elapsedTime;

public:
    BlitzGame(StateMachine &sm, sf::RenderWindow &window);

    void Update() override;
    void Render() override;
    void UpdateElapsedTime();
};



#endif //BLITZGAME_H
