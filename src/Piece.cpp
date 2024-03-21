//
// Created by 24crickenbach on 3/20/2024.
//

#include "Piece.h"

#include <iostream>

#include "System.h"


Piece::Piece(int type, TetrisBoard &gameBoard) : p_Board(&gameBoard)
{
    m_type = type;

    generatePieceArray(type);
    generatePieceVisual();

}



void Piece::generatePieceArray(int type)
{
    switch(type)
    {
        case O_BLOCK:
            m_piece = {{1,1},
                        {1,1}};
        break;
        case I_BLOCK:
            m_piece = {
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0}};
        break;
        case S_BLOCK:
            m_piece = {
            {0,0,0},
            {0,1,1},
            {1,1,0}};
            break;
        case Z_BLOCK:
            m_piece = {
            {0,0,0},
            {1,1,0},
            {0,1,1}};
        case L_BLOCK:
            m_piece = {
            {0,0,0},
            {1,0,0},
            {1,1,1}};
            break;
        case J_BLOCK:
            m_piece = {
            {0,0,0},
            {0,0,1},
            {1,1,1}};
            break;
        case T_BLOCK:
            m_piece = {
            {0,0,0},
            {0,1,0},
            {1,1,1}};
            break;

        default:
            std::cout<<"Illegal piece type specified\n";
        exit(1);
    }

}

void Piece::generatePieceVisual()
{

    for(int y = 0; y < m_piece.size(); y++)
    {
        for(int x = 0; x < m_piece[0].size(); x++)
        {
            if(m_piece[y][x])
            {
                sf::RectangleShape rect(sf::Vector2f(System::PIECE_SIZE, System::PIECE_SIZE));
                rect.setPosition(System::WIDTH/2 + x * System::PIECE_SIZE, 100 - (m_piece.size() - y) * System::PIECE_SIZE);
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(2);
                switch(m_type)
                {
                    case O_BLOCK:
                        rect.setFillColor(sf::Color::Yellow);
                    break;
                }
                m_pieceVisual.push_back(rect);
            }
        }
    }

}

void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto& rect : m_pieceVisual)
    {
        target.draw(rect);
    }
}

void Piece::Move(MovementOption direction)
{
    for(auto& piece : m_pieceVisual)
    {
        piece.move(System::PIECE_SIZE * direction, 0);
    }
}

void Piece::Fall()
{
    for(auto& piece : m_pieceVisual)
    {
        piece.move(0, System::PIECE_SIZE);
    }
}

const PieceArray & Piece::GetPieceArray() const
{
    return m_piece;
}
