#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef MOTOR_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define MOTOR_INO_HPP
#include "_motor.hpp"


void Motor::setup()
{
	pinMode(MOTOR_PIN_ENABLE, OUTPUT);
	digitalWrite(MOTOR_PIN_ENABLE, LOW);
	pinMode(MOTOR_PIN_UP, OUTPUT);
	digitalWrite(MOTOR_PIN_UP, LOW);
	pinMode(MOTOR_PIN_DN, OUTPUT);
	digitalWrite(MOTOR_PIN_DN, LOW);
}


void Motor::loop()
{
  // handle setter:
  if (setAction != MOTOR_NULL) {
    _action = setAction;
    setAction = MOTOR_NULL;
  }
  if (setSpeed != MOTOR_SPEED_NULL) {
    _speed = setSpeed / 100.0 * (MOTOR_MAX_SPEED - MOTOR_MIN_SPEED) + MOTOR_MIN_SPEED;
    setSpeed = MOTOR_SPEED_NULL;
  }

  // decide what to do:
  if (action == MOTOR_STOP) {
    active_pin = 0;
    _speed = 0;
  }
  if (action == MOTOR_UP) {
    active_pin = MOTOR_PIN_UP;
  }
  if (action == MOTOR_DN) {
    active_pin = MOTOR_PIN_DN;
  }


  // control the motor:
	if (active_pin != last_active_pin) {
		// if something is changed, turn of both pins to make sure only one will be activated below:
		digitalWrite(MOTOR_PIN_UP, LOW);
		digitalWrite(MOTOR_PIN_DN, LOW);
	}
	if (active_pin) {
    // set speed:
		analogWrite(active_pin, _speed);
    // enable the motor:
    digitalWrite(MOTOR_PIN_ENABLE, HIGH);
	} else {
    // disable the motor:
		digitalWrite(MOTOR_PIN_ENABLE, LOW);
		// lower the control lines:
		digitalWrite(MOTOR_PIN_UP, LOW);
		digitalWrite(MOTOR_PIN_DN, LOW);
  }
  last_active_pin = active_pin;


  // public getters:
  action = _action;
  speed = _speed;
	running = (bool) active_pin;
}
