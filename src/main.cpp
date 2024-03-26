#include "StateMachine.hpp"
#include <Windows.h>
int main()
{
    ShowWindow( GetConsoleWindow(), SW_HIDE );
    StateMachine sm;

    sm.AddState(GAME);
    sm.SwitchState(GAME);
    sm.Run();
    return 0;
}
