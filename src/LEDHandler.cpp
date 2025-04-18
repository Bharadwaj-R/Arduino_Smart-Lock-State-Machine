#include "LEDHandler.h"

#define LEDPin A5

void SetupLED()
{
    pinMode(LEDPin, OUTPUT);
    digitalWrite(LEDPin, LOW);
}

void TurnOnLED()
{
    digitalWrite(LEDPin, HIGH);
}

void TurnOffLED()
{
    digitalWrite(LEDPin, LOW);
}