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

void WiFiManager::setSSID(const String &ssid)
{
    m_ssid = ssid;
}

void WiFiManager::setPassword(const String &password)
{
    m_password = password;
}

bool WiFiManager::connectToWifi(uint8_t timeoutInSeconds)
{
    Serial.println("Connecting to WiFi");
    // Set WiFi mode to Station (client)
    WiFi.mode(WIFI_STA);
    WiFi.begin(m_ssid, m_password);

    uint32_t start = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - start) < timeoutInSeconds * 1000)
    {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Failed to connect to WiFi");
        return false;
    }

    WiFi.setAutoReconnect(true);

    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(getIpAddress());

    return true;
}

void WiFiManager::startCaptivePortal()
{
    IPAddress apIP(172, 217, 28, 1);
    IPAddress netMask(255, 255, 255, 0);

    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, netMask);
    WiFi.softAP("AVRESA-AP", NULL);
    delay(100); // Wait for AP to start
    Serial.println("SoftAP started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(53, "*", apIP);
}

void WiFiManager::stopCaptivePortal()
{
    // Stop the captive portal. This will stop the softAP and DNS server.
    WiFi.softAPdisconnect(true);
    dnsServer.stop();
}

void WiFiManager::processDNSRequests()
{
    // Process DNS requests to redirect all requests to the captive portal
    dnsServer.processNextRequest();
}

String WiFiManager::getAPName()
{
    return "AVRESA-AP";
}

// Implement your methods here