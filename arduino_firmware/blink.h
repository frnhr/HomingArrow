

/* DATA */

typedef struct {
	int led;					// pin
	unsigned long interval;     // blink interval, millis
	bool state;				    // led HIGH or LOW
	unsigned _last_blink;       // millis of last blink
} Blink;
Blink blink = {
	13,    // pin 13, built-in LED
	1000,  // interval
	true,  // state
	0	   // _last_blink
};


/* PROTOTYPES */

void blink_setup();
void blink_loop();
