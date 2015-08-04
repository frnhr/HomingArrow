

/***** INTERFACES *****/

// does not read other modules

// read interface compass

// does not write



/***** INTERFACE *****/

typedef struct {
	float azimuth;		// angle away from the north to the east
	bool inited;		// device is ready
} CompassInterface;
CompassInterface compass = {
	-1.0,  	// azimuth
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
