#ifndef _INCL_HOMING_ARROW_COMPASS
#define _INCL_HOMING_ARROW_COMPASS


/***** DEPENDENCIES *****/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "motor.h"
#include "utils.h"


/***** CONFIGURATION *****/

// Local compass error due to difference between geographic and magnetic North pole.
#define COMPASS_MAGNETIC_DECLINATION 0.0  // In degrees, see: http://www.magnetic-declination.com/

#define COMPASS_UID 12345


/***** MODULE *****/

// provides: compass

// reads: motor
// writes: --


/***** INTERFACE *****/

typedef struct {
    double azimuth;                 // angle away from the north to the east
    bool inited;                    // device is ready
    bool set_north;                 // command to set current position as North
} CompassInterface;
CompassInterface compass = {
    0.0,                              // azimuth
    false,                            // inited
    false,                            // set_north
};


/***** INTERNALS *****/

typedef struct {
    double offset;                       // offset angle, if compass module or box not mounted northward 
    double last_value;                   // last raw value
    Adafruit_HMC5883_Unified sensor;    
    sensors_event_t event;
} CompassInternals;
CompassInternals _compass = {
    0.0,                                    // offset
    0.0,                                    // last_value
    Adafruit_HMC5883_Unified(COMPASS_UID),  // sensor
    NULL,                                   // event
};


/* PROTOTYPES */

void compass_setup();
void compass_loop();

#endif
