#ifndef _INCL_HOMING_ARROW_MOTOR
#define _INCL_HOMING_ARROW_MOTOR

#include "status.h"

/***** INTERFACES *****/

// reads status

// no read interface
// TODO refactor hardware configuration out of the interface

// no write interface


/***** INTERFACE *****/

typedef struct {
	int pin_enable;
	int pin_az_plus;
	int pin_az_minus;
	bool running;
    int full_speed;
    int low_speed;
} MotorInterface;
MotorInterface motor = {
	12,		// pin_enable
	11,		// pin_az_plus
	10,		// pin_az_minus
	false,	// running
    255,    // full_speed
    90,     // low_speed
};


/***** INTERNALS *****/

typedef struct {
    int speed;          		// PWM duty cycle
    double deadzone;            // deadzone azimuth (deg), motor won't move if within
    double slowzone;			// slowzone azimuth (deg), motor will move with low_speed within
    unsigned long ramp;			// ramp duration, millis
    unsigned long ramp_start;	// time when ramp was started
    int ramp_value;				// current ramp value, 0 - 255
    int last_ramp_value;		// last used ramp value
    int active_pin;				// pin_az_plus or pin_az_minus
} MotorInternals;
MotorInternals _motor = {
	0,              // speed
    deg2rad(2.0),   // deadzone
    deg2rad(10.0),  // deadzone
    0,              // ramp
    0,              // ramp_start
    0,              // ramp_value
    0,              // last_ramp_value
    0,              // active_pin
};


/* PROTOTYPES */

void motor_setup();
void motor_loop();

#endif
