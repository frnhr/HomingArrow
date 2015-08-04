
#include "blink.h"

void blink_setup() 
{
	pinMode(blink.led, OUTPUT);
}


void blink_loop()
{
	if (millis() - blink._last_blink > blink.interval) {
		blink.state = !blink.state;
		blink._last_blink = millis();
	}
	digitalWrite(blink.led, blink.state);
}
