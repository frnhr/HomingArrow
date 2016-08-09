#ifndef _INCL_HOMING_ARROW_BATTERY
#define _INCL_HOMING_ARROW_BATTERY

/***** DEPENDENCIES *****/

// none


/***** CONFIGURATION *****/

#define BATTERY_ADC_PIN A6
#define BATTERY_TRESHOLD 7.5
#define BATTERY_DIVIDER 3.0

/***** MODULE *****/

// provides: BATTERY

// reads: none
// writes: none


/***** INTERFACE *****/

struct {
    float voltage = 0.0;
    bool is_low = false;
} battery;


/***** INTERNALS *****/

// none


/* PROTOTYPES */

void battery_setup();
void battery_loop();

#endif
