#include <Arduino.h>
#include "application.h"
#include "config.h"

/**
 * @brief Represents the main application.
 */
Application *app;
FileManager fileManager;

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
  EEPROMManager eeprom(64, 0);

  // Load Secrets
  Secrets secrets;
  fileManager.loadWifiSSID(secrets.ssid);
  fileManager.loadWifiPassword(secrets.password);
  fileManager.loadApiKey(secrets.apiKey);

  Serial.println("Secrets loaded");
  Serial.println("SSID: " + secrets.ssid);
  Serial.println("Password: " + secrets.password);
  Serial.println("API Key: " + secrets.apiKey);

  // Load Config
  Parameter parameters;
  fileManager.loadBrightness(parameters.brightness);
  fileManager.loadStationCode(parameters.stationCode);

  Serial.println("Parameters loaded");
  Serial.println("Brightness: " + String(parameters.brightness));
  Serial.println("Station Code: " + parameters.stationCode);

  // Initialize Application with loaded secrets and configuration
  app = new Application(secrets, parameters, fileManager);
  if (app == nullptr)
  {
    Serial.println("Failed to allocate memory for Application");
    return;
  }
  uint8_t displayID = eeprom.readDisplayType();
  app->init(displayID);
}

/**
 * @brief The main loop of the program.
 *
 * This function continuously runs the application's logic.
 * It is called repeatedly after the setup() function.
 */
void loop()
{
  app->run();
}