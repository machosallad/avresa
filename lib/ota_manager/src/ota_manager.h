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
    bool verifyChecksum(const String &path, const String &checksumPath);
    String calculateMD5(const String &path);
    String m_currentVersion;

    static const String m_firmwareInfoUrl;
    static const String m_firmwareUrl;
    static const String m_firmwareChecksumUrl;
    Display &m_display;
};

#endif // OTA_MANAGER_H