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
    array<array<bool, 12>,21> m_board;
    sf::RectangleShape m_frame;

public:
    TetrisBoard();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    const sf::Vector2f& getFramePos() const;

};



#endif //TETRISBOARD_H
