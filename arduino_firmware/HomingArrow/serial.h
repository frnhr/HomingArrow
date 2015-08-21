#ifndef _INCL_HOMING_ARROW_SERIAL
#define _INCL_HOMING_ARROW_SERIAL


/***** DEPENDENCIES *****/

#include "status.h"
#include "encoder.h"
#include "compass.h"
#include "gps.h"
#include "utils.h"


/***** CONFIGURATION *****/

#define SERIAL_BAUD_RATE 9600


/***** MODULE *****/

// provides: none

// reads: status, homing_arrow
// writes: --


/***** INTERNALS *****/

typedef struct {
    unsigned int baud_rate;
    String data_received;
    bool reading_complete;
} SerialComm;
SerialComm _serial = {
    SERIAL_BAUD_RATE,   // baud_rate
    "",                 // data_received
    false               // reading_complete
};


/***** PROTOTYPES *****/

void serial_setup();
void serial_loop();

#endif
