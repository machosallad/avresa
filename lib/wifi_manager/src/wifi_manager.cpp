#include "wifi_manager.h"
WiFiManager::WiFiManager(const String &ssid, const String &password) : m_ssid(ssid), m_password(password)
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

String WiFiManager::getIpAddress()
{
    return WiFi.localIP().toString();
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

    WiFi.setAutoReconnect(true);

    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(getIpAddress());
}

// Implement your methods here