#include "EventHandler.h"
#include "StateMachine.h"

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
        SuperStatePassReset = Resting;
    }
    
    
    switch(SuperStatePassReset)
    {
        case Resting:
        break;

        case PasswordReset:
        break;

        case FirstKeyPress:
        break;

        case SecondKeyPress:
        break;

        case ThirdKeyPress:
        break;

        case PasswordSaved:
        break;

        default:
        SuperStatePassReset = Resting;
        SuperStatePassCheck = Lock;
    }

}

void Events()
{
    
}