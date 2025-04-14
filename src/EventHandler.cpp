#include "EventHandler.h"

uint32_t currentTime = 0;
uint32_t lastActivity = 0;

void StateMachine()
{
    
    switch(SuperStatePassCheck)
    {
        case Lock:
        TurnOffLED();

        break;

        case Key1Press:
        break;

        case Key2Press:
        break;

        case Key3Press:
        break;

        case Unlock:
        break;

        case Idle:
        break;

        default:
        SuperStatePassCheck = Lock;
        SuperStatePassReset = Idle;
    }
    
    
    switch(SuperStatePassReset)
    {
        case Idle:
        break;

        case PasswordReset:
        break;

        case Key1Press:
        break;

        case Key2Press:
        break;

        case Key3Press:
        break;

        case PasswordSaved:
        break;

        default:
        SuperStatePassReset = Idle;
        SuperStatePassCheck = Lock;
    }

}

void Events()
{
    
}