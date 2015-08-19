#include "Arduino.h"
#include "_homing_arrow.h"

void setup()
{
  	serial_setup();
  	compass_setup();
  	gps_setup();
  	encoder_setup();
  	motor_setup();
  	blink_setup();
}



void loop()
{
	serial_loop();
	compass_loop();
	gps_loop();
	encoder_loop();
	status_loop();
	motor_loop();
	blink_loop();
}
