#include "C1.h"

void setup()
{
  	serial_setup();
  	compass_setup();
  	gps_setup();
  	encoder_setup();
  	blink_setup();
}


void loop()
{
	serial_loop();
	compass_loop();
	gps_loop();
	encoder_loop();
	blink_loop();
}
