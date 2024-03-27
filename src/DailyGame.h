//
// Created by 24crickenbach on 3/27/2024.
//

#ifndef DAILYGAME_H
#define DAILYGAME_H
#define SECONDS_PER_DAY 86400
#include "Game.h"
#include <fstream>

class DailyGame : public Game{


    sf::Text m_dailyText;

    bool m_hasPlaced;



    unsigned long m_previousTime;
    unsigned int m_timeDifference;
    unsigned int m_timeLeft;

    void HandleTimeText();

    //bool Tick() override;
    void ManageGameClock() override;
    void Render() override;
    void DropPiece() override;
    void ConfirmPiece();

public:
    DailyGame(StateMachine &sm, sf::RenderWindow &window);
    void Update() override;




};



#endif //DAILYGAME_H
