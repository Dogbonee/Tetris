//
// Created by 24crickenbach on 3/20/2024.
//

#include "TetrisBoard.h"

#include <iostream>





TetrisBoard::TetrisBoard(Piece* pCurrentPiece) : m_piecePos(5,0), p_currentPiece(pCurrentPiece)
{
    m_frame.setSize(sf::Vector2f(252, 500));
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
bool TetrisBoard::RotatePiece(RotationOption rotation)
{
    //So much better than last algorithm i.e actually works (most of the time) still has some bugs later in the game so we need to check that
    if(m_currentType == O_BLOCK)return false;

    int n = 3 + (m_currentType == I_BLOCK);

    int arr[4][4];
    int rotatedArr[4][4];

    //Hack to avoid sigsegv when rotating i piece at border
    if(m_currentType == I_BLOCK && m_piecePos.x > 7) return false;
    for(int i = m_piecePos.y; i < m_piecePos.y + n; i++)
    {
        for(int j = m_piecePos.x; j < m_piecePos.x + n; j++)
        {
            try
            {
                //Try to populate array with m_board
                arr[i-m_piecePos.y][j-m_piecePos.x] = m_board[i].at(j) != 1 ? m_board[i][j] : 0;
            }catch(std::out_of_range& e)
            {
                return false;
            }
        }
    }


    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            rotatedArr[n-1-i][j] = arr[n-1-j][n-1-i];
        }
    }

    for(int i = m_piecePos.y; i < m_piecePos.y + n; i++)
    {
        for(int j = m_piecePos.x; j < m_piecePos.x + n; j++)
        {
            if(rotatedArr[i-m_piecePos.y][j-m_piecePos.x] - 1 == m_board[i][j])
            {
                return false;
            }
        }
    }


    for(int i = m_piecePos.y; i < m_piecePos.y + n; i++)
    {
        for(int j = m_piecePos.x; j < m_piecePos.x + n; j++)
        {
            m_board[i][j] = m_board[i][j] == 1 ? 1 : rotatedArr[i-m_piecePos.y][j-m_piecePos.x];
        }

    }

    return true;
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

                sf::RectangleShape rect(sf::Vector2f(System::PIECE_SIZE, System::PIECE_SIZE));
                rect.setPosition(System::PIECE_SIZE * x + System::X_OFFSET, System::PIECE_SIZE * (y-1) + System::Y_OFFSET - System::PIECE_SIZE/2);
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(1);
                rect.setFillColor(System::ColorPiece(p_currentPiece->GetType()));
                m_vRect.push_back(rect);


            }
        }
    }
    ResetPiece();


}

void TetrisBoard::ResetPiece()
{
    m_piecePos = sf::Vector2i(5,0);
}

std::vector<int> TetrisBoard::CheckLines()
{
    std::vector<int> completedLines;
    for(int y = 0; y < m_board.size() - 1; y++)
    {
        bool lineComplete = true;
        for(int x = 1; x < m_board[0].size()-1; x++)
        {
            if(m_board[y][x] != 1)
            {
                lineComplete = false;

            }
        }
        if(lineComplete)
        {
            completedLines.push_back(y);
        }
    }
    for(const auto line : completedLines)
    {
        ClearLine(line);
    }
    return completedLines;
}

void TetrisBoard::ClearLine(const int line)
{
    std::cout<<"Clearing line " <<line <<"\n";
    for(int i = 1; i < m_board[0].size()-1; i++)
    {
        m_board[line][i] = 0;
    }
    for(int y = 0; y <= line; y++)
    {
        for(int x = 1; x < m_board[0].size()-1; x++)
        {
            //only affect collision pieces
            if(m_board[y][x] < 1) continue;
            //if board is the piece and has not been affected (2), move the piece num down in the board and set it as affected (3)
            if(m_board[y][x] == 1)
            {
                m_board[y+1][x] += 3;
                m_board[y][x] = 0;
            }
            //if board is the piece and has been affected (3), set it to not affected (2) and continue.
            //This prevents an infinite loop of m_board[y+1][x] always being moved down
            if(m_board[y][x] == 3)
            {
                m_board[y][x] = 1;
            }
            //if board is the piece and has been affected and needs to move down again, increment the next one down
            //and set it equal to not affected. This occurs when a piecenum that needs to move down moves onto another piecenum
            if(m_board[y][x] == 4)
            {
                m_board[y+1][x] += 3;
                m_board[y][x] = 1;
            }
        }
    }



    for(int i = 0; i < m_vRect.size(); i++)
    {
        if(m_vRect[i].getPosition().y == (line - 1) * System::PIECE_SIZE + System::Y_OFFSET - System::PIECE_SIZE/2)
        {
            m_vRect.erase(m_vRect.begin() + i);
            i--;
        }
    }
    for(auto& rect : m_vRect)
    {
        if(rect.getPosition().y < (line - 1) * System::PIECE_SIZE + System::Y_OFFSET - System::PIECE_SIZE/2)
        {
            rect.move(0, System::PIECE_SIZE);
        }
    }

}


void TetrisBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_frame, states);
    for(auto& i : m_vRect)
    {
        target.draw(i);
    }
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

const array<array<uint8_t, 12>, 21> & TetrisBoard::GetBoard() const
{
    return m_board;
}

void TetrisBoard::SetCurrentPieceType(PieceType type)
{
    m_currentType = type;
}

array<uint8_t, 12>& TetrisBoard::operator[](size_t index)
{
    return m_board[index];
}

TetrisBoard & TetrisBoard::operator=(TetrisBoard board)
{
    m_board = board.GetBoard();
    return *this;
}


