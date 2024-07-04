#include "eeprom_manager.h"

EEPROMManager::EEPROMManager(int size, int address) : eepromSize(size), uuidAddress(address)
{
    EEPROM.begin(eepromSize);
}

EEPROMManager::~EEPROMManager()
{
    EEPROM.end();
}

int EEPROMManager::readUUID()
{
    return EEPROM.read(uuidAddress);
}