#include "wifi_manager.h"
WiFiManager::WiFiManager(const char *ssid, const char *password) : m_ssid(ssid), m_password(password)
{
    // Constructor body (if needed)
}

WiFiManager::~WiFiManager()
{
    // Destructor implementation
}

bool WiFiManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::connectToWifi()
{
    Serial.println("Connecting to WiFi");
    WiFi.begin(m_ssid, m_password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to WiFi");
}

// Implement your methods here