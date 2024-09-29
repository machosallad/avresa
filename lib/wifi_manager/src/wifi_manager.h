#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <DNSServer.h>

class WiFiManager
{
public:
    WiFiManager(const String &ssid, const String &password);
    ~WiFiManager();

    bool connectToWifi(uint8_t timeoutInSeconds = 10);
    bool isConnected();
    String getIpAddress();
    void setSSID(const String &ssid);
    void setPassword(const String &password);
    void startCaptivePortal();
    void stopCaptivePortal();
    void processDNSRequests();
    String getAPName();

private:
    String m_ssid;
    String m_password;
    DNSServer dnsServer;
};
;

#endif // WIFI_MANAGER_H