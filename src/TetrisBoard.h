//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef TETRISBOARD_H
#define TETRISBOARD_H
#include <array>
#include "System.h"

#include "Piece.h"

enum PieceType : int;

class Piece;
using std::array;

using Board = std::vector<std::vector<int>>;


enum MovementOption : int{
    MOVE_LEFT = -1,
    MOVE_DOWN = 0,
    MOVE_RIGHT = 1
};

enum RotationOption : int{
    CLOCKWISE = -1,
    COUNTER_CLOCKWISE = 1
};

class TetrisBoard : public sf::Drawable{

    //10x20 board, with room left over for border collisions
    Board m_board;
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
    void AddRect(PieceType type, sf::Vector2i pos);
    void ResetPiece();
    std::vector<int> CheckLines();
    void ClearLine(int line);
    void PrintBoard();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    const sf::Vector2f& getFramePos() const;
    const sf::Vector2i & GetPiecePos() const;
    const Board & GetBoard()const;
    void SetCurrentPieceType(PieceType type);

    std::vector<int>& operator [](size_t index);
    TetrisBoard& operator =(TetrisBoard board);
};



#endif //TETRISBOARD_H
