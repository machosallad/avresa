#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <Arduino.h>
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

/**
 * @class FileManager
 * @brief Manages the saving and loading of secrets and parameters to and from files.
 *
 * The FileManager class provides methods to save and load WiFi credentials, API keys,
 * and other parameters to specific file paths. It supports operations using both
 * individual string values and structured data types.
 *
 * @note The file paths for secrets and parameters are defined as private member variables.
 */
class FileManager
{
public:
    FileManager();
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