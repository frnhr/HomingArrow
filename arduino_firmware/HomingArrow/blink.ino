
#include "blink.h"

void blink_setup() 
{
	pinMode(_blink.led, OUTPUT);
}


void blink_loop()
{
	if (millis() - _blink._last_blink > blink.interval) {  // TODO make overflow-safe
		_blink.state = ! _blink.state;
		_blink._last_blink = millis();
		digitalWrite(_blink.led, _blink.state);
	}
}
