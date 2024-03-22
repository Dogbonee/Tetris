//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <SFML/Graphics.hpp>

#include "TetrisBoard.h"

using std::vector;

class TetrisBoard;

enum PieceType {

    O_BLOCK = 0,
    I_BLOCK,
    S_BLOCK,
    Z_BLOCK,
    L_BLOCK,
    J_BLOCK,
    T_BLOCK

};



typedef vector<vector<uint8_t>> PieceArray;
class Piece : public sf::Drawable{

    PieceArray m_piece;
    vector<sf::RectangleShape> m_pieceVisual;
    int m_type;

    void generatePieceArray(int type);
    void generatePieceVisual();


public:
    Piece(int type);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void Move(MovementOption direction);
    void Fall();
    void Rotate(RotationOption direction);

    const PieceArray & GetPieceArray() const;
};



#endif //PIECE_H
