#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

class WiFiManager
{
public:
    WiFiManager(const char *ssid, const char *password);
    ~WiFiManager();

    void connectToWifi();
    bool isConnected();
    String getIpAddress();

private:
    const char *m_ssid;
    const char *m_password;
};

#endif // WIFI_MANAGER_H