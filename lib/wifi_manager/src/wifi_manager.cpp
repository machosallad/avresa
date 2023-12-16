#include "wifi_manager.h"
WiFiManager::WiFiManager(const char *ssid, const char *password) : ssid(ssid), password(password)
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
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to WiFi");
}

// Implement your methods here