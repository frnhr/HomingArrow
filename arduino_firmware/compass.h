

/***** INTERFACES *****/

// does not read other modules

// read interface compass

// does not write



/***** INTERFACE *****/

typedef struct {
	double azimuth;		// angle away from the north to the east
	bool inited;		// device is ready
	bool set_north;		// command to set current position as North
} CompassInterface;
CompassInterface compass = {
	-1.0,  	// azimuth
	false,	// inited
	false,	// set_north
};


/***** INTERNALS *****/

typedef struct {
	double offset;		// offset angle, if compass module or box not mounted northward 
} CompassInternals;
CompassInternals _compass = {
	0.0,  	// offset
};


/* PROTOTYPES */

void compass_setup();
void compass_loop();
