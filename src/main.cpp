#include <Arduino.h>
#include <Wire.h>
int oscR1, oscR2, oscR3, oscR4, oscR5, oscR6, oscR7, oscR8;
#include "network.h"
#include "relay.h"

void setup()
{
  Serial.begin(115200);
  // set_wifi();
  // delay(100);
  setup_relay();
  Serial.println("LiquidComputing OSC");
}


void loop()
{
  read_Digitals();
  // touch_ON(random(123));
  // osc_receiver();
  // relaysOSC();
  // all_relay();
  delay(100);
}
