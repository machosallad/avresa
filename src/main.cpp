#include <Arduino.h>
#include "application.h"

Application app;
void setup()
{
  Serial.begin(9600);
  delay(1000);
  app.init();
}

void loop()
{
  app.run();
}