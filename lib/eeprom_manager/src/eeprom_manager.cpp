#include "eeprom_manager.h"

EEPROMManager::EEPROMManager(int size, int address) : eepromSize(size), uuidAddress(address)
{
    EEPROM.begin(eepromSize);
}

EEPROMManager::~EEPROMManager()
{
    EEPROM.end();
}

uint8_t EEPROMManager::readUUID()
{
    return EEPROM.read(uuidAddress);
}

bool EEPROMManager::writeUUID(uint8_t uuid)
{
    EEPROM.write(uuidAddress, uuid);
    if (!EEPROM.commit())
    {
        return false; // EEPROM.commit() failed
    }

    // Read back the value to verify the write operation
    uint8_t writtenValue = EEPROM.read(uuidAddress);
    return writtenValue == uuid;
}