#include "eeprom_manager.h"

EEPROMManager::EEPROMManager(int size, int address) : eepromSize(size), displayTypeAddress(address)
{
    EEPROM.begin(eepromSize);
}

EEPROMManager::~EEPROMManager()
{
    EEPROM.end();
}

uint8_t EEPROMManager::readDisplayType()
{
    return EEPROM.read(displayTypeAddress);
}

bool EEPROMManager::writeDisplayType(uint8_t displayType)
{
    EEPROM.write(displayTypeAddress, displayType);
    if (!EEPROM.commit())
    {
        return false; // EEPROM.commit() failed
    }

    // Read back the value to verify the write operation
    uint8_t writtenValue = EEPROM.read(displayTypeAddress);
    return writtenValue == displayType;
}