//
// Created by 24crickenbach on 3/20/2024.
//

#include "TetrisBoard.h"

#include <iostream>

#include "System.h"

TetrisBoard::TetrisBoard()
{
    m_frame.setSize(sf::Vector2f(250, 500));
    m_frame.setFillColor(sf::Color::Transparent);
    m_frame.setOutlineColor(sf::Color::Red);
    m_frame.setOutlineThickness(30);
    m_frame.setOrigin(m_frame.getSize().x/2, m_frame.getSize().y/2);
    m_frame.setPosition(System::WIDTH/2, System::HEIGHT/2);

    for(int y = 0; y < m_board.size(); y++)
    {
        for(int x = 0; x < m_board[0].size(); x++)
        {
            m_board[y][x] = 0;
        }
    }
    for(int i = 0; i < 20; i++)
    {
        m_board[i][0] = true;
        m_board[i][11] = true;
        m_board[20][i/2 + 1] = true;
    }
    for(int y = 0; y < m_board.size(); y++)
    {
        for(int x = 0; x < m_board[0].size(); x++)
        {
            std::cout<<m_board[y][x] << " ";
        }
        std::cout<<std::endl;
    }

}

void TetrisBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_frame, states);
}

const sf::Vector2f & TetrisBoard::getFramePos() const
{
    return m_frame.getPosition();
}


