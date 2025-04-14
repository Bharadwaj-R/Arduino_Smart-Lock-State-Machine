#include "BuzzerHandler.h"

#define BuzzerPin 10

void SetupBuzzer()
{
    pinMode(BuzzerPin, HIGH);
}

void BuzzBuzzer()
{
    digitalWrite(BuzzerPin, HIGH);
}

void StopBuzzer()
{
    digitalWrite(BuzzerPin, LOW);
}