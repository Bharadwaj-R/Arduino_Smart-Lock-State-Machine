#include "LEDHandler.h"

#define LEDPin LED_BUILTIN

void SetupLED()
{
    pinMode(LEDPin, OUTPUT);
    pinMode(LEDPin, LOW);
}

void TurnOnLED()
{
    digitalWrite(LEDPin, HIGH);
}

void TurnOffLED()
{
    digitalWrite(LEDPin, HIGH);
}