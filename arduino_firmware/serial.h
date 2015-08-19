#ifndef _INCL_HOMING_ARROW_SERIAL
#define _INCL_HOMING_ARROW_SERIAL

/***** INTERFACES *****/

// does not read other modules

// reads homing_arrow

// writes to status (TODO)



/***** INTERFACE *****/

// none


/***** INTERNALS *****/

typedef struct {
	unsigned int baud_rate;
    String data_received;
    bool reading_complete;
} SerialComm;
SerialComm _serial = {
	9600,  // baud_rate
	"",    // data_received
	false  // reading_complete
};



/***** PROTOTYPES *****/

void serial_setup();
void serial_loop();

#endif
