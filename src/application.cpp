#include "application.h"
#include "config.h"

Application::Application() : m_trafikverketClient(SERVER_KEY, SERVER_URL), m_wifiManager(WIFI_SSID, WIFI_PASSWORD)
{
    // Constructor
}

Application::~Application()
{
    // Destructor
}

void Application::init()
{
    m_wifiManager.connectToWifi();

    // Make the HTTP post request
    if (m_wifiManager.isConnected())
    {
        String response = m_trafikverketClient.getTrainAnnouncements(STATION_CODE);
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