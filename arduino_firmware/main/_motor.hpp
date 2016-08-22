#include <Arduino.h>
#include "modules.hpp"


#ifndef MOTOR_HPP
#define MOTOR_HPP


#include <math.h>
#include "utils.h"


#define MOTOR_PIN_ENABLE 12
#define MOTOR_PIN_UP 11
#define MOTOR_PIN_DN 10
#define MOTOR_MAX_SPEED 255  // PWM, 255 = 100%
#define MOTOR_MIN_SPEED 130   // PWM, lower then 100 sometime causes stall when starting, but this is depemndent on gearing, etc.
#define MOTOR_PIN_ACTIVE_ON_TARGET MOTOR_PIN_AZ_PLUS  // direction of rotation when on target

#define MOTOR_NULL 0
#define MOTOR_UP 1
#define MOTOR_DN 2
#define MOTOR_STOP 3

#define MOTOR_SPEED_NULL 150


class Motor: public Module
{
private:
  int8_t active_pin = 0;                         // pin_az_plus or pin_az_minus
  int8_t last_active_pin = 0;                    // for comparison with active_pin
  int8_t _action = MOTOR_STOP;
  int8_t _speed = 0;
public:
  bool running = false;
  bool inited = false;
  int8_t action = MOTOR_STOP;
  uint8_t setAction = MOTOR_NULL;
  int8_t speed = 0;
  int8_t setSpeed = MOTOR_SPEED_NULL;

  void setup();
  void loop();
};

Motor* motor = (Motor*) ModulesRegistry::add(new Motor());

#endif  // #ifndef MOTOR_HPP
