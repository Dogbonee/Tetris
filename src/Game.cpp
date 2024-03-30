//
// Created by 24crickenbach on 3/20/2024.
//

#include "Game.h"



Game::Game(StateMachine &sm, sf::RenderWindow &window) : State(sm, window),
                                                         m_tickLength(m_defaultTickLength),
                                                         m_defaultTickLength(System::m_levelOneTick),
                                                         m_speedTickLength(m_defaultTickLength / 10), m_board(&m_currentPiece),
                                                         m_ghostBoard(&m_ghostPiece), m_currentPiece(O_BLOCK),
                                                         m_nextPiece(O_BLOCK),
                                                         m_holdPiece(O_BLOCK),
                                                         m_ghostPiece(m_currentPiece),
                                                         m_nextPiecePosition(650, 100), m_holdPiecePosition(650, 250),
                                                         m_hasHeld(false), m_hasHeldThisTurn(false), m_isGameOver(false), m_score(0)
{
    if (!GlobalResources::BlockFont.loadFromFile("../res/Pixeboy.ttf"))
    {
        std::cout << "Font could not be loaded!\n";
    }

    m_scoreLabel.setFont(GlobalResources::BlockFont);
    m_scoreLabel.setCharacterSize(60);
    m_scoreLabel.setPosition(50, 100);
    m_scoreLabel.setString("Score");
    m_nextLabel.setFont(GlobalResources::BlockFont);
    m_nextLabel.setCharacterSize(40);
    m_nextLabel.setPosition(605, 20);
    m_nextLabel.setString("Next");
    m_holdLabel.setFont(GlobalResources::BlockFont);
    m_holdLabel.setCharacterSize(40);
    m_holdLabel.setPosition(605, 170);
    m_holdLabel.setString("Hold");
    m_scoreText.setFont(GlobalResources::BlockFont);
    m_scoreText.setCharacterSize(40);
    setScore();

    m_fpsCounter.setFont(GlobalResources::BlockFont);
    m_fpsCounter.setPosition(20,20);
    m_fpsCounter.setCharacterSize(30);

    //Init all ui before this point
    std::srand(std::time(nullptr));
    SpawnPiece(static_cast<PieceType>(std::rand() % 7));
    m_ghostPiece = m_currentPiece;
    HandleNextPiece();
    ManageGhostPiece();
}

void Game::Render()
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
    //DrawPieces(m_window);
    p_window->display();
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
        case sf::Keyboard::C:
            if(!m_hasHeldThisTurn)
            {
                HoldPiece();
            }
            break;
    }
}

void Game::Update()
{
    //should handle in other function in future
    m_tickLength = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? m_speedTickLength : m_defaultTickLength;
    HandleEvents();
    ManageGameClock();
    Render();
}

void Game::Run()
{
    Update();
}

void Game::setScore()
{
    m_scoreText.setString(std::to_string(m_score));
    sf::FloatRect textRect = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);
    m_scoreText.setPosition(120,200);
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
            if(m_board[y][5+x] > 5)
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
        m_fpsCounter.setString("FPS: " + std::to_string(static_cast<int>(round(1/m_clock.restart().asSeconds()))));
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
    HandleScoring();
    //m_board.PrintBoard();
    SpawnPiece(m_nextPiece.GetType());
    HandleNextPiece();
    ManageGhostPiece();
    m_hasHeldThisTurn = false;

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

void Game::HandleScoring()
{
    std::vector<int> completedLines = m_board.CheckLines();
    if(completedLines.size() == 0)return;
    int earnedScore = 0;
    switch(completedLines.size())
    {
        case 1:
            earnedScore = 100;
            break;
        case 2:
            earnedScore = 300;
            break;
        case 3:
            earnedScore = 600;
            break;
        case 4:
            earnedScore = 1000;
            break;
    }
    m_score += earnedScore;

    if(m_score > 4000)
    {
        m_defaultTickLength =System::m_levelTwoTick;
    }
    if(m_score > 12000)
    {
        m_defaultTickLength =System::m_levelThreeTick;
    }
    if(m_score > 24000)
    {
        m_defaultTickLength =System::m_levelFourTick;
    }
    if(m_score > 40000)
    {
        m_defaultTickLength =System::m_levelFiveTick;
    }
    if(m_score > 60000)
    {
        m_defaultTickLength =System::m_levelSixTick;
    }
    m_speedTickLength = m_defaultTickLength / 10;
    std::cout<<"Score: "<<m_score << " Tick length: " << m_defaultTickLength << '\n';
    setScore();
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

void Game::HandleNextPiece()
{
    m_nextPiece = {static_cast<PieceType>(std::rand() % 7)};
    m_nextPiece.SetPosition(m_nextPiecePosition);
    if(m_nextPiece.GetType() == I_BLOCK || m_nextPiece.GetType() == O_BLOCK)
    {
        m_nextPiece.SetPosition(sf::Vector2f(m_nextPiecePosition.x, m_nextPiecePosition.y + System::PIECE_SIZE));
    }
}

void Game::HoldPiece()
{

    //clear currentpiece from board
    for(int y = 0; y < 21; y++)
    {
        for(int x = 0; x < 12; x++)
        {
            if(m_board[y][x] == 2)
            {
                m_board[y][x] = 0;

            }
        }
    }

    PieceType currentType = m_currentType;
    SpawnPiece(m_hasHeld ? m_holdPiece.GetType() : m_nextPiece.GetType());
    m_holdPiece = {currentType};
    m_holdPiece.SetPosition(m_holdPiecePosition);
    if(m_holdPiece.GetType() == I_BLOCK || m_holdPiece.GetType() == O_BLOCK)
    {
        m_holdPiece.SetPosition(sf::Vector2f(m_holdPiecePosition.x, m_holdPiecePosition.y + System::PIECE_SIZE));
    }
    m_board.ResetPiece();
    m_ghostBoard.ResetPiece();
    ManageGhostPiece();
    m_hasHeld = true;
    m_hasHeldThisTurn = true;
}

void Game::DropPiece()
{
    while(Tick());
}

void Game::GameOver()
{
    m_isGameOver = true;
    m_gameOverScreen.SetGameOverScore(m_score);
}

