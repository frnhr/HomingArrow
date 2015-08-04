//C1.ino


#include "C1.h"


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
}


void blink_loop()
{
	if (millis() - blink._last_blink > blink.interval) {
		blink.state = !blink.state;
		blink._last_blink = millis();
	}
	digitalWrite(led, blink.state);
}
