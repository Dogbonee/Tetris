#include "StateMachine.h"
#include <Windows.h>
int main()
{
    ShowWindow( GetConsoleWindow(), SW_HIDE );
    GlobalResources::LoadResources();
    StateMachine sm;

    sm.AddState();
    sm.SwitchState(MENU);
    sm.Run();
    return 0;
}
