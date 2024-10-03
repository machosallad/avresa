#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Update.h>
#include <FS.h>
#include <SPIFFS.h>
#include <esp_partition.h>
#include "ota_manager.h"
#include <ArduinoJson.h>
#include "ota_constants.h"
#include "spiffs_manager.h"

const String OtaManager::m_firmwareInfoUrl = OTA_FIRMWARE_INFO_URL;         // Firmware info file URL
const String OtaManager::m_firmwareUrl = OTA_FIRMWARE_URL;                  // Firmware file URL
const String OtaManager::m_firmwareChecksumUrl = OTA_FIRMWARE_CHECKSUM_URL; // Firmware checksum file URL

OtaManager::OtaManager(const String &currentVersion, Display &display) : m_currentVersion(currentVersion), m_display(display)
{
}

OtaManager::~OtaManager()
{
}

bool OtaManager::updateAvailable()
{
    // Download the JSON file containing firmware info
    const char *jsonPath = "/firmware.json";

    if (!downloadFile(m_firmwareInfoUrl, jsonPath))
    {
        Serial.println("Failed to download firmware info");
        return false;
    }

    // Parse the JSON file
    File jsonFile = SPIFFS.open(jsonPath);
    if (!jsonFile)
    {
        Serial.println("Failed to open firmware info file");
        return false;
    }

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonFile);
    jsonFile.close();

    if (error)
    {
        Serial.println("Failed to parse firmware info");
        return false;
    }

    String version = doc["version"];
    String buildDate = doc["build_date"];
    String firmwareUrl = doc["firmware_url"];
    String checksum = doc["checksum"];

    Serial.println("New firmware version: " + version);
    Serial.println("Build date: " + buildDate);

    // Compare versions
    if (version != m_currentVersion)
    {
        Serial.println("Update available");
        return true;
    }
    else
    {
        Serial.println("No update available");
        return false;
    }
}

bool OtaManager::downloadOta()
{
    const char *firmwarePath = "/firmware.bin";
    const char *checksumPath = "/firmware.bin.md5";
    bool result = false;
    SPIFFSManager spiffsManager;

    m_display.clearScreen();
    m_display.printText("Downloading update", Display::Line::Line1);
    m_display.printText("Installing update", Display::Line::Line3);

    if (downloadFile(m_firmwareUrl, firmwarePath) && downloadFile(m_firmwareChecksumUrl, checksumPath))
    {
        Serial.println("Downloaded firmware and checksum file");
        if (verifyChecksum(firmwarePath, checksumPath))
        {
            Serial.println("MD5 checksum matches, applying firmware...");
            if (applyFirmware(firmwarePath))
            {
                Serial.println("Firmware update successful");
                result = true;
            }
            else
            {
                Serial.println("Firmware update failed");
            }
        }
        else
        {
            Serial.println("MD5 checksum does not match, aborting update");
        }
    }
    else
    {
        Serial.println("Failed to download firmware or checksum file");
    }

    return result;
}

String OtaManager::getCurrentVersion()
{
    return m_currentVersion;
}

bool OtaManager::downloadFile(const String &url, const String &path)
{
    HTTPClient http;
    int httpCode = http.GET();
    String currentUrl = url;
    int maxRedirects = 5; // Maximum number of redirects to follow

    Serial.println("Discovering redirects...");
    for (int i = 0; i < maxRedirects; i++)
    {
        http.begin(currentUrl);
        httpCode = http.GET();

        // Handle HTTP redirection
        if (httpCode == HTTP_CODE_FOUND || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == HTTP_CODE_TEMPORARY_REDIRECT || httpCode == HTTP_CODE_PERMANENT_REDIRECT)
        {
            currentUrl = http.getLocation();
            Serial.println("Redirected to: " + currentUrl);
            http.end(); // End the current connection
        }
        else
        {
            break; // Exit the loop if not a redirection
        }
    }

    if (httpCode == HTTP_CODE_OK)
    {
        File file = SPIFFS.open(path, FILE_WRITE);
        if (!file)
        {
            Serial.println("Failed to open file for writing");
            return false;
        }

        WiFiClient *stream = http.getStreamPtr();
        uint8_t buffer[1024] = {0}; // Increased buffer size to 1024 bytes
        int totalLength = http.getSize();
        int len = totalLength;
        int totalRead = 0;

        Serial.println("Downloading file...");
        int downloadedLength = 0;
        while (http.connected() && (len > 0 || len == -1))
        {
            size_t size = stream->available();
            if (size)
            {
                int c = stream->readBytes(buffer, ((size > sizeof(buffer)) ? sizeof(buffer) : size));
                file.write(buffer, c);
                downloadedLength += c;
                if (totalLength > 0)
                {
                    Serial.printf("Downloaded %d of %d bytes (%.2f%%)\r", downloadedLength, totalLength, (downloadedLength * 100.0) / totalLength);
                    m_display.fillColorPercentage((downloadedLength * 100) / totalLength, Display::Color::Orange, Display::Line::Line2, 1);
                }
                else
                {
                    Serial.printf("Downloaded %d bytes\n", downloadedLength);
                }
                if (len > 0)
                {
                    len -= c;
                }
            }
            else
            {
                delay(10); // Slight delay to avoid busy-waiting
            }
        }

        file.close();
        return true;
    }
    else
    {
        Serial.printf("HTTP GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
        return false;
    }
}

bool OtaManager::applyFirmware(const String &path)
{
    Serial.println("Applying firmware from path: " + String(path));

    if (!SPIFFS.exists(path))
    {
        Serial.println("Firmware file does not exist");
        return false;
    }

    File file = SPIFFS.open(path);
    if (!file)
    {
        Serial.println("Failed to open firmware file");
        return false;
    }

    size_t fileSize = file.size();
    Serial.println("Firmware file size: " + String(fileSize) + " bytes");

    if (!Update.begin(fileSize))
    {
        Serial.println("Not enough space to begin OTA");
        file.close();
        return false;
    }

    // Set up progress callback
    Update.onProgress([this](size_t done, size_t total)
                      {
        Serial.printf("Progress: %u%%\r", (done * 100) / total);
                        m_display.fillColorPercentage((done * 100) / total, Display::Color::Orange, Display::Line::Line4, 1); });

    size_t written = Update.writeStream(file);
    if (written == fileSize)
    {
        Serial.println("Written : " + String(written) + " successfully");
    }
    else
    {
        Serial.println("Written only : " + String(written) + "/" + String(fileSize) + ". Retry?");
    }

    if (Update.end())
    {
        Serial.println("OTA done!");
        if (Update.isFinished())
        {
            Serial.println("Update successfully completed. Applied on next boot.");
            return true;
        }
        else
        {
            Serial.println("Update not finished? Something went wrong!");
            return false;
        }
    }
    else
    {
        Serial.println("Error Occurred. Error #: " + String(Update.getError()));
        return false;
    }

    file.close();
}

String OtaManager::calculateMD5(const String &path)
{
    File file = SPIFFS.open(path);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return String();
    }

    MD5Builder md5;
    md5.begin();
    while (file.available())
    {
        uint8_t buffer[512];
        size_t bytesRead = file.read(buffer, sizeof(buffer));
        md5.add(buffer, bytesRead);
    }
    file.close();
    md5.calculate();
    return md5.toString();
}

bool OtaManager::verifyChecksum(const String &file, const String &checksumPath)
{
    File checksumFile = SPIFFS.open(checksumPath);
    if (!checksumFile)
    {
        Serial.println("Failed to open checksum file");
        return false;
    }

    String checksumLine = checksumFile.readStringUntil('\n');
    checksumFile.close();

    // Extract the checksum part from the line
    int spaceIndex = checksumLine.indexOf(' ');
    String expectedMD5;
    if (spaceIndex != -1)
        expectedMD5 = checksumLine.substring(0, spaceIndex);
    else
        expectedMD5 = checksumLine;

    expectedMD5.trim(); // Remove any whitespace or newline characters
    String calculatedMD5 = calculateMD5(file);

    Serial.println("Calculated MD5: " + calculatedMD5);
    Serial.println("Expected MD5: " + expectedMD5);

    return calculatedMD5.equalsIgnoreCase(expectedMD5);
}
