#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Define your sensitive settings here
const char *WIFI_SSID = "your_wifi_ssid";
const char *WIFI_PASSWORD = "your_wifi_password";
const char *SERVER_KEY = "your_server_key";
const char *SERVER_URL = "your_server_url";

struct Config
{
    String ssid;
    String password;
    String serverKey;
    String serverUrl;
    String stationCode;
    int brightness;
};

#endif // CONFIG_H