//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include <SFML/System/Vector2.hpp>
#include "Piece.h"

class System {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    static constexpr float PIECE_SIZE = 25;
    static constexpr int X_MIDDLE = WIDTH/2 + 13;
    static constexpr int X_OFFSET = X_MIDDLE - PIECE_SIZE * 6 - PIECE_SIZE/2;
    static constexpr int Y_OFFSET = 85;


    static sf::Color ColorPiece(PieceType type);
};




#endif //SYSTEM_H
