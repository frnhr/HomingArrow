#ifndef _INCL_HOMING_ARROW_SERIAL
#define _INCL_HOMING_ARROW_SERIAL


/***** DEPENDENCIES *****/


/***** CONFIGURATION *****/

#define SERIAL_BAUD_RATE 115200


/***** MODULE *****/

// provides: none

// reads: status, homing_arrow
// writes: gps, compass

/***** INTERNALS *****/

struct {
    unsigned int baud_rate = SERIAL_BAUD_RATE;
    bool reading_complete = false;
    String data_received = "";
} _serial;


/***** PROTOTYPES *****/

void serial_setup();
void serial_loop();

#endif
