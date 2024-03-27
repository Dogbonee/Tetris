//
// Created by 24crickenbach on 3/27/2024.
//

#include "DailyGame.h"

#include <chrono>

DailyGame::DailyGame(StateMachine &sm, sf::RenderWindow &window) : Game(sm, window)
{

    std::ifstream file;
    file.open("../save.tetr");

    std::string dateBuf;
    std::getline(file, dateBuf);
    std::cout<<dateBuf<<"\n";

    file.close();

    try
    {
        m_previousTime = std::stoi(dateBuf);

    }catch (std::exception& e)
    {
        std::cout<<"Could not load time\n";
        exit(1);
    }
    m_previousTime = m_previousTime == 0 ? std::time(nullptr) - std::time(nullptr)%SECONDS_PER_DAY + SECONDS_PER_DAY: m_previousTime;



    m_defaultTickLength = 1000000;
    m_tickLength = m_defaultTickLength;
    m_speedTickLength = 0.1f;

    m_dailyText.setFont(GlobalResources::BlockFont);
    m_dailyText.setCharacterSize(100);

    m_dailyText.setPosition(System::WIDTH/2, System::HEIGHT/2);

    HandleTimeText();

    m_hasPlaced = m_timeDifference < SECONDS_PER_DAY;
}

void DailyGame::HandleTimeText()
{
    m_timeDifference = std::time(nullptr) - m_previousTime;

    unsigned int hoursLeft = m_timeDifference / 3600;
    unsigned int minutesLeft = (m_timeDifference % 3600) / 60;
    m_dailyText.setString("Next Piece in " + std::to_string(hoursLeft)+':'+std::to_string(minutesLeft));
    m_dailyText.setOrigin(System::CenterTextOrigin(m_dailyText));
}

void DailyGame::ManageGameClock()
{
    static float tickTimeRemaining = m_tickLength;
    tickTimeRemaining -= m_clock.restart().asSeconds();

    if((tickTimeRemaining <= 0 || tickTimeRemaining > m_tickLength) && !m_hasPlaced)
    {
        m_hasPlaced = !Tick() ? true : m_hasPlaced;
        tickTimeRemaining = m_tickLength;
        m_fpsCounter.setString("FPS: " + std::to_string(static_cast<int>(round(1000000/m_clock.restart().asMicroseconds()))));
    }
}




void DailyGame::Update()
{
   Game::Update();

}

void DailyGame::Render()
{
    p_window->clear();
    p_window->draw(m_fpsCounter);
    if(m_isGameOver)
    {
        p_window->draw(m_gameOverScreen);
        p_window->display();
        return;
    }


    p_window->draw(m_board);
    p_window->draw(m_currentPiece);
    p_window->draw(m_nextPiece);
    p_window->draw(m_scoreLabel);
    p_window->draw(m_scoreText);
    p_window->draw(m_holdLabel);
    p_window->draw(m_nextLabel);

    if(m_currentPiece.GetPosition() != m_ghostPiece.GetPosition())
    {
        p_window->draw(m_ghostPiece);
    }
    if(m_hasHeld)
    {
        p_window->draw(m_holdPiece);
    }
    if(m_hasPlaced)
    {
        p_window->draw(m_dailyText);
    }
    p_window->display();
}

void DailyGame::DropPiece()
{
    if(!m_hasPlaced)
    {
        Game::DropPiece();
        m_hasPlaced = true;
    }
}

void DailyGame::ConfirmPiece()
{
    std::ofstream file("../save.tetr");
    m_hasPlaced = true;
    HandleTimeText();
    int secondsTmmr = (std::time(nullptr) + SECONDS_PER_DAY);
    m_timeLeft = (secondsTmmr) - secondsTmmr % SECONDS_PER_DAY;
    file << m_timeLeft;
    file.close();
}
