#include "motor.h"

void motor_setup()
{
	pinMode(motor.pin_enable, OUTPUT);
	digitalWrite(motor.pin_enable, LOW);
	pinMode(motor.pin_az_plus, OUTPUT);
	digitalWrite(motor.pin_az_plus, LOW);
	pinMode(motor.pin_az_minus, OUTPUT);
	digitalWrite(motor.pin_az_minus, LOW);	
}

void motor_loop()
{
	digitalWrite(motor.pin_enable, HIGH);
	analogWrite(motor.pin_az_plus, 127);
	analogWrite(motor.pin_az_minus, 255);
}
