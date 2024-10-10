#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include <Arduino.h>
#include "display.h"
#include <HTTPClient.h>

class OtaManager
{
public:
    OtaManager(const String &currentVersion, Display &display);
    ~OtaManager();

    bool updateAvailable();
    bool updateFirmware();
    String getCurrentVersion();

private:
    bool downloadFile(const String &url, const String &path);
    bool extractChecksum(const String &line, String &checksum);
    bool flashFromHttpStream(HTTPClient &http, uint32_t size = 0);
    int sendHttpRequest(HTTPClient &http);

    static const String m_firmwareInfoUrl;
    static const String m_firmwareUrl;
    String m_currentVersion;
    String m_expectedMD5;
    Display &m_display;
};

#endif // OTA_MANAGER_H