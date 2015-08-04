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
	encoder.last_value = _encoder.GRAY2BIN[_encoder.gray_code];

	Serial.print(encoder.last_value);
	Serial.print("\n");
}
