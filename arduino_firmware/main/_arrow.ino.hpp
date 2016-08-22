#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef ARROW_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define ARROW_INO_HPP
#include "_arrow.hpp"


void Arrow::setup()
{
  Serial.print(F("[arrow          ]\t"));
  uint8_t signature;
  EEPROM.get(ARROW_EEPROM_ADDR_SIGNATURE, signature);
  if (signature == ARROW_EEPROM_SIGNATURE) {
    configured = true;
    EEPROM.get(ARROW_EEPROM_ADDR_SIGNATURE, _offset);
    Serial.print(F("INFO: offset:"));
    Serial.print(rad2deg(_offset));
    Serial.print(F("\n"));
  } else {
    Serial.print(F("WARNING:  offset not set, assuming \"0.00\"!\n"));
  }
}


void Arrow::loop()
{
  // handle setters:

  // ... azimuth
  if (isSett(setCurrentAzimuth, ARROW_NULL_VALUE, ARROW_NULL_EPSOLIN)) {
    // make use of offset setter:
    setOffset = _offset - map_to_half_circle_rad(setCurrentAzimuth - azimuth);
    // reset the setter:
    setCurrentAzimuth = ARROW_NULL_VALUE;
  }

  // ... offset:
	if (isSett(setOffset, ARROW_NULL_VALUE, ARROW_NULL_EPSOLIN)) {
    // make sure value is between 0 and 2*Pi
		_offset = map_to_circle_rad(setOffset);
    // save it to EEPROM:
		EEPROM.put(ARROW_EEPROM_ADDR_OFFSET, _offset);
    // mark EEPROM as "configured":
    if (!configured) {
      configured = true;
      EEPROM.put(ARROW_EEPROM_ADDR_SIGNATURE, ARROW_EEPROM_SIGNATURE);
    }
    // reset setter:
    setOffset = ARROW_NULL_VALUE;
	}

  // if nothing is set from encoder, nothing to do:
  if (!isSett(setAzimuth, ARROW_NULL_VALUE, ARROW_NULL_EPSOLIN)) {
    return;
  }

	// calculate azimuth (in radians) and apply offset:
	azimuth = map_to_circle_rad(setAzimuth + _offset);

  // reset the setter:
  setAzimuth = ARROW_NULL_VALUE;

  // declate inited:
  inited = true;
}
