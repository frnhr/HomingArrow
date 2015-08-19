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

	if (! motor.running) {
		if (abs(status.azimuth_delta) > _motor.deadzone) {
			// start the motor
			_motor.active_pin = (status.azimuth_delta > 0.0) ? motor.pin_az_minus : motor.pin_az_plus;
			// make sure both pins are off:
			digitalWrite(motor.pin_az_minus, LOW);
			digitalWrite(motor.pin_az_plus, LOW);
			// set motor.running flag
			motor.running = true;
		} else {
			;  // not running and should not be running, all is well...
		}
	}

	if (motor.running) {
		if (abs(status.azimuth_delta) > _motor.deadzone / 2.0) {
			// running and should be running
			digitalWrite(motor.pin_enable, HIGH);
			if (abs(status.azimuth_delta) < _motor.slowzone) {
				analogWrite(_motor.active_pin, motor.low_speed);
			} else {
				analogWrite(_motor.active_pin, motor.full_speed);				
			}
		} else { // (status.azimuth_delta <= _motor.deadzone)
			// stop it all
			motor.running = false;
			digitalWrite(motor.pin_enable, LOW);
			digitalWrite(motor.pin_az_minus, LOW);
			digitalWrite(motor.pin_az_plus, LOW);
		}
	}
}
