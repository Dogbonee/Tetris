//
// Created by 24crickenbach on 3/26/2024.
//

#include "GameOver.h"

GameOver::GameOver()
{
    GameoverText.setFont(GlobalResources::BlockFont);
    GameoverText.setCharacterSize(160);
    GameoverText.setString("Game Over!");
    GameoverText.setOrigin(System::CenterTextOrigin(GameoverText));
    GameoverText.setPosition(System::WIDTH/2, 150);
    ScoreText.setFont(GlobalResources::BlockFont);
    ScoreText.setCharacterSize(60);
    ScoreText.setPosition(System::WIDTH/2, System::HEIGHT/2);
}

void GameOver::SetGameOverScore(unsigned long score)
{
    ScoreText.setString("Score: " + std::to_string(score));
    ScoreText.setOrigin(System::CenterTextOrigin(ScoreText));
}

void GameOver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(GameoverText);
    target.draw(ScoreText);
}
