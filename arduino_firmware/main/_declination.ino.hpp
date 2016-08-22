#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef DECLINATION_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define DECLINATION_INO_HPP
#include "_declination.hpp"


void Declination::setup()
{
  Serial.print(F("[declination     ]\t"));
  uint8_t hasEepromData;
  EEPROM.get(DECLINATION_EEPROM_ADDR, hasEepromData);
  if (isCloseTo(hasEepromData, DECLINATION_SIGN, DECLINATION_NULL_EPSILON)) {
    EEPROM.get(DECLINATION_EEPROM_VALUE, _declination);
    declination = _declination;
  }
  if (isCloseTo(declination, DECLINATION_NULL_VALUE, DECLINATION_NULL_EPSILON)) {
    Serial.print(F("WARNING: not set!"));
    inited = false;
  } else {
    Serial.print(F("INFO: set to: "));
    Serial.print(declination);
    inited = true;
  }
  Serial.print(F("\n"));
}


void Declination::loop()
{
  // handle declination setter:
  if (isSett(setDeclination, DECLINATION_NULL_VALUE, DECLINATION_NULL_EPSILON)) {
    // save to private var:
    _declination = deg2rad(setDeclination);
    // save to EEPROM:
    EEPROM.put(DECLINATION_EEPROM_VALUE, (float) _declination);
    EEPROM.put(DECLINATION_EEPROM_ADDR, (uint8_t) DECLINATION_SIGN);  // signals that value is present (because 0 is also a valid value)
    // clear the setter:
    setDeclination = DECLINATION_NULL_VALUE;
    // set the inited flag if needed:
    inited = true;
  }

  // update public getter:
  declination = _declination;
}
