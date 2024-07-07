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
     * @brief Reads the display type from the EEPROM memory.
     * @return The display type read from the EEPROM memory.
     */
    uint8_t readDisplayType();

    /**
     * @brief Writes the given display type to the EEPROM.
     *
     * This function is responsible for writing the provided display type to the EEPROM.
     *
     * @param displayType The display type to be written to the EEPROM.
     */
    bool writeDisplayType(uint8_t displayType);

private:
    int eepromSize;         ///< The size of the EEPROM memory in bytes.
    int displayTypeAddress; ///< The address of the display type in the EEPROM memory.
};

#endif // EEPROM_MANAGER_H