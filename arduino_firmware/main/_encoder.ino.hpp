#include <Arduino.h>
#include "modules.hpp"

#include "_encoder.hpp"
#include "hardware_config.h"

// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef ENCODER_INO_H
#error The .ino.h file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define ENCODER_INO_H


void Encoder::setup()
{
	for (int i=0; i<8; i++) {
		pinMode(pins[i], INPUT_PULLUP);
	}

  // read stuff from EEPROM:

  // ... if EEPROM was ever configured:
  uint8_t eeprom_signature;
  EEPROM.get(ENCODER_EEPROM_ADDR_SIGN, eeprom_signature);
  configured = (eeprom_signature == ENCODER_EEPROM_SIGNATURE);

  // ... azimuth offset:
  if (! configured) {
    offset = 0.0;
  } else {
  	EEPROM.get(ENCODER_EEPROM_ADDR_OFFSET, offset);
    set_offset = offset;
  }

  // reset setters:
  set_offset = ENCODER_NULL_AZIMUTH;
}


void Encoder::loop()
{
  // handle setters:

  // ... azimuth
  if (set_azimuth != ENCODER_NULL_AZIMUTH) {
    // make use of offset setter:
    set_offset = offset - map_to_half_circle_rad(set_azimuth - azimuth);
    // reset the setter:
    set_azimuth = ENCODER_NULL_AZIMUTH;
  }

  // ... offset:
	if (set_offset != ENCODER_NULL_AZIMUTH) {
    // make sure value is between 0 and 2*Pi
		offset = map_to_circle_rad(set_offset);
    // save it to EEPROM:
		EEPROM.put(ENCODER_EEPROM_ADDR_OFFSET, offset);
    // mark EEPROM as "configured":
    if (!configured) {
      configured = true;
      EEPROM.put(ENCODER_EEPROM_ADDR_SIGN, ENCODER_EEPROM_SIGNATURE);
    }
    // reset setter:
    set_offset = ENCODER_NULL_AZIMUTH;
	}

  // read raw gray code from encoder:
	gray_code = 0;
	for (int i=0; i<8; i++) {
		if (digitalRead(pins[i])) {
			gray_code += power(2, i);
		}
	}

  // get position from matrix:
  position = ENCODER_GRAY2BIN[gray_code];

  // some gray_code values are forbidden, and will map to 255:
  // (this should happen only if invalid wiring or something else very bad)
	if (position == 255) {
    // only report error if encoder has been initializeD:
		if (inited) {
      // only report a value once:
    	if (last_error == gray_code) return;
    	last_error = gray_code;
    	Serial.print(F("Invalid encoder value: "));
    	Serial.print(gray_code);
    	Serial.print(F("\n"));
		}
		return;
	}

	// encoder_value is valid.

	// set "inited" flag
	inited = true;

	// calculate azimuth (in radians) and apply offset:
	azimuth = map_to_circle_rad(((float) position) / resolution * 2 * M_PI - offset);
}
