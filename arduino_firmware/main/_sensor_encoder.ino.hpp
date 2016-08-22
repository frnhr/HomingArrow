#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef SENSOR_ENCODER_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define SENSOR_ENCODER_INO_HPP
#include "_sensor_encoder.hpp"


#ifndef ARROW_HPP
  #warning sensor_encoder module compiled without arrow module
#endif


void SensorEncoder::setup()
{}


void SensorEncoder::loop()
{
  // read raw gray code from encoder:
	gray_code = 0;
	for (int i=0; i<8; i++) {
		if (digitalRead(pins[i])) {
			gray_code += power(2, i);
		}
	}

  // get position from matrix:
  position = SENSOR_ENCODER_GRAY2BIN[gray_code];

  // some gray_code values are forbidden, and will map to 255:
  // (this should happen only if invalid wiring or something else very bad)
	if (position == 255) {
    // only report error if encoder has been initialized:
		if (inited) {
      // only report a value once:
    	if (last_error == gray_code) return;
    	last_error = gray_code;
    	Serial.print(F("WARNING: Invalid encoder value: "));
    	Serial.print(gray_code);
    	Serial.print(F("\n"));
		}
		return;
	}

	// encoder_value is valid.

	// set "inited" flag
	inited = true;
}
