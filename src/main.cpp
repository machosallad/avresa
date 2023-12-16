#include <Arduino.h>
#include "announcements.h"
#include "wifi_manager.h"
#include "trafikverket_client.h"
#include "content_manager.h"
#include "web_server.h"
#include "config.h"

unsigned long lastRequestTime = 0;          // When the last request was made
const unsigned long requestInterval = 6000; // Request interval (6 seconds)

void setup()
{
  Serial.begin(9600);
  delay(1000);

  TrafikverketClient TrafikverketClient(SERVER_KEY, SERVER_URL);
  ContentManager contentManager();
  WiFiManager wifiManager(WIFI_SSID, WIFI_PASSWORD);
  wifiManager.connectToWifi();

  // Make the HTTP post request
  if (wifiManager.isConnected())
  {
    String response = TrafikverketClient.getTrainAnnouncements(STATION_CODE);
    Announcements announcements(response);
    announcements.printAll();
  }
  else
  {
    Serial.println("WiFi Disconnected");
  }
}

void loop()
{
  unsigned long currentTime = millis();
  if (currentTime - lastRequestTime >= requestInterval)
  {
    lastRequestTime = currentTime;
    Serial.println("Requesting data...");
  }
}