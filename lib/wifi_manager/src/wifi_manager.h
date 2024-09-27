#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

class WiFiManager
{
public:
    WiFiManager(const String &ssid, const String &password);
    ~WiFiManager();

    void connectToWifi();
    bool isConnected();
    String getIpAddress();
    void setSSID(const String &ssid);
    void setPassword(const String &password);

private:
    String m_ssid;
    String m_password;
};
;

#endif // WIFI_MANAGER_H