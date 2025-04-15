#include "EventHandler.h"
#include "StateMachine.h"

uint32_t currentTime = 0;
uint32_t lastActivity = 0;
bool flagBuzzer = false;
char keyInput = '\0';
char passKey1 = '2';
char passKey2 = '2';
char passKey3 = '3';

void StateMachine()
{
    if(ScanKeypad() != '\0')
    {
        keyInput = ScanKeypad();
        return;
    }
    
    currentTime = millis();

    if(currentTime - lastActivity >= 500 && flagBuzzer)
    {
        StopBuzzer();
        flagBuzzer = false;
    }
    
    if(currentTime - lastActivity < 500 && flagBuzzer)
    {
        return;
    }

    switch(SuperStatePassCheck)
    {
        case Lock:
        TurnOffLED();
        if(keyInput == passKey1) 
        {
            SuperStatePassCheck = Key1Press;
        }
        else
        {
            SuperStatePassCheck = Lock;
            BuzzerEvent();
        }
        break;

        case Key1Press:
        if(keyInput == passKey2)
        {
            SuperStatePassCheck = Key2Press;
        }
        else
        {
            SuperStatePassCheck = Lock;
            BuzzerEvent();
        }
        break;

        case Key2Press:
        if(keyInput == passKey3)
        {
            SuperStatePassCheck = Unlock;
            TurnOnLED();
        }
        else
        {
            SuperStatePassCheck = Lock;
            BuzzerEvent();
        }
        break;

        case Unlock:
        if(CheckIfA())
        {
            SuperStatePassCheck = Idle;
            SuperStatePassReset = PasswordReset;
        }
        else SuperStatePassCheck = Lock;
        break;

        case Idle:
        // Eat 5 star, do nothing.
        break;

        default:
        SuperStatePassCheck = Lock;
        SuperStatePassReset = Resting;
    }
    
    
    switch(SuperStatePassReset)
    {
        case Resting:
        // Have a break, have a KitKat
        break;

        case PasswordReset:
        if(CheckIfAlphabet())
        {
            SuperStatePassReset = Resting;
            SuperStatePassCheck = Lock;
            ResetPass();
        }
        else
        {
            SuperStatePassReset = FirstKeyInput;
            passKey1 = keyInput;
        }
        break;

        case FirstKeyInput:
        if(CheckIfAlphabet())
        {
            SuperStatePassReset = Resting;
            SuperStatePassCheck = Lock;
            ResetPass();
        }
        else
        {
            SuperStatePassReset = SecondKeyInput;
            passKey2 = keyInput;
        }
        break;

        case SecondKeyInput:
        if(CheckIfAlphabet())
        {
            SuperStatePassReset = Resting;
            SuperStatePassCheck = Lock;
            ResetPass();
        }
        else
        {
            SuperStatePassReset = PasswordSaved;
        }
        break;

        case PasswordSaved:
        Serial.print("!! Password Saved !!\nNew Password is: ");
        Serial.print(passKey1);
        Serial.print(passKey2);
        Serial.println(passKey3);
        SuperStatePassReset = Resting;
        SuperStatePassCheck = Lock;
        break;

        default:
        SuperStatePassReset = Resting;
        SuperStatePassCheck = Lock;
    }

}



void BuzzerEvent()
{
    flagBuzzer = true;
    BuzzBuzzer();
    lastActivity = currentTime;
}


bool CheckIfA()
{
    if(keyInput == 'A') return true;
    else return false;
}


bool CheckIfAlphabet()
{
    switch(keyInput)
    {
        // case 'A':
        case 'B':
        case 'C':
        case 'D':
        case '*':
        case '#':
        return true;

        default:
        return false;
    }
}


void ResetPass()
{
    passKey1 = '2';
    passKey2 = '2';
    passKey3 = '3';
    Serial.println("!! Password reset to default !!");
}