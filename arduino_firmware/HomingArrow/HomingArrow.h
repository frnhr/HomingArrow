
/***** DEPENDENCIES *****/

#include "Arduino.h"
// (everything else, automatically handled by Arduino)


/***** CONFIGURATION *****/

#define VERSION "1.0.3"
#define NAME "Homing Arrow"

#define LOOP_FAST_INTERVAL 100
#define LOOP_SLOW_INTERVAL 5000


/***** INTERFACE *****/

struct
{
    char * name = NAME;
    char * version = VERSION;
} homing_arrow;


/***** INTERNALS *****/

struct
{
    unsigned long now = 0;
    unsigned long fast_timer = 0;
    unsigned long slow_timer = 0;
} _loop;


/***** PROTOTYPES *****/

void setup();
void loop();
void realtime_loop();
void fast_loop();
void slow_loop();
