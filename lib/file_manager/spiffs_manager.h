#ifndef SPIFFS_MANAGER_H
#define SPIFFS_MANAGER_H

#include <SPIFFS.h>

/**
 * @class SPIFFSManager
 * @brief A class to manage the SPIFFS file system.
 *
 * The SPIFFSManager class provides methods to initialize and terminate the SPIFFS
 * file system. It ensures that the file system is properly mounted at the beginning
 * and unmounted at the end.
 */
class SPIFFSManager
{
public:
    SPIFFSManager()
    {
        if (!SPIFFS.begin())
        {
            Serial.println("Failed to mount file system");
        }
    }

    ~SPIFFSManager()
    {
        SPIFFS.end();
    }
};

#endif // SPIFFS_MANAGER_H