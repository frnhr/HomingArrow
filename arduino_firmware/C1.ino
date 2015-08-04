//C1.ino

#include "C1.h"

void setup()
{
  	serial_setup();
  	encoder_setup();
  	blink_setup();
}


void loop()
{
	serial_loop();
	encoder_loop();
	blink_loop();
}
