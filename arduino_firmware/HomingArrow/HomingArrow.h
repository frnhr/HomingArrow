
/***** DEPENDENCIES *****/

#include "Arduino.h"
// (everything else, automatically handled by Arduino)


/***** CONFIGURATION *****/

#define VERSION "0.9.0"
#define NAME "Homing Arrow"

#define LOOP_FAST_INTERVAL 100
#define LOOP_SLOW_INTERVAL 5000


/***** INTERFACE *****/

typedef struct
{
    char * name;
    char * version;
} HomingArrowInterface;
HomingArrowInterface homing_arrow = {
    NAME,       // name
    VERSION,    // version
};


/***** INTERNALS *****/

typedef struct
{
    unsigned long now;
    unsigned long fast_timer;
    unsigned long slow_timer;
} LoopInternals;
LoopInternals _loop = {
    0,      // now
    0,      // fast_timer
    0,      // slow_timer
};


/***** PROTOTYPES *****/

void setup();
void loop();
void realtime_loop();
void fast_loop();
void slow_loop();
