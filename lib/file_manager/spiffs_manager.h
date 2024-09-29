#ifndef SPIFFS_MANAGER_H
#define SPIFFS_MANAGER_H

#include <SPIFFS.h>
#include "FS.h"

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

    bool saveFile(const String &filename, const String &data)
    {
        File file = SPIFFS.open(filename, FILE_WRITE);
        if (!file)
        {
            Serial.println("Failed to open file for writing: " + filename);
            return false;
        }
        if (file.print(data))
        {
            Serial.println("File written: " + filename);
            file.close();
            return true;
        }
        else
        {
            Serial.println("Write failed: " + filename);
            file.close();
            return false;
        }
    }

    bool loadFile(const String &filename, String &data)
    {
        File file = SPIFFS.open(filename, FILE_READ);
        if (!file)
        {
            Serial.println("Failed to open file for reading: " + filename);
            return false;
        }
        data = file.readString();
        Serial.println("File read: " + filename);
        file.close();
        return true;
    }
};

#endif // SPIFFS_MANAGER_H