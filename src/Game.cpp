//
// Created by 24crickenbach on 3/20/2024.
//

#include "Game.h"

#include <iostream>

Game::Game() : m_window{sf::VideoMode(System::WIDTH, System::HEIGHT), "Tetris"}, m_board(&m_currentPiece),
               m_ghostBoard(&m_ghostPiece),
               m_currentPiece(O_BLOCK), m_ghostPiece(m_currentPiece), m_defaultTickLength(1.0f),
               m_speedTickLength(0.1f), m_tickLength(m_defaultTickLength)
{
    std::srand(std::time(nullptr));
    SpawnPiece(static_cast<PieceType>(std::rand() % 7));
    m_ghostPiece = m_currentPiece;
    ManageGhostPiece();
}

void Game::Render()
{
    m_window.clear();
    m_window.draw(m_board);
    m_window.draw(m_currentPiece);
    if(m_currentPiece.GetPosition() != m_ghostPiece.GetPosition())
    {
        m_window.draw(m_ghostPiece);
    }
    //DrawPieces(m_window);
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
            if(!m_board.WillCollide(MOVE_RIGHT))
            {
                MovePieceComponents(MOVE_RIGHT);
            }
            break;
        case sf::Keyboard::Left:
            if(!m_board.WillCollide((MOVE_LEFT)))
            {
                MovePieceComponents(MOVE_LEFT);
            }
            break;
        case sf::Keyboard::Up:
            RotatePieceComponents(CLOCKWISE);
            break;
        case sf::Keyboard::Space:
            DropPiece();
            break;
    }
}

void Game::Update()
{
    while(m_window.isOpen())
    {
        //should handle in other function in future
        m_tickLength = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? m_speedTickLength : m_defaultTickLength;
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
    Piece piece(type);
    m_currentPiece = piece;
    m_currentType = type;
    m_board.SetCurrentPieceType(type);
    int pieceSize = m_currentPiece.GetPieceArray().size();
    for(int y = 0; y < pieceSize; y++)
    {
        for(int x = 0; x < pieceSize; x++)
        {
            if(m_board[y][5+x] == 1)
            {
                GameOver();
            }
            m_board[y][5+x] = m_currentPiece.GetPieceArray()[y][x] * 2;

        }
    }

}



void Game::ManageGameClock()
{
    static float tickTimeRemaining = m_tickLength;
    tickTimeRemaining -= m_clock.restart().asSeconds();

    if(tickTimeRemaining <= 0 || tickTimeRemaining > m_tickLength)
    {
        Tick();
        tickTimeRemaining = m_tickLength;
    }
}

bool Game::Tick()
{
    //Returns whether piece can tick again without colliding
    //Check collision
    if(!m_board.WillCollide(MOVE_DOWN))
    {
        m_currentPiece.Fall();
        m_board.FallPiece();
        return true;
    }

    m_board.SetPiece();
    HandleLineComponents();
    //m_board.PrintBoard();
    SpawnPiece(static_cast<PieceType>(std::rand() % 7));
    ManageGhostPiece();
    return false;
}

void Game::MovePieceComponents(MovementOption direction)
{
    m_currentPiece.Move(direction);
    m_board.MovePiece(direction);
    ManageGhostPiece();
}

void Game::RotatePieceComponents(RotationOption direction)
{
    if(m_currentType == O_BLOCK) return;
    if(m_board.RotatePiece(direction))
    {
        m_currentPiece.RotateVisual(direction);
        ManageGhostPiece();
    }
}

void Game::HandleLineComponents()
{
    std::vector<int> completedLines = m_board.CheckLines();
}

void Game::HandleGhostPiece()
{
    while(!m_ghostBoard.WillCollide(MOVE_DOWN))
    {
        m_ghostPiece.Fall();
        m_ghostBoard.FallPiece();
    }
}

void Game::ResetGhostPiece()
{
    m_ghostPiece = m_currentPiece;
    m_ghostPiece.MakeTransparent();
}

void Game::ManageGhostPiece()
{
    m_ghostBoard = m_board;
    ResetGhostPiece();
    HandleGhostPiece();
}

void Game::DropPiece()
{
    while(Tick());
}

void Game::GameOver()
{
    std::cout<<"Game over!\n";
    exit(0);
}

