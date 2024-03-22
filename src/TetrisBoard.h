//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef TETRISBOARD_H
#define TETRISBOARD_H
#include <SFML/Graphics.hpp>
#include <array>
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


public:
    TetrisBoard();
    void RotatePiece(RotationOption rotation);
    void FallPiece();
    void MovePiece(MovementOption direction);
    bool WillCollide(MovementOption direction);
    void SetPiece();
    void CheckLines();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    const sf::Vector2f& getFramePos() const;
    void PrintBoard();

    const sf::Vector2i & GetPiecePos() const;

    array<uint8_t, 12>& operator [](size_t index);
};



#endif //TETRISBOARD_H
