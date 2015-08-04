//C1.ino

#include "C1.h"

void setup()
{
  	serial_setup();
  	blink_setup();
}


void loop()
{
	serial_loop();
	blink_loop();
}
