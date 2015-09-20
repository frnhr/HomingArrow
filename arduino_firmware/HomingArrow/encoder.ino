#include "encoder.h"


void encoder_setup()
{
	for (int i=0; i<8; i++) {
		pinMode(encoder.pins[i], INPUT_PULLUP);
	    digitalWrite(encoder.pins[i], HIGH);
	}

	EEPROM.get(ENCODER_EEPROM_ADDR, encoder.offset);
	_encoder.offset = encoder.offset;
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
	if (pgm_read_byte_near(ENCODER_GRAY2BIN + _encoder.gray_code) == (byte) -1) {
		if (encoder.inited) {
			// only report if encoder has been initialized
			encoder_error(_encoder.gray_code);
		}
		return;
	} 

	/***** normal operation *****/

	// set "inited" flag
	encoder.inited = true;
	
	// decode Gray code into binary position
	_encoder.position = pgm_read_byte_near(ENCODER_GRAY2BIN + _encoder.gray_code);

	// handle set_offset command
	if (encoder.offset != _encoder.offset) {
		encoder.offset = map_to_circle_rad(encoder.offset);
		_encoder.offset = encoder.offset;
		EEPROM.put(ENCODER_EEPROM_ADDR, encoder.offset);
	}

	// calculate azimuth (in radians)
	encoder.azimuth = map_to_circle_rad(((float) _encoder.position) / _encoder.resolution * 2 * M_PI - _encoder.offset);
}


void encoder_error(unsigned int value)
{
	if (_encoder.last_error == value) return;  // only a value report once
	_encoder.last_error = value;
	Serial.print(F("Invalid encoder value: "));
	Serial.print(value);
	Serial.print(F("\n"));
}
