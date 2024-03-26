#include "StateMachine.hpp"
#include <Windows.h>
int main()
{
    ShowWindow( GetConsoleWindow(), SW_HIDE );
    GlobalResources::LoadResources();
    StateMachine sm;

    sm.AddState(MENU);
    sm.AddState(GAME);
    sm.SwitchState(MENU);
    sm.Run();
    return 0;
}
