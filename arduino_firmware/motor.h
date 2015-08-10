#ifndef _INCL_C1_MOTOR
#define _INCL_C1_MOTOR


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
} MotorInterface;
MotorInterface motor = {
	12,		// pin_enable
	11,		// pin_az_plus
	10,		// pin_az_minus
};


/***** INTERNALS *****/

typedef struct {
    int speed;          	// PWM duty cycle
    int deadzone;			// deadzone azimuth (deg), motor won't move if within
    unsigned long ramp;		// ramp duration, millis
} MotorInternals;
MotorInternals _motor = {
	0,		// speed
    10,		// deadzone
    1000,	// ramp
};


/* PROTOTYPES */

void motor_setup();
void motor_loop();

#endif
