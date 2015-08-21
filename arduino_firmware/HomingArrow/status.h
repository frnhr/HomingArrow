#ifndef _INCL_HOMING_ARROW_STATUS
#define _INCL_HOMING_ARROW_STATUS


/***** DEPENDENCIES *****/

#include "status.h"
#include "encoder.h"
#include "compass.h"
#include "gps.h"
#include "utils.h"


/***** CONFIGURATION *****/

//none


/***** MODULE *****/

// provides: status

// reads: encoder, compass, gps
// writes: --


/***** INTERFACE *****/

typedef struct
{
	float azimuth;			// current arrow azimuth
	float azimuth_delta;	// difference between desired and current arrow azimuths
} StatusInterface;
StatusInterface status = {
	0.0,		// azimuth
	0.0,		// azimuth_delta
};


/***** INTERNALS *****/

typedef struct
{
	;
} StatusInternals;
StatusInternals _status = {};

#endif
