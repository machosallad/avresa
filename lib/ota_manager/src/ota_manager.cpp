#include <WiFiClientSecure.h>
#include <Update.h>
#include <FS.h>
#include <SPIFFS.h>
#include <esp_partition.h>
#include "ota_manager.h"
#include <ArduinoJson.h>
#include "ota_constants.h"
#include "spiffs_manager.h"

const String OtaManager::m_firmwareInfoUrl = OTA_FIRMWARE_INFO_URL; // Firmware info file URL
const String OtaManager::m_firmwareUrl = OTA_FIRMWARE_URL;          // Firmware file URL

OtaManager::OtaManager(const String &currentVersion, Display &display) : m_currentVersion(currentVersion), m_display(display), m_expectedMD5("")
{
}

OtaManager::~OtaManager()
{
}

bool OtaManager::updateAvailable()
{
    // Download the JSON file containing firmware info
    SPIFFSManager spiffsManager;
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

    String version = doc["version"].as<String>();
    String buildDate = doc["date"].as<String>();
    String checksumLine = doc["md5"].as<String>();

    // Extract checksum from the line
    if (!extractChecksum(checksumLine, m_expectedMD5))
    {
        Serial.println("Failed to extract checksum from firmware info");
        return false;
    }

    Serial.println("Current firmware version: " + m_currentVersion);
    Serial.println("New firmware version: " + version);
    Serial.println("Build date: " + buildDate);
    Serial.println("Checksum: " + m_expectedMD5);

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

String OtaManager::getCurrentVersion()
{
    return m_currentVersion;
}

bool OtaManager::downloadFile(const String &url, const String &path)
{
    HTTPClient http;
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.begin(url);
    int httpCode = http.GET();

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

bool OtaManager::extractChecksum(const String &line, String &checksum)
{
    // Extract only checksum from the line if it contains more than just the checksum
    int spaceIndex = line.indexOf(' ');
    String expectedMD5;
    if (spaceIndex != -1)
        expectedMD5 = line.substring(0, spaceIndex);
    else
        expectedMD5 = line;

    expectedMD5.trim(); // Remove any whitespace or newline characters

    if (expectedMD5.length() == 32)
    {
        checksum = expectedMD5;
        return true;
    }

    return false;
}

bool OtaManager::updateFirmware()
{
    HTTPClient http;
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    if (!http.begin(m_firmwareUrl))
    {
        return false; // httpclient setup error
    }
    Serial.printf("Sending HTTP request '%s'\n", m_firmwareUrl.c_str());

    // Connect and send HTTP request to server
    int size = sendHttpRequest(http);

    // Is there an image to download
    if (size > 0)
    {
        m_display.clearScreen();
        m_display.printTextCenteredHorizontal("Downloading update", Display::Line::Line2);

        if (flashFromHttpStream(http))
        {
            http.end();
            return true; // End connection
        }
    }
    else
    {
        Serial.println("Image file not found");
    }
    http.end(); // End connection

    return false;
}

int OtaManager::sendHttpRequest(HTTPClient &http)
{
    // Set request headers to be sent to server
    http.useHTTP10(true); // Use HTTP/1.0 for update since the update handler does not support any transfer encoding
    http.setTimeout(8000);
    http.addHeader("Cache-Control", "no-cache");
    http.setUserAgent("ESP32");

    int code = http.GET();
    int len = http.getSize();

    if (code == HTTP_CODE_OK)
    {
        return (len > 0 ? len : 0); // Return 0 or length of image to download
    }
    else if (code < 0)
    {
        Serial.printf("HTTP GET request failed, error: %s\n", http.errorToString(code).c_str());
        return code;
    }
    else
    {
        Serial.printf("HTTP GET request failed, error code: %d\n", code);
        return -code;
    }
}

bool OtaManager::flashFromHttpStream(HTTPClient &http, uint32_t size)
{
    size = (size == 0 ? http.getSize() : size);
    if (size == 0)
    {
        return false;
    }

    WiFiClient *client = http.getStreamPtr();
    Update.onProgress([this](size_t done, size_t total)
                      {
        Serial.printf("Progress: %u%%\r", (done * 100) / total);
                        m_display.fillColorPercentage((done * 100) / total, Display::Color::Orange, Display::Line::Line3, 1); });

    if (!Update.begin(size, U_FLASH))
    {
        Serial.printf("Update.begin failed! (%s)\n", Update.errorString());
        return false;
    }

    if (!Update.setMD5(m_expectedMD5.c_str()))
    {
        Serial.println("Failed to set MD5 checksum");
    }

    if (Update.writeStream(*client) != size)
    {
        Serial.printf("Update.writeStream failed! (%s)\n", Update.errorString());
        return false;
    }

    if (!Update.end())
    {
        Serial.printf("Update.end failed! (%s)\n", Update.errorString());
        return false;
    }

    return true;
}
