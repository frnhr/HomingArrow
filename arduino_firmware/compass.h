#ifndef _INCL_HOMING_ARROW_COMPASS
#define _INCL_HOMING_ARROW_COMPASS

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>


/***** INTERFACES *****/

// does not read other modules

// read interface compass

// does not write



/***** INTERFACE *****/

typedef struct {
	double azimuth;					// angle away from the north to the east
	bool inited;					// device is ready
	bool set_north;					// command to set current position as North
	double magnetic_declination;	// local compass error due to difference between geographic and magnetic North pole
} CompassInterface;
CompassInterface compass = {
	0.0,  	// azimuth
	false,	// inited
	false,	// set_north
	0.0,  	// magnetic_declination
};


/***** INTERNALS *****/

typedef struct {
	double offset;		 // offset angle, if compass module or box not mounted northward 
	double last_value;   // last raw value
	Adafruit_HMC5883_Unified sensor;
} CompassInternals;
CompassInternals _compass = {
	0.0,  	// offset
	0.0,  	// last_value
	Adafruit_HMC5883_Unified(12345),	// sensor
};


/* PROTOTYPES */

void compass_setup();
void compass_loop();

#endif
