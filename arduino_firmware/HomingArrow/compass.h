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
#define COMPASS_MAGNETIC_DECLINATION 3.2  // In degrees, see: http://www.magnetic-declination.com/

#define COMPASS_AVERAGE_BUFFER 1

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
    double phi = 0.0;        // roll
    double theta = 0.0;      // pitch
    double alpha = deg2rad(COMPASS_MAGNETIC_DECLINATION);
    double delta = 0.0;      // magnetic dip
    double psi = 0.0;        // yaw
    long B = 0;              // magnetic vector module
    double Dx = 0.0;         // shortcut
    double Dy = 0.0;         // shortcut
    Adafruit_LSM303 sensor;  // library object, implements serial
    double average[COMPASS_AVERAGE_BUFFER];
    int average_i = 0;
} _compass;


/* PROTOTYPES */

void compass_setup();
void compass_loop();

#endif
