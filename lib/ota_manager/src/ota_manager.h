#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include <Arduino.h>

class OtaManager
{
public:
    OtaManager(const String &currentVersion);
    ~OtaManager();

    bool updateAvailable();
    void downloadOta();

private:
    bool downloadFile(const String &url, const String &path);
    bool applyFirmware(const String &path);
    String calculateMD5(const String &path);
    String m_currentVersion;

    static const String m_firmwareInfoUrl;
    static const String m_firmwareUrl;
    static const String m_firmwareChecksumUrl;
};

#endif // OTA_MANAGER_H