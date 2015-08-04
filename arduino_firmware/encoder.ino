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
	_encoder.gray_code = 0;
	for (int i=0; i<8; i++) {
		if (! digitalRead(encoder.pins[i])) {
			_encoder.gray_code += power(2, i);
		}
	}
	if (_encoder.GRAY2BIN[_encoder.gray_code] < 0) {
		if (encoder.inited) {
			encoder_error(_encoder.gray_code);
		}
	} else {
		if (! encoder.inited) {
			encoder.inited = true;
		}
		_encoder.last_value = _encoder.GRAY2BIN[_encoder.gray_code];
		encoder.azimuth = map_to_circle(encoder.offset + _encoder.last_value / 360.0);
	}
}


void encoder_error(unsigned int value)
{
	// TODO can we safely ignore invalid values?
	Serial.print(F("Invalid encoder value: "));
	Serial.print(value);
	Serial.print(F("\n"));
}
