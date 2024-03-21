//
// Created by 24crickenbach on 3/20/2024.
//

#include "Game.h"

Game::Game() : m_window{sf::VideoMode(System::WIDTH, System::HEIGHT), "Tetris"}, m_tickLength(1.f)
{
    SpawnPiece(T_BLOCK);
}

void Game::Render()
{
    m_window.clear();
    m_window.draw(m_board);
    DrawPieces(m_window);
    m_window.display();
}

void Game::HandleEvents()
{

    for(sf::Event event{}; m_window.pollEvent(event);)
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                //Key repeat enabled
                HandleKeyboardInput(event.key.code);
                break;
        }
    }
}

void Game::HandleKeyboardInput(sf::Keyboard::Key keyCode)
{
    switch(keyCode)
    {
        case sf::Keyboard::Right:
            if(p_currentPiece)
            {
                p_currentPiece->Move(MOVE_RIGHT);
            }
            break;
        case sf::Keyboard::Left:
            if(p_currentPiece)
            {
                p_currentPiece->Move(MOVE_LEFT);
            }
    }
}

void Game::Update()
{
    while(m_window.isOpen())
    {
        HandleEvents();
        ManageGameClock();
        Render();
    }
}

void Game::Run()
{
    Update();
}

void Game::SpawnPiece(PieceType type)
{

    m_pieces.emplace_back(type, m_board);
    p_currentPiece = &m_pieces.back();
    int pieceSize = p_currentPiece->GetPieceArray().size();
    for(int y = 0; y < pieceSize; y++)
    {
        for(int x = 0; x < pieceSize; x++)
        {
            m_board[y][5+x] = p_currentPiece->GetPieceArray()[y][x] * 2;

        }
    }
    m_board.PrintBoard();
}

void Game::DrawPieces(sf::RenderWindow &window)
{
    for(auto& piece : m_pieces)
    {
        window.draw(piece);
    }
}

void Game::ManageGameClock()
{
    static float tickTimeRemaining = m_tickLength;
    tickTimeRemaining -= m_clock.restart().asSeconds();
    if(tickTimeRemaining <= 0)
    {
        Tick();
        tickTimeRemaining = m_tickLength;
    }
}

void Game::Tick()
{
    //Check collision
    p_currentPiece->Fall();

}

