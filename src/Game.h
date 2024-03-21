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
    sf::Event m_event;
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
    std::vector<Piece> m_pieces;
    Piece* p_currentPiece;



    //Game functions
    void SpawnPiece(PieceType type);
    void DrawPieces(sf::RenderWindow& window);
    void ManageGameClock();
    void Tick();
};



#endif //APP_H
