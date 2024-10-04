#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include <Arduino.h>
#include "display.h"

class OtaManager
{
public:
    OtaManager(const String &currentVersion, Display &display);
    ~OtaManager();

    bool updateAvailable();
    bool downloadOta();
    String getCurrentVersion();

private:
    bool downloadFile(const String &url, const String &path);
    bool applyFirmware(const String &path);
    bool verifyChecksum(const String &path, const String &md5);
    String calculateMD5(const String &path);
    String m_currentVersion;
    String m_expectedMD5;
    bool extractChecksum(const String &line, String &checksum);

    static const String m_firmwareInfoUrl;
    static const String m_firmwareUrl;
    Display &m_display;
};

#endif // OTA_MANAGER_H