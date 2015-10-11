#ifndef _INCL_HOMING_ARROW_CAL_COMPASS
#define _INCL_HOMING_ARROW_CAL_COMPASS


/***** DEPENDENCIES *****/

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>


/***** CONFIGURATION *****/

#define COMPASS_UNCALIBRATED_MAX 1050


/***** MODULE *****/

// provides: compass


/***** INTERFACE *****/

struct {
    bool just_updated = false;
    bool run = true;
} compass;


/***** INTERNALS *****/

struct {
    bool just_updated = false;
    Adafruit_LSM303 sensor;  // library object, implements serial
    unsigned long pass = 0;
    // initial values, deliberately reverted:
    int x_max = -1 * COMPASS_UNCALIBRATED_MAX;
    int x_min = +1 * COMPASS_UNCALIBRATED_MAX;
    int y_max = -1 * COMPASS_UNCALIBRATED_MAX;
    int y_min = +1 * COMPASS_UNCALIBRATED_MAX;
    int z_max = -1 * COMPASS_UNCALIBRATED_MAX;
    int z_min = +1 * COMPASS_UNCALIBRATED_MAX;
    double x_p = 0;
    double y_p = 0;
    double z_p = 0;
    char active_axes = ' ';
} _compass;


/* PROTOTYPES */

void compass_setup();
void compass_loop();
void compass_serial_loop();

#endif
