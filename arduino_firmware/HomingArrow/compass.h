#ifndef _INCL_HOMING_ARROW_COMPASS
#define _INCL_HOMING_ARROW_COMPASS


/***** DEPENDENCIES *****/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include <math.h>
#include "motor.h"
#include "utils.h"


/***** CONFIGURATION *****/

// Local compass error due to difference between geographic and magnetic North pole.
#define COMPASS_MAGNETIC_DECLINATION 0.0  // In degrees, see: http://www.magnetic-declination.com/

#define COMPASS_MAX_ACCEL 1050  // Vertical acceleration (m/s2), not very precise

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
    double last_value = 0.0;                 // last raw value
    double corrected_x = 0.0;
    double corrected_y = 0.0;
    double alpha_x = 0.0;
    double alpha_y = 0.0;
    Adafruit_LSM303 sensor;    // library object, implements serial
} _compass;


/* PROTOTYPES */

void compass_setup();
void compass_loop();

#endif
