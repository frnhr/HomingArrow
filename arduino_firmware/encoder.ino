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
	if (_encoder.GRAY2BIN[_encoder.gray_code] == -1) {
		if (_encoder.inited) {
			encoder_error(_encoder.gray_code);
		}
	} else {
		encoder.last_value = _encoder.GRAY2BIN[_encoder.gray_code];
		if (! _encoder.inited) {
			_encoder.inited = true;
		}
	}
}


void encoder_error(unsigned int value)
{
	// TODO can we safely ignore invalid values?
	Serial.print(F("Invalid encoder value: "));
	Serial.print(value);
	Serial.print(F("\n"));
}