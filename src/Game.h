//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef APP_H
#define APP_H
#include <SFML/graphics.hpp>

#include "Piece.h"
#include "System.h"
#include "TetrisBoard.h"
#include <ctime>
class Game {



    sf::RenderWindow m_window;
    sf::Event m_event{};
    sf::Clock m_clock;
    float m_tickLength;
    float m_defaultTickLength;
    float m_speedTickLength;

    void Render();
    void HandleEvents();
    void HandleKeyboardInput(sf::Keyboard::Key keyCode);
    void Update();



public:
    Game();
    void Run();


private:
    //Game objects
    TetrisBoard m_board;
    TetrisBoard m_ghostBoard;

    Piece m_currentPiece;
    Piece m_nextPiece;
    Piece m_holdPiece;
    Piece m_ghostPiece;
    PieceType m_currentType;

    sf::Vector2f m_nextPiecePosition;
    sf::Vector2f m_holdPiecePosition;

    bool m_hasHeld;
    bool m_hasHeldThisTurn;


    //Game functions
    void SpawnPiece(PieceType type);

    void ManageGameClock();
    bool Tick();
    void MovePieceComponents(MovementOption direction);
    void RotatePieceComponents(RotationOption direction);
    void HandleLineComponents();
    void HandleGhostPiece();
    void ResetGhostPiece();
    void ManageGhostPiece();
    void HandleNextPiece();
    void HoldPiece();
    void DropPiece();
    void GameOver();
};



#endif //APP_H
