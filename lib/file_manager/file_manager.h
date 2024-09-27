#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <map>

struct Secrets
{
    String ssid;
    String password;
    String apiKey;
};

struct Parameter
{
    int brightness;
    String stationCode;
};

class FileManager
{
public:
    FileManager();
    void init();
    void end();
    bool saveSecret(const String &ssid, const String &password, const String &apiKey);
    bool saveSecret(const Secrets &secrets);
    bool saveWifiSSID(const String &ssid);
    bool saveWifiPassword(const String &apiKey);
    bool saveApiKey(const String &apiKey);
    bool loadSecret(String &ssid, String &password, String &apiKey);
    bool loadSecret(Secrets &secrets);
    bool saveParameter(const Parameter &parameters);
    bool loadParameter(Parameter &parameters);

private:
    const char *secretFilePath = "/secrets.txt";
    const char *parameterFilePath = "/parameters.txt";
};

#endif // FILE_MANAGER_H