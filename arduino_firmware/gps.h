/***** INTERFACES *****/

// does not read other modules

// read interface gps

// does not write



/***** INTERFACE *****/

typedef struct {
	double current_lon;     	// cirrent position, distance from the Prime Meridian, negative for W
	double current_lat;    		// current positon, distance from the Equator, negative for S
	double target_lon;	    	// target longitude
	double target_lat;	    	// target latitude
	double azimuth;	    	    // azimuth to target
	double distance;			// target distance
	double target_zone;			// radius around target coords that is considered to be "on target"
	bool on_target;				// target reached
	bool inited;		  		// device is ready
} GPSInterface;
GPSInterface gps = {
	0.0,		// current_lon
	0.0,		// current_lat
	0.0,		// target_lon
	0.0,		// target_lat
	0.0,		// distance
	0.0,		// azimuth
	10.0,		// target_zone
	false,		// on_target
	false		// inited
};


/***** INTERNALS *****/

typedef struct {
	const double earth_cr;  // mean Earth circumference
} GPSInternals;
GPSInternals _gps = {
	6371009 * 2 * M_PI,	// earth_cr
};


/* PROTOTYPES */

void gps_setup();
void gps_loop();
