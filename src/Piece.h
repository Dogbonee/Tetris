//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include "TetrisBoard.h"

using std::vector;


enum PieceType {

    O_BLOCK = 0,
    I_BLOCK,
    S_BLOCK,
    Z_BLOCK,
    L_BLOCK,
    J_BLOCK,
    T_BLOCK

};

enum MovementOption {
    MOVE_LEFT = -1,
    MOVE_RIGHT = 1
};

typedef vector<vector<bool>> PieceArray;
class Piece : public sf::Drawable{

    PieceArray m_piece;
    vector<sf::RectangleShape> m_pieceVisual;
    TetrisBoard* p_Board;
    int m_type;

    void generatePieceArray(int type);
    void generatePieceVisual();


public:
    Piece(int type, TetrisBoard& gameBoard);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void Move(MovementOption direction);
    void Fall();

    const PieceArray & GetPieceArray() const;
};



#endif //PIECE_H
