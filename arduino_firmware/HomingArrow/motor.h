#ifndef _INCL_HOMING_ARROW_MOTOR
#define _INCL_HOMING_ARROW_MOTOR


/***** DEPENDENCIES *****/

#include <math.h>
#include "status.h"


/***** CONFIGURATION *****/

#define MOTOR_PIN_ENABLE 12
#define MOTOR_PIN_AZ_PLUS 11
#define MOTOR_PIN_AZ_MINUS 10
#define MOTOR_MAX_SPEED 255  // PWM, 255 = 100%
#define MOTOR_MIN_SPEED 110   // PWM, lower then 100 sometime causes stall when starting, but this is depemndent on gearing, etc.
#define MOTOR_PIN_ACTIVE_ON_TARGET MOTOR_PIN_AZ_PLUS  // direction of rotation when on target

// TODO move these to status?
#define MOTOR_DEADZONE 360.0 / ENCODER_RESOLUTION / 2 * 1.1   // angle erorr that is still ok (not triggering arrow movement)
															  // 1.1 multiplier defines ammount of overlap between adjecent positioins
#define MOTOR_SLOWZONE 30.0  // degrees


/***** MODULE *****/

// provides: motor

// reads: status, gps, encoder
// writes: --


/***** INTERFACE *****/

struct {
    bool running = false;
} motor;


/***** INTERNALS *****/

struct {
    int speed = 0;                              // PWM duty cycle
    double deadzone = deg2rad(MOTOR_DEADZONE);  // deadzone azimuth (deg), motor won't move if within
    double slowzone = deg2rad(MOTOR_SLOWZONE);  // slowzone azimuth (deg), motor will move with low_speed within
    int active_pin = 0;                         // pin_az_plus or pin_az_minus
    int last_active_pin = 0;                    // for comparison with active_pin
} _motor;


/* PROTOTYPES */

void motor_setup();
void motor_loop();

#endif
