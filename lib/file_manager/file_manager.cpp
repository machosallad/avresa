#include "file_manager.h"

FileManager::FileManager()
{
}

void FileManager::init()
{
    // Initialize SPIFFS
    if (!SPIFFS.begin(true))
    {
        Serial.println("An error has occurred while mounting SPIFFS");
    }
    else
    {
        Serial.println("SPIFFS mounted successfully");
    }
}

void FileManager::end()
{
    SPIFFS.end();
}

bool FileManager::saveWifiSSID(const String &ssid)
{
    return saveSecret(ssid, "", "");
}

bool FileManager::saveWifiPassword(const String &password)
{
    return saveSecret("", password, "");
}

bool FileManager::saveApiKey(const String &apiKey)
{
    return saveSecret("", "", apiKey);
}

bool FileManager::saveSecret(const String &ssid, const String &password, const String &apiKey)
{
    // Load existing secrets
    Secrets secrets;
    loadSecret(secrets);

    // Update only the provided fields
    if (!ssid.isEmpty())
    {
        secrets.ssid = ssid;
    }
    if (!password.isEmpty())
    {
        secrets.password = password;
    }
    if (!apiKey.isEmpty())
    {
        secrets.apiKey = apiKey;
    }

    // Save the updated secrets
    File file = SPIFFS.open(secretFilePath, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return false;
    }
    file.println(secrets.ssid);
    file.println(secrets.password);
    file.println(secrets.apiKey);
    file.close();
    return true;
}

bool FileManager::saveSecret(const Secrets &secrets)
{
    return saveSecret(secrets.ssid, secrets.password, secrets.apiKey);
}

bool FileManager::loadSecret(Secrets &secrets)
{
    String ssid, password, apiKey;
    if (!loadSecret(ssid, password, apiKey))
    {
        return false;
    }
    secrets.ssid = ssid;
    secrets.password = password;
    secrets.apiKey = apiKey;
    return true;
}

bool FileManager::loadSecret(String &ssid, String &password, String &apiKey)
{
    File file = SPIFFS.open(secretFilePath, FILE_READ);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return false;
    }
    ssid = file.readStringUntil('\n');
    password = file.readStringUntil('\n');
    apiKey = file.readStringUntil('\n');
    ssid.trim();
    password.trim();
    apiKey.trim();
    file.close();
    return true;
}

bool FileManager::saveParameter(const Parameter &parameter)
{
    File file = SPIFFS.open(parameterFilePath, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return false;
    }
    file.println(parameter.brightness);
    file.println(parameter.stationCode);
    file.close();
    return true;
}

bool FileManager::loadParameter(Parameter &parameter)
{
    File file = SPIFFS.open(parameterFilePath, FILE_READ);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return false;
    }
    parameter.brightness = file.readStringUntil('\n').toInt();
    parameter.stationCode = file.readStringUntil('\n');
    parameter.stationCode.trim();
    file.close();
    return true;
}