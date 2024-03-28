//
// Created by 24crickenbach on 3/27/2024.
//

#ifndef DAILYGAME_H
#define DAILYGAME_H
#define SECONDS_PER_DAY 86400
#define MST_OFFSET 17
#include "Game.h"
#include <fstream>

class DailyGame : public Game{


    sf::Text m_dailyText;

    bool m_hasPlaced;



    unsigned long m_nextTime;
    unsigned int m_timeLeft;

    void HandleTimeText();
    void LoadBoard(std::ifstream& file);

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
