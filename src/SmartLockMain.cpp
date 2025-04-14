#include <Arduino.h>
#include "EventHandler.h"

void setup()
{
  Serial.begin(115200);
  SetupLED();
  SetupBuzzer();
  SetupKeypad();
  Serial.println("!!  All Setup Success. Press any key  !!");
}

void loop()
{
  StateMachine();
}