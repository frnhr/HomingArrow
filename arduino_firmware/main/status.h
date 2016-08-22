#ifndef _INCL_HOMING_ARROW_STATUS
#define _INCL_HOMING_ARROW_STATUS


/***** DEPENDENCIES *****/

#include "_encoder.hpp"
#include "_compass.hpp"
#include "_gps.hpp"
#include "utils.h"


/***** CONFIGURATION *****/

//none


/***** MODULE *****/

// provides: status

// reads: encoder, compass, gps
// writes: --


/***** INTERFACE *****/

struct
{
    float azimuth = 0.0;          // current arrow azimuth
    float azimuth_delta = 0.0;    // difference between desired and current arrow azimuths
    bool inited = false;            // all sensors ready
} status;


/***** INTERNALS *****/

// none

#endif
