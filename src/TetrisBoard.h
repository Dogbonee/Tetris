//
// Created by 24crickenbach on 3/20/2024.
//

#ifndef TETRISBOARD_H
#define TETRISBOARD_H
#include <SFML/Graphics.hpp>
#include <array>

using std::array;


class TetrisBoard : public sf::Drawable{

    //10x20 board, with room left over for border collisions
    array<array<uint8_t, 12>,21> m_board;
    sf::RectangleShape m_frame;

public:
    TetrisBoard();
    void FallPiece();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    const sf::Vector2f& getFramePos() const;
    void PrintBoard();

    array<uint8_t, 12>& operator [](size_t index);
};



#endif //TETRISBOARD_H
