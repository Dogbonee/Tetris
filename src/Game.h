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

#include "State.hpp"

class Game : public State{


    sf::Clock m_clock;
    float m_tickLength;
    float m_defaultTickLength;
    float m_speedTickLength;

    void Render() override;
    void HandleKeyboardInput(sf::Keyboard::Key keyCode) override;
    void Update() override;



public:
    Game(StateMachine &sm, sf::RenderWindow &window);
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

    unsigned long m_score;

    //UI
    sf::Text m_scoreText;
    sf::Text m_scoreLabel;
    sf::Text m_nextLabel;
    sf::Text m_holdLabel;
    sf::Font m_textFont;

    void setScore();




    //Game functions
    void SpawnPiece(PieceType type);

    void ManageGameClock();
    bool Tick();
    void MovePieceComponents(MovementOption direction);
    void RotatePieceComponents(RotationOption direction);
    void HandleScoring();
    void HandleGhostPiece();
    void ResetGhostPiece();
    void ManageGhostPiece();
    void HandleNextPiece();
    void HoldPiece();
    void DropPiece();
    void GameOver();
};



#endif //APP_H
