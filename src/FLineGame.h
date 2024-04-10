
//
// Created by hunde on 4/9/2024.
//

#ifndef FLINEGAME_H
#define FLINEGAME_H
#include "Game.h"


class FLineGame : public Game{


    sf::Text m_lineCountText;
    sf::Text m_timeText;

    float m_elapsedTime;

public:
    FLineGame(StateMachine &sm, sf::RenderWindow &window);
    void Update() override;
    void Render() override;
    void HandleScoring() override;

    void UpdateElapsedTime();

};



#endif //FLINEGAME _H
