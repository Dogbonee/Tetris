cmake_minimum_required(VERSION 3.21)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES src/main.cpp
        src/Game.cpp
        src/Game.h
        src/TetrisBoard.cpp
        src/TetrisBoard.h
        src/System.h
        src/Piece.cpp
        src/Piece.h
        src/System.cpp
)



add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window)
