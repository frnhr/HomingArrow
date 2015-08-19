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
			_motor.ramp_start = millis();			
			_motor.active_pin = (status.azimuth_delta > 0) ? motor.pin_az_minus : motor.pin_az_plus;
			Serial.println(_motor.active_pin);
			// make sure both pins are off:
			digitalWrite(motor.pin_az_minus, LOW);
			digitalWrite(motor.pin_az_plus, LOW);
			// set motor.running flag
			motor.running = true;
		} else {
			// not running and should not be running, all is well...
		}
	}

	if (motor.running) {
		if (abs(status.azimuth_delta) > _motor.deadzone) {
			// running and should be running
			digitalWrite(motor.pin_enable, HIGH);
			if (millis() - _motor.ramp_start < _motor.ramp) {
				analogWrite(_motor.active_pin, (int) ((millis() - _motor.ramp_start) * 255.0 / _motor.ramp));
			} else {
				analogWrite(_motor.active_pin, 110);
			}
		} else { // (status.azimuth_delta <= _motor.deadzone)
			// stop it all
			// TODO follow ramp when stopping
			motor.running = false;
			digitalWrite(motor.pin_enable, LOW);
			digitalWrite(motor.pin_az_minus, LOW);
			digitalWrite(motor.pin_az_plus, LOW);
		}
	}
}
