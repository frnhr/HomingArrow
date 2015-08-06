

/***** INTERFACES *****/

// does not read other modules

// read interface compass

// does not write



/***** INTERFACE *****/

typedef struct {
	double azimuth;		// angle away from the north to the east
	double offset;		// offset angle, if compass module or box not mounted northward 
	bool inited;		// device is ready
} CompassInterface;
CompassInterface compass = {
	-1.0,  	// azimuth
	0.0,  	// offset
	false	// inited
};


/***** INTERNALS *****/

typedef struct {
	int ttt;
} CompassInternals;
CompassInternals _compass = {
	1
};


/* PROTOTYPES */

void compass_setup();
void compass_loop();
