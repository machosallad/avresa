#include "application.h"
#include "config.h"

unsigned long lastRequestTime = 0;           // When the last request was made
const unsigned long requestInterval = 10000; // Request interval (10 seconds)

Application::Application()
{
    // Constructor
}

Application::~Application()
{
    // Destructor
}

void Application::init()
{
    TrafikverketClient trafikverketClient(SERVER_KEY, SERVER_URL);
    ContentManager contentManager();
    WiFiManager wifiManager(WIFI_SSID, WIFI_PASSWORD);
    wifiManager.connectToWifi();

    // Make the HTTP post request
    if (wifiManager.isConnected())
    {
        String response = trafikverketClient.getTrainAnnouncements(STATION_CODE);
        Announcements announcements(response);
        announcements.printAll();
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}

void Application::run()
{
    unsigned long currentTime = millis();
    if (currentTime - lastRequestTime >= requestInterval)
    {
        lastRequestTime = currentTime;
        Serial.println("Requesting data... (not yet implemented)");
    }
}