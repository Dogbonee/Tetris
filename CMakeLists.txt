cmake_minimum_required(VERSION 3.21)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR C:/StudentFiles/Student/SFML-2.6.1/lib/cmake/SFML)
set(SOURCE_FILES src/main.cpp
        src/Game.cpp
        src/Game.h
        src/TetrisBoard.cpp
        src/TetrisBoard.h
        src/System.cpp
        src/System.h
        src/Piece.cpp
        src/Piece.h
        src/State.cpp
        src/State.hpp
        src/StateMachine.cpp
        src/StateMachine.hpp
        src/Menu.cpp
        src/Menu.h
        src/ResourceLoader.cpp
        src/ResourceLoader.h
        src/Button.cpp
        src/Button.h
        src/GameOver.cpp
        src/GameOver.h
)
set(SFML_STATIC_LIBRARIES TRUE)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SFML 2.6 COMPONENTS graphics REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics)