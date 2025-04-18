#include "BuzzerHandler.h"

#define BuzzerPin A0

void SetupBuzzer()
{
    pinMode(BuzzerPin, HIGH);
}

void BuzzBuzzer()
{
    tone(BuzzerPin, 3000);
}

void StopBuzzer()
{
    noTone(BuzzerPin);
}