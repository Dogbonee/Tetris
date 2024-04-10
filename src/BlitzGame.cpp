//
// Created by hunde on 4/9/2024.
//

#include "BlitzGame.h"

BlitzGame::BlitzGame(StateMachine &sm, sf::RenderWindow &window) : Game(sm, window)
{
    m_timeText.setFont(GlobalResources::BlockFont);
    m_timeText.setCharacterSize(60);
    m_timeText.setString("0:00:00");

    m_timeText.setPosition(120, 300);
    m_timeText.setOrigin(System::CenterTextOrigin(m_timeText));

    m_elapsedTime = 120;
}

void BlitzGame::Update(const float& dt)
{
    Game::Update(dt);
    UpdateElapsedTime(dt);
    if(m_elapsedTime <= 0)
    {
        m_gameOverScreen.GameoverText.setString("Game End");
        m_gameOverScreen.GameoverText.setOrigin(System::CenterTextOrigin(m_gameOverScreen.GameoverText));
        m_gameOverScreen.SetGameOverScore(m_score);
        m_isGameOver = true;
    }

}

void BlitzGame::Render()
{
    Game::Render();
    if(!m_isGameOver)
    {
        p_window->draw(m_timeText);
    }
}

void BlitzGame::UpdateElapsedTime(const float& dt)
{
    m_elapsedTime -= dt;
    int minutes = static_cast<int>(m_elapsedTime) / 60;
    int seconds = static_cast<int>(m_elapsedTime) % 60;
    int millis = static_cast<int>((m_elapsedTime - (static_cast<float>(seconds) + minutes * 60)) * 100.f);
    m_timeText.setString(std::to_string(minutes) + ':' + (seconds < 10 ? "0" : "")
        + std::to_string(seconds) + ':' + (millis < 10 ? "0" : "") + std::to_string(millis));
    m_timeText.setOrigin(System::CenterTextOrigin(m_timeText));
}
