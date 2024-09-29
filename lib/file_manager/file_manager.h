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
    bool saveWifiSSID(const String &ssid);
    bool saveWifiPassword(const String &apiKey);
    bool saveApiKey(const String &apiKey);
    bool loadWifiSSID(String &ssid);
    bool loadWifiPassword(String &password);
    bool loadApiKey(String &apiKey);
    bool saveBrightness(int brightness);
    bool loadBrightness(int &brightness);
    bool saveStationCode(const String &stationCode);
    bool loadStationCode(String &stationCode);

private:
    bool saveToFile(const String &filename, const String &data);
    bool loadFromFile(const String &filename, String &data);
};

#endif // FILE_MANAGER_H