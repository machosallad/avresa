#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "application.h"

/**
 * @brief Represents the main application.
 */
Application app;

/**
 * @brief The main entry point of the program.
 *
 * This function initializes the serial communication, waits for 1 second,
 * and then initializes the application. It is called once at the start of the program.
 */
void setup()
{
  Serial.begin(9600);
  delay(1000);
  app.init();
}

/**
 * @brief The main loop of the program.
 *
 * This function continuously runs the application's logic.
 * It is called repeatedly after the setup() function.
 */
void loop()
{
  app.run();
}