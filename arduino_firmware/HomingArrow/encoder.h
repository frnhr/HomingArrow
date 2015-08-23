#ifndef _INCL_HOMING_ARROW_ENCODER
#define _INCL_HOMING_ARROW_ENCODER


/***** DEPENDENCIES *****/

#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "utils.h"


/***** CONFIGURATION *****/

#define ENCODER_PINS {2, 3, 4, 5, 6, 7, 8, 9}
#define ENCODER_RESOLUTION 128
#define ENCODER_EEPROM_ADDR 0
#define ENCODER_GRAY_TO_BIN { \
         -1,  56,  40,  55,  24,   0,  39,  52, \
          8,  57,  -1,  -1,  23,  -1,  36,  13, \
        120,  -1,  41,  54,  -1,  -1,  -1,  53, \
          7,  -1,  -1,  -1,  20,  19, 125,  18, \
        104, 105,  -1,  -1,  25, 106,  38,  -1, \
         -1,  58,  -1,  -1,  -1,  -1,  37,  14, \
        119, 118,  -1,  -1,  -1, 107,  -1,  -1, \
          4,  -1,   3,  -1, 109, 108,   2,   1, \
         88,  -1,  89,  -1,  -1,  -1,  -1,  51, \
          9,  10,  90,  -1,  22,  11,  -1,  12, \
         -1,  -1,  42,  43,  -1,  -1,  -1,  -1, \
         -1,  -1,  -1,  -1,  21,  -1, 126, 127, \
        103,  -1, 102,  -1,  -1,  -1,  -1,  -1, \
         -1,  -1,  91,  -1,  -1,  -1,  -1,  -1, \
        116, 117,  -1,  -1, 115,  -1,  -1,  -1, \
         93,  94,  92,  -1, 114,  95, 113,   0, \
         72,  71,  -1,  68,  73,  -1,  -1,  29, \
         -1,  70,  -1,  69,  -1,  -1,  35,  34, \
        121,  -1, 122,  -1,  74,  -1,  -1,  30, \
          6,  -1, 123,  -1,  -1,  -1, 124,  17, \
         -1,  -1,  -1,  67,  26,  -1,  27,  28, \
         -1,  59,  -1,  -1,  -1,  -1,  -1,  15, \
         -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, \
          5,  -1,  -1,  -1, 110,  -1, 111,  16, \
         87,  84,  -1,  45,  86,  85,  -1,  50, \
         -1,  -1,  -1,  46,  -1,  -1,  -1,  33, \
         -1,  83,  -1,  44,  75,  -1,  -1,  31, \
         -1,  -1,  -1,  -1,  -1,  -1,  -1,  32, \
        100,  61, 101,  66,  -1,  62,  -1,  49, \
         99,  60,  -1,  47,  -1,  -1,  -1,  48, \
         77,  82,  78,  65,  76,  63,  -1,  64, \
         98,  81,  79,  80,  97,  96, 112,  -1,\
        }


/***** MODULE *****/

// provides: encoder

// reads: --
// writes: --


/***** INTERFACE *****/

struct {
    bool inited = false;                 // whether a good value was ever read
    const int pins[8] = ENCODER_PINS;   // Arduino pins that encoder is connected to
    double azimuth = 0.0;               // Angle to the geographic North
    double offset = 0.0;                // Angle between North and encoder zero position 
} encoder;


/***** INTERNALS *****/

struct {
    unsigned int gray_code = 0;             // raw value read from the encoder
    unsigned int position = -1;             // most recent successfully read value
    unsigned int last_error = -1;           // last error value reported (to prevent repeating)
    const unsigned int resolution = \
                    ENCODER_RESOLUTION;     // number of positions for a full circle
    double offset = 0.0;                    // offset, used unternally
} _encoder;

const PROGMEM byte ENCODER_GRAY2BIN[256] = ENCODER_GRAY_TO_BIN;


/* PROTOTYPES */

void encoder_setup();
void encoder_loop();
void encoder_error(unsigned int value);

#endif
