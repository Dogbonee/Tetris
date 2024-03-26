//
// Created by 24crickenbach on 3/26/2024.
//

#include "GameOver.h"

GameOver::GameOver()
{
    m_gameoverText.setFont(GlobalResources::BlockFont);
    m_gameoverText.setCharacterSize(160);
    m_gameoverText.setString("Game Over!");
    m_gameoverText.setOrigin(System::CenterTextOrigin(m_gameoverText));
    m_gameoverText.setPosition(System::WIDTH/2, 150);
    m_scoreText.setFont(GlobalResources::BlockFont);
    m_scoreText.setCharacterSize(60);
    m_scoreText.setPosition(System::WIDTH/2, System::HEIGHT/2);
}

void GameOver::SetGameOverScore(unsigned long score)
{
    m_scoreText.setString("Score: " + std::to_string(score));
    m_scoreText.setOrigin(System::CenterTextOrigin(m_scoreText));
}

void GameOver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_gameoverText);
    target.draw(m_scoreText);
}
