#ifndef _INCL_HOMING_ARROW_MOTOR
#define _INCL_HOMING_ARROW_MOTOR


/***** DEPENDENCIES *****/

#include <math.h>
#include "status.h"


/***** CONFIGURATION *****/

#define MOTOR_PIN_ENABLE 12
#define MOTOR_PIN_AZ_PLUS 11
#define MOTOR_PIN_AZ_MINUS 10
#define MOTOR_MAX_SPEED 255
#define MOTOR_MIN_SPEED 80

// TODO move these to status?
#define MOTOR_DEADZONE 4.0   // degrees
#define MOTOR_SLOWZONE 30.0  // degrees


/***** MODULE *****/

// provides: motor

// reads: status
// writes: --


/***** INTERFACE *****/

typedef struct {
    bool running;
} MotorInterface;
MotorInterface motor = {
    false,  // running
};


/***** INTERNALS *****/

typedef struct {
    int speed;                  // PWM duty cycle
    double deadzone;            // deadzone azimuth (deg), motor won't move if within
    double slowzone;            // slowzone azimuth (deg), motor will move with low_speed within
    int active_pin;             // pin_az_plus or pin_az_minus
    int last_active_pin;        // for comparison with active_pin
} MotorInternals;
MotorInternals _motor = {
    0,                        // speed
    deg2rad(MOTOR_DEADZONE),  // deadzone
    deg2rad(MOTOR_SLOWZONE),  // slowzone
    0,                        // active_pin
    0,                        // last_active_pin
};


/* PROTOTYPES */

void motor_setup();
void motor_loop();

#endif
