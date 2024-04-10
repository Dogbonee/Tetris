
//
// Created by hunde on 4/9/2024.
//

#include "FLineGame.h"

FLineGame::FLineGame(StateMachine &sm, sf::RenderWindow &window) : Game(sm, window), m_elapsedTime(0)
{
    m_timeText.setFont(GlobalResources::BlockFont);
    m_timeText.setCharacterSize(60);
    m_timeText.setString("0:00:00");
    m_timeText.setPosition(120, 300);
    m_timeText.setOrigin(System::CenterTextOrigin(m_timeText));

    m_lineCountText.setFont(GlobalResources::BlockFont);

    m_lineCountText.setCharacterSize(40);
    m_lineCountText.setString("Lines: 0");
    m_lineCountText.setPosition(120, 380);
    m_lineCountText.setOrigin(System::CenterTextOrigin(m_lineCountText));
}

void FLineGame::Update(const float& dt)
{
    Game::Update(dt);
    UpdateElapsedTime(dt);
}

void FLineGame::Render()
{
    Game::Render();
    if(!m_isGameOver)
    {
        p_window->draw(m_timeText);
        p_window->draw(m_lineCountText);
    }
}

void FLineGame::HandleScoring()
{
    Game::HandleScoring();
    if(m_clearedLineCount >= 40)
    {
        m_gameOverScreen.GameoverText.setString("Game End");
        m_gameOverScreen.GameoverText.setOrigin(System::CenterTextOrigin(m_gameOverScreen.GameoverText));
        m_gameOverScreen.ScoreText.setString("Time: " + m_timeText.getString());
        m_gameOverScreen.ScoreText.setOrigin(System::CenterTextOrigin(m_gameOverScreen.ScoreText));
        m_isGameOver = true;
    }
    m_lineCountText.setString("Lines: " + std::to_string(m_clearedLineCount));
    m_lineCountText.setOrigin(System::CenterTextOrigin(m_lineCountText));
}

void FLineGame::UpdateElapsedTime(const float& dt)
{
    m_elapsedTime += dt;
    int minutes = static_cast<int>(m_elapsedTime) / 60;
    int seconds = static_cast<int>(m_elapsedTime) % 60;
    int millis = static_cast<int>((m_elapsedTime - (static_cast<float>(seconds) + minutes * 60)) * 100.f);
    m_timeText.setString(std::to_string(minutes) + ':' + (seconds < 10 ? "0" : "")
        + std::to_string(seconds) + ':' + (millis < 10 ? "0" : "") + std::to_string(millis));
    m_timeText.setOrigin(System::CenterTextOrigin(m_timeText));
}
