#include "Game.h"
#include <Windows.h>
int main()
{
    ShowWindow( GetConsoleWindow(), SW_HIDE );
    Game game;
    game.Run();
    return 0;
}
