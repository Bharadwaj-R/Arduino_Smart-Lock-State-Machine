#include <Arduino.h>
#include "EventHandler.h"

void setup()
{
  Serial.begin(115200);
  SetupLED();
  SetupBuzzer();
  SetupKeypad();
  Serial.println("!!  All Setup Success. System locked. Input password to unlock  !!");
}

void loop()
{
  StateMachine();
}