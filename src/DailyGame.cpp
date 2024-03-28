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

    LoadBoard(file);

    file.close();

    try
    {
        m_nextTime = std::stoi(dateBuf);

    }catch (std::exception& e)
    {
        std::cout<<"Could not load time\n";
        m_nextTime = 0;
    }



    m_defaultTickLength = 1000000;
    m_tickLength = m_defaultTickLength;
    m_speedTickLength = 0.1f;

    m_dailyText.setFont(GlobalResources::BlockFont);
    m_dailyText.setCharacterSize(100);

    m_dailyText.setPosition(System::WIDTH/2, System::HEIGHT/2);

    HandleTimeText();

    m_hasPlaced = std::time(nullptr) < m_nextTime;
}

void DailyGame::HandleTimeText()
{
    unsigned int difference = m_nextTime - std::time(nullptr);
    unsigned int hoursLeft = difference / 3600 - MST_OFFSET;
    unsigned int minutesLeft = (difference % 3600) / 60 + 1;
    std::string minutesZero = minutesLeft < 10 ? "0" : "";
    m_dailyText.setString("Next Piece in " + std::to_string(hoursLeft) + ':'+ minutesZero + std::to_string(minutesLeft));
    m_dailyText.setOrigin(System::CenterTextOrigin(m_dailyText));
}

void DailyGame::LoadBoard(std::ifstream& file)
{
    int i = 0;
    for(std::string buf; std::getline(file, buf); i++)
    {
        if(i == 0 || buf.empty())continue;
        for(int j = 0; j < buf.size(); j++)
        {
            m_board[i][j] = buf[j] == '1' ? 1 : 0;
            //In the future we need to save the pieces as different numbers and then add rects based on those numbers
        }
    }
    SpawnPiece(static_cast<PieceType>(std::rand() % 7));
    ManageGhostPiece();
}

void DailyGame::ManageGameClock()
{
    static float tickTimeRemaining = m_tickLength;
    tickTimeRemaining -= m_clock.restart().asSeconds();

    if((tickTimeRemaining <= 0 || tickTimeRemaining > m_tickLength) && !m_hasPlaced)
    {
        if(!Tick())ConfirmPiece();
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
        ConfirmPiece();
    }
}

void DailyGame::ConfirmPiece()
{
    std::ofstream file("../save.tetr");
    m_hasPlaced = true;
    int secondsTmmr = (std::time(nullptr) + SECONDS_PER_DAY);
    m_nextTime = (secondsTmmr) - secondsTmmr % SECONDS_PER_DAY;
    HandleTimeText();
    file << m_nextTime << '\n';
    for(int i = 0; i < System::BOARD_HEIGHT; i++)
    {
        for(int j = 0; j < System::BOARD_WIDTH; j++)
        {
            file << (m_board[i][j] & 1);
        }
        file<<'\n';
    }
    file.close();
}
