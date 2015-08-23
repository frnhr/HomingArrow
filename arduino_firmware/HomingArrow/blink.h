#ifndef _INCL_HOMING_ARROW_BLINK
#define _INCL_HOMING_ARROW_BLINK

/***** DEPENDENCIES *****/

#include "status.h"


/***** CONFIGURATION *****/

#define BLINK_LED 13  // pin 13, built-in LED

// blink patterns:
#define BLINK_INTERVALS_N 6
#define BLINK_SETUP {1000, 1000, 0, 0, 0, 0}
#define BLINK_IDLE {100, 4900, 0, 0, 0, 0}
#define BLINK_LOW_BATTERY {500, 500, 500, 500, 100, 900}
#define BLINK_GPS {100, 400, 0, 0, 0, 0}

/***** MODULE *****/

// provides: blink

// reads: status, battery
// writes: none


/***** INTERFACE *****/

struct {
    unsigned long * pattern = NULL;     // blink pattern, millis
} blink;


/***** INTERNALS *****/

struct {
    byte i = 0;                                             // interval pointer
    unsigned long pattern_setup[6] = BLINK_SETUP;
    unsigned long pattern_idle[6] = BLINK_IDLE;
    unsigned long pattern_battery[6] = BLINK_LOW_BATTERY;
    unsigned long pattern_gps[6] = BLINK_GPS;
    unsigned long last_blink = 0;                           // millis of last interval transition
} _blink;


/* PROTOTYPES */

void blink_setup();
void blink_loop();

#endif
