#include "motor.h"


void motor_setup()
{
	pinMode(MOTOR_PIN_ENABLE, OUTPUT);
	digitalWrite(MOTOR_PIN_ENABLE, LOW);
	pinMode(MOTOR_PIN_AZ_PLUS, OUTPUT);
	digitalWrite(MOTOR_PIN_AZ_PLUS, LOW);
	pinMode(MOTOR_PIN_AZ_MINUS, OUTPUT);
	digitalWrite(MOTOR_PIN_AZ_MINUS, LOW);	
}


void motor_loop()
{

	if (! motor.running) {
		if (fabs(status.azimuth_delta) > _motor.deadzone) {
			// start the motor
			_motor.active_pin = (status.azimuth_delta > 0.0) ? MOTOR_PIN_AZ_MINUS : MOTOR_PIN_AZ_PLUS;
			// make sure both pins are off:
			digitalWrite(MOTOR_PIN_AZ_MINUS, LOW);
			digitalWrite(MOTOR_PIN_AZ_PLUS, LOW);
			// set motor.running flag
			motor.running = true;
		} else {
			;  // not running and should not be running, all is well...
		}
	}

	if (motor.running) {
		if (fabs(status.azimuth_delta) > _motor.deadzone / 2.0) {
			// running and should be running
			digitalWrite(MOTOR_PIN_ENABLE, HIGH);
			_motor.active_pin = (status.azimuth_delta > 0.0) ? MOTOR_PIN_AZ_MINUS : MOTOR_PIN_AZ_PLUS;
			if (_motor.active_pin != _motor.last_active_pin) {
				digitalWrite(MOTOR_PIN_AZ_MINUS, LOW);
				digitalWrite(MOTOR_PIN_AZ_PLUS, LOW);
			}

			if (fabs(status.azimuth_delta) < _motor.slowzone) {
				analogWrite(
					_motor.active_pin, 
					(int) (((float)MOTOR_MIN_SPEED) + fabs(status.azimuth_delta) / _motor.slowzone * ((float) (MOTOR_MAX_SPEED - MOTOR_MIN_SPEED)))
				);
			} else {
				analogWrite(_motor.active_pin, MOTOR_MAX_SPEED);				
			}
		} else { // (status.azimuth_delta <= _motor.deadzone)
			// stop it all
			motor.running = false;
			digitalWrite(MOTOR_PIN_ENABLE, LOW);
			digitalWrite(MOTOR_PIN_AZ_MINUS, LOW);
			digitalWrite(MOTOR_PIN_AZ_PLUS, LOW);
		}
	}

	_motor.last_active_pin = _motor.active_pin;
}
