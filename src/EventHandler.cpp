#include "EventHandler.h"
#include "StateMachine.h"

SuperStateCheck SuperStatePassCheck = Lock;
SuperStateReset SuperStatePassReset = Resting;


void BuzzerEvent();
bool CheckIfA();
bool CheckIfAlphabet();
void ResetPass();


uint32_t currentBuzzerTime = 0;
uint32_t lastBuzzerActivity = 0;
bool flagBuzzer = false;
char keyInput = '\0';
char passKey1 = '2';
char passKey2 = '2';
char passKey3 = '3';


void StateMachine()
{
    currentBuzzerTime = millis();
    if(currentBuzzerTime - lastBuzzerActivity >= 500 && flagBuzzer)
    {
        StopBuzzer();
        flagBuzzer = false;
        return;
    }
    
    if(currentBuzzerTime - lastBuzzerActivity < 500 && flagBuzzer)
    {
        return;
    }

    /////////////////////////////////////////////////////////////////////////

    keyInput = ScanKeypad();
    if(keyInput == '\0' && SuperStatePassCheck != Unlock && SuperStatePassReset != PasswordSaved) 
    {
        return;
    }
    
    /////////////////////////////////////////////////////////////////////////

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
            TurnOffLED();
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
            TurnOffLED();
            BuzzerEvent();
        }
        break;

        case Unlock:
        TurnOnLED();
        SuperStatePassCheck = UnlockActions;
        break;

        case UnlockActions:
        if(CheckIfA())
        {
            Serial.println("!! Resetting Password !!");
            SuperStatePassCheck = Idle;
            SuperStatePassReset = PasswordReset;
            return;
        }
        else 
        {   
            SuperStatePassCheck = Lock;
            TurnOffLED();
            BuzzBuzzer();
        }
        break;

        case Idle:
        // Eat 5 star, do nothing.
        break;

        default:
        SuperStatePassCheck = Lock;
        SuperStatePassReset = Resting;
    }
    
    /////////////////////////////////////////////////////////////////////////

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
            TurnOffLED();
            ResetPass();
            return;
        }
        else
        {
            SuperStatePassReset = FirstKeyInput;
            passKey1 = keyInput;
            Serial.println("!! First Input Updated !!");
        }
        break;

        case FirstKeyInput:
        if(CheckIfAlphabet())
        {
            SuperStatePassReset = Resting;
            SuperStatePassCheck = Lock;
            TurnOffLED();
            ResetPass();
            return;
        }
        else
        {
            SuperStatePassReset = SecondKeyInput;
            passKey2 = keyInput;
            Serial.println("!! Second Input updated !!");
        }
        break;

        case SecondKeyInput:
        if(CheckIfAlphabet())
        {
            SuperStatePassReset = Resting;
            SuperStatePassCheck = Lock;
            TurnOffLED();
            ResetPass();
            return;
        }
        else
        {
            SuperStatePassReset = PasswordSaved;
            passKey3 = keyInput;
            Serial.println("!! Third Key Updated !!");
        }
        break;

        case PasswordSaved:
        Serial.print("!! Password Saved !!\nNew Password is: ");
        Serial.print(passKey1);
        Serial.print(passKey2);
        Serial.println(passKey3);
        Serial.println();
        SuperStatePassReset = Resting;
        SuperStatePassCheck = Lock;
        TurnOffLED();
        break;

        default:
        SuperStatePassReset = Resting;
        SuperStatePassCheck = Lock;
    }
}

/////////////////////////////////////////////////////////////////////////////

void BuzzerEvent()
{
    flagBuzzer = true;
    BuzzBuzzer();
    lastBuzzerActivity = millis();
}

/////////////////////////////////////////////////////////////////////////////

bool CheckIfA()
{
    if(keyInput == '#' || keyInput == 'A') return true;
    else return false;
}

/////////////////////////////////////////////////////////////////////////////

bool CheckIfAlphabet()
{
    switch(keyInput)
    {
        case 'A':
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

/////////////////////////////////////////////////////////////////////////////

void ResetPass()
{
    passKey1 = '2';
    passKey2 = '2';
    passKey3 = '3';
    Serial.println("!! Password reset to default !!");
}

/////////////////////////////////////////////////////////////////////////////