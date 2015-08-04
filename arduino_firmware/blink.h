

/***** INTERFACES *****/

// does not read other modules

// read interface blink

// does not write



/***** INTERFACE *****/

typedef struct {
	unsigned long interval;     // blink interval, millis
} BlinkInterface;
BlinkInterface blink = {
	1000,  // interval
};


/***** INTERNALS *****/

typedef struct {
	int led;					// pin
	bool state;				    // led HIGH or LOW
	unsigned _last_blink;       // millis of last blink
} BlinkInternals;
BlinkInternals _blink = {
	13,    // pin 13, built-in LED
	true,  // state
	0	   // _last_blink
};


/* PROTOTYPES */

void blink_setup();
void blink_loop();