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

struct {
    double azimuth = 0.0;   // angle away from the north to the east
    bool inited = false;    // device is ready
} compass;


/***** INTERNALS *****/

struct {
    double last_value = 0.0;                        // last raw value
    Adafruit_HMC5883_Unified sensor = Adafruit_HMC5883_Unified(COMPASS_UID);    // library object, implements serial
    sensors_event_t event;                   // library event object
} _compass;


/* PROTOTYPES */

void compass_setup();
void compass_loop();

#endif
