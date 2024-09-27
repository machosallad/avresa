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

  // Initialize SPIFFS
  fileManager.init();

  // Write Secrets to filesystem
  // TODO: Remove this and move to a configuration page instead
  String wifiSSID(WIFI_SSID);
  String wifiPassword(WIFI_PASSWORD);
  String serverKey(SERVER_KEY);
  fileManager.saveSecret(wifiSSID, wifiPassword, serverKey);
  fileManager.saveParameter(Parameter{128, String(STATION_CODE)});

  // Load Secrets
  Secrets secrets;
  if (!fileManager.loadSecret(secrets))
  {
    Serial.println("Failed to load secrets");
    return;
  }

  Serial.println("Secrets loaded");
  Serial.println("SSID: " + secrets.ssid);
  Serial.println("Password: " + secrets.password);
  Serial.println("API Key: " + secrets.apiKey);

  // Load Config
  Parameter parameters;
  if (!fileManager.loadParameter(parameters))
  {
    Serial.println("Failed to load parameters");
    return;
  }

  Serial.println("Parameters loaded");
  Serial.println("Brightness: " + String(parameters.brightness));
  Serial.println("Station Code: " + parameters.stationCode);

  // Close SPIFFS
  fileManager.end();

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