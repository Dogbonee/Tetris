//
// Created by 24crickenbach on 3/20/2024.
//

#include "TetrisBoard.h"

#include <iostream>

#include "System.h"



TetrisBoard::TetrisBoard() : m_piecePos(5,0)
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


}

//TODO: change rotation algorithm to one with O(1) extra space
void TetrisBoard::RotatePiece(RotationOption rotation)
{
    //So much better than last algorithm i.e actually works (most of the time) still has some bugs later in the game so we need to check that
    int arr[3][3];
    int rotatedArr[3][3];
    for(int i = m_piecePos.y; i < m_piecePos.y + 3; i++)
    {
        for(int j = m_piecePos.x; j < m_piecePos.x + 3; j++)
        {
            if(m_board[i][j] != 1)
            {
                arr[i-m_piecePos.y][j-m_piecePos.x] = m_board[i][j];
            }
        }
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            rotatedArr[2-i][j] = arr[2-j][2-i];
        }
    }

    for(int i = m_piecePos.y; i < m_piecePos.y + 3; i++)
    {
        for(int j = m_piecePos.x; j < m_piecePos.x + 3; j++)
        {
            m_board[i][j] = rotatedArr[i-m_piecePos.y][j-m_piecePos.x];
            if(m_board[i][j] > 5)
            {
                std::cout<<"Game array has been corrupted\n";
                exit(1);
            }
        }
    }

}

void TetrisBoard::FallPiece()
{
    for(int y = 0; y < m_board.size(); y++)
    {
        for(int x = 0; x < m_board[0].size(); x++)
        {
            //if board is not the piece, return
            if(m_board[y][x] < 2) continue;
            //if board is the piece and has not been affected (2), move the piece num down in the board and set it as affected (3)
            if(m_board[y][x] == 2)
            {
                m_board[y+1][x] += 3;
                m_board[y][x] = 0;
            }
            //if board is the piece and has been affected (3), set it to not affected (2) and continue.
            //This prevents an infinite loop of m_board[y+1][x] always being moved down
            if(m_board[y][x] == 3)
            {
                m_board[y][x] = 2;
            }
            //if board is the piece and has been affected and needs to move down again, increment the next one down
            //and set it equal to not affected. This occurs when a piecenum that needs to move down moves onto another piecenum
            if(m_board[y][x] == 5)
            {
                m_board[y+1][x] += 3;
                m_board[y][x] = 2;
            }
        }
    }
    m_piecePos.y++;
}

void TetrisBoard::MovePiece(MovementOption direction)
{
    for(int y = 0; y < m_board.size(); y++)
    {
        //The for loop has to run in the direction the piece is moving, otherwise affected piecenums (3) will not be set to two.
        //This abonination of a for loop sets the directon of the for loop to run right->left if the direction is left,
        //otherwise run left->right
        for(int x = (m_board[0].size() - 1) * (direction == MOVE_LEFT); x != (m_board[0].size() - 1) * (direction == MOVE_RIGHT); x+=direction)
        {
            //if board is not the piece, return
            if(m_board[y][x] < 2) continue;
            //if board is the piece and has not been affected (2), move the piece num over in the board and set it as affected (3)
            if(m_board[y][x] == 2)
            {
                m_board[y][x+direction] += 3;
                m_board[y][x] = 0;
            }
            //if board is the piece and has been affected (3), set it to not affected (2) and continue.
            //This prevents an infinite loop of m_board[y][x + dir] always being moved over
            if(m_board[y][x] == 3)
            {
                m_board[y][x] = 2;
            }
            //if board is the piece and has been affected and needs to move down again, increment the next one over
            //and set it equal to not affected. This occurs when a piecenum that needs to move over moves onto another piecenum
            if(m_board[y][x] == 5)
            {
                m_board[y][x+direction] += 3;
                m_board[y][x] = 2;
            }

        }
    }
    m_piecePos.x += direction;
}

bool TetrisBoard::WillCollide(MovementOption direction)
{
    uint8_t movingDown = direction == 0;
    std::vector<sf::Vector2i> pieceCoords;
    for(int y = 0; y < m_board.size(); y++)
    {
        for(int x = 0; x < m_board[0].size(); x++)
        {
            if(m_board[y][x] == 2)
            {
                pieceCoords.emplace_back(x,y);
            }
        }
    }
    for(auto& coord : pieceCoords)
    {
        if(m_board[coord.y + movingDown][coord.x+direction] == 1)
        {
            return true;
        }
    }

    return false;
}

void TetrisBoard::SetPiece()
{
    std::vector<sf::Vector2i> pieceCoords;
    for(int y = 0; y < m_board.size(); y++)
    {
        for(int x = 0; x < m_board[0].size(); x++)
        {
            if(m_board[y][x] == 2)
            {
                m_board[y][x] = 1;
            }
        }
    }
    m_piecePos = sf::Vector2i(5,0);
}

void TetrisBoard::CheckLines()
{
    std::vector<int> completedLines;
    for(int y = 0; y < completedLines.size() - 1; y++)
    {
        bool lineComplete = true;
        for(int x = 0; x < m_board[0].size(); x++)
        {
            if(m_board[m_board.size() - y][x] != 1)
            {
                lineComplete = false;
            }
        }
        if(lineComplete)
        {
            completedLines.push_back(m_board.size() - y);
        }
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

void TetrisBoard::PrintBoard()
{
    for(int y = 0; y < m_board.size(); y++)
    {
        for(int x = 0; x < m_board[0].size(); x++)
        {
            printf("%d ", m_board[y][x]);
        }
        printf("\n");
    }
    printf("\n\n");
}

const sf::Vector2i & TetrisBoard::GetPiecePos() const
{
    return m_piecePos;
}

array<uint8_t, 12>& TetrisBoard::operator[](size_t index)
{
    return m_board[index];
}


