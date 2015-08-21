#include "encoder.h"


void encoder_setup()
{
	for (int i=0; i<8; i++) {
		pinMode(encoder.pins[i], INPUT_PULLUP);
	    digitalWrite(encoder.pins[i], HIGH);
	}
}


void encoder_loop()
{
	/***** read raw data (Grauy code) from the encoder *****/
	_encoder.gray_code = 0;
	for (int i=0; i<8; i++) {
		if (digitalRead(encoder.pins[i])) {
			_encoder.gray_code += power(2, i);
		}
	}

	/***** invalid Gray code value *****/
	if (pgm_read_byte_near(ENCODER_GRAY2BIN + _encoder.gray_code) < 0) {
		if (encoder.inited) {
			// only report if encoder has been initialized
			encoder_error(_encoder.gray_code);
		}
		return;
	} 

	/***** normal operation *****/

	// set "inited" flag
	if (! encoder.inited) encoder.inited = true;
	
	// decode Gray code into binary position
	_encoder.last_value = pgm_read_byte_near(ENCODER_GRAY2BIN + _encoder.gray_code);

	// set offset if commanded
	if (encoder.set_north) {
		encoder.set_north = false;
		_encoder.offset = _encoder.last_value;
	}

	// calculate azimuth (in radians)
	encoder.azimuth = map_to_circle_rad((_encoder.last_value - _encoder.offset) / _encoder.resolution * 2 * M_PI);
}


void encoder_error(unsigned int value)
{
	if (_encoder.last_error == value) return;  // only report once
	_encoder.last_error = value;
	Serial.print(F("Invalid encoder value: "));
	Serial.print(value);
	Serial.print(F("\n"));
}
