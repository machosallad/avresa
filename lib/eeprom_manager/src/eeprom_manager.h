#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <EEPROM.h>

/**
 * @class EEPROMManager
 * @brief A class for managing EEPROM operations.
 *
 * This class provides functionality to read and write data to EEPROM memory.
 */
class EEPROMManager
{
public:
    /**
     * @brief Constructs an EEPROMManager object.
     * @param size The size of the EEPROM memory in bytes.
     * @param address The starting address of the EEPROM memory.
     */
    EEPROMManager(int size, int address);

    /**
     * @brief Destroys the EEPROMManager object.
     */
    ~EEPROMManager();

    /**
     * @brief Reads the UUID from the EEPROM memory.
     * @return The UUID read from the EEPROM memory.
     */
    uint8_t readUUID();

    /**
     * @brief Writes the given UUID to the EEPROM.
     *
     * This function is responsible for writing the provided UUID to the EEPROM.
     *
     * @param uuid The UUID to be written to the EEPROM.
     */
    bool writeUUID(uint8_t uuid);

private:
    int eepromSize;  ///< The size of the EEPROM memory in bytes.
    int uuidAddress; ///< The address of the UUID in the EEPROM memory.
};

#endif // EEPROM_MANAGER_H