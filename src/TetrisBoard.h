//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef TETRISBOARD_H
#define TETRISBOARD_H
#include <SFML/Graphics.hpp>
#include <array>

#include "Piece.h"

enum PieceType : int;
class Piece;
using std::array;

enum MovementOption {
    MOVE_LEFT = -1,
    MOVE_DOWN = 0,
    MOVE_RIGHT = 1
};

enum RotationOption {
    CLOCKWISE = -1,
    COUNTER_CLOCKWISE = 1
};

class TetrisBoard : public sf::Drawable{

    //10x20 board, with room left over for border collisions
    array<array<uint8_t, 12>,21> m_board;
    sf::RectangleShape m_frame;
    sf::Vector2i m_piecePos;
    std::vector<sf::RectangleShape> m_vRect;
    PieceType m_currentType;
    Piece* p_currentPiece;

public:



    TetrisBoard(Piece* pCurrentPiece);
    bool RotatePiece(RotationOption rotation);
    void FallPiece();
    void MovePiece(MovementOption direction);
    bool WillCollide(MovementOption direction);
    void SetPiece();
    std::vector<int> CheckLines();
    void ClearLine(int line);
    void PrintBoard();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    const sf::Vector2f& getFramePos() const;
    const sf::Vector2i & GetPiecePos() const;
    void SetCurrentPieceType(PieceType type);

    array<uint8_t, 12>& operator [](size_t index);
};



#endif //TETRISBOARD_H
