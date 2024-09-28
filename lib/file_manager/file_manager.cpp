#include "file_manager.h"
#include "spiffs_manager.h"

FileManager::FileManager()
{
}

bool FileManager::saveWifiSSID(const String &ssid)
{
    Serial.println("Saving SSID: " + ssid);
    return saveToFile("/ssid.txt", ssid);
}

bool FileManager::saveWifiPassword(const String &password)
{
    Serial.println("Saving password: " + password);
    return saveToFile("/password.txt", password);
}

bool FileManager::saveApiKey(const String &apiKey)
{
    Serial.println("Saving API Key: " + apiKey);
    return saveToFile("/apikey.txt", apiKey);
}

bool FileManager::loadWifiSSID(String &ssid)
{
    return loadFromFile("/ssid.txt", ssid);
}

bool FileManager::loadWifiPassword(String &password)
{
    return loadFromFile("/password.txt", password);
}

bool FileManager::loadApiKey(String &apiKey)
{
    return loadFromFile("/apikey.txt", apiKey);
}

bool FileManager::saveToFile(const String &filename, const String &data)
{
    SPIFFSManager spiffsManager;
    return spiffsManager.saveFile(filename, data);
}

bool FileManager::loadFromFile(const String &filename, String &data)
{
    SPIFFSManager spiffsManager;
    return spiffsManager.loadFile(filename, data);
}

bool FileManager::saveBrightness(int brightness)
{
    SPIFFSManager spiffsManager;
    return saveToFile("/brightness.txt", String(brightness));
}

bool FileManager::loadBrightness(int &brightness)
{
    SPIFFSManager spiffsManager;
    String data;
    if (!loadFromFile("/brightness.txt", data))
    {
        return false;
    }
    brightness = data.toInt();
    return true;
}

bool FileManager::saveStationCode(const String &stationCode)
{
    SPIFFSManager spiffsManager;
    return saveToFile("/station_code.txt", stationCode);
}

bool FileManager::loadStationCode(String &stationCode)
{
    SPIFFSManager spiffsManager;
    return loadFromFile("/station_code.txt", stationCode);
}