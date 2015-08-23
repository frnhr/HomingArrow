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

	/*** DECIDE WHAT TO DO ***/ 

	_motor.active_pin = 0;
	if (gps.on_target) {
		// spin in one direction
		_motor.active_pin = MOTOR_PIN_ACTIVE_ON_TARGET;
	} else {
		if (fabs(status.azimuth_delta) > _motor.deadzone) {
			_motor.active_pin = (status.azimuth_delta > 0.0) ? MOTOR_PIN_AZ_MINUS : MOTOR_PIN_AZ_PLUS;
		}
	}

	/*** DO IT ***/

	if (_motor.active_pin) {

		// set speed
		if (fabs(status.azimuth_delta) >= _motor.slowzone || gps.on_target) {
			// outside slowzone or on target, full speed:
			analogWrite(_motor.active_pin, MOTOR_MAX_SPEED);				
		} else {
			// inside slowzone, calculate speed:
			analogWrite(
				_motor.active_pin, 
				(int) (((float)MOTOR_MIN_SPEED) + fabs(status.azimuth_delta) / _motor.slowzone * ((float) (MOTOR_MAX_SPEED - MOTOR_MIN_SPEED)))
			);
		}

		if (_motor.active_pin != _motor.last_active_pin) {
			// if something is changed, turn of both pins to make sure only one will eventually be activated
			digitalWrite(MOTOR_PIN_AZ_MINUS, LOW);
			digitalWrite(MOTOR_PIN_AZ_PLUS, LOW);
		}

		// enable motor:
		digitalWrite(MOTOR_PIN_ENABLE, HIGH);
	} else {
		// disable motor:
		digitalWrite(MOTOR_PIN_ENABLE, LOW);
		// lower control lines, for good measure...
		digitalWrite(MOTOR_PIN_AZ_MINUS, LOW);
		digitalWrite(MOTOR_PIN_AZ_PLUS, LOW);
	}

	// for next loop:
	_motor.last_active_pin = _motor.active_pin;

	/*** PUBLISH MOTOR STATUS ***/
	motor.running = (bool) _motor.active_pin;
}
