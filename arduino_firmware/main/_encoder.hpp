#include <Arduino.h>
#include "modules.hpp"

#ifndef ENCODER_HPP
#define ENCODER_HPP


/***** DEPENDENCIES *****/

#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "utils.h"
#include "hardware_config.h"

#ifndef ENCODER_PINS
#define ENCODER_PINS {2, 3, 4, 5, 6, 7, 8, 9}
#endif

#define ENCODER_EEPROM_SIGNATURE 123  // arbitrary value to recognise configured state
#define ENCODER_NULL_AZIMUTH 88  // radians

#define ENCODER_RESOLUTION 128
#define ENCODER_EEPROM_ADDR_SIGN 10
#define ENCODER_EEPROM_ADDR_OFFSET 11
#define ENCODER_GRAY_TO_BIN { \
        255,  56,  40,  55,  24,   0,  39,  52, \
          8,  57, 255, 255,  23, 255,  36,  13, \
        120, 255,  41,  54, 255, 255, 255,  53, \
          7, 255, 255, 255,  20,  19, 125,  18, \
        104, 105, 255, 255,  25, 106,  38, 255, \
        255,  58, 255, 255, 255, 255,  37,  14, \
        119, 118, 255, 255, 255, 107, 255, 255, \
          4, 255,   3, 255, 109, 108,   2,   1, \
         88, 255,  89, 255, 255, 255, 255,  51, \
          9,  10,  90, 255,  22,  11, 255,  12, \
        255, 255,  42,  43, 255, 255, 255, 255, \
        255, 255, 255, 255,  21, 255, 126, 127, \
        103, 255, 102, 255, 255, 255, 255, 255, \
        255, 255,  91, 255, 255, 255, 255, 255, \
        116, 117, 255, 255, 115, 255, 255, 255, \
         93,  94,  92, 255, 114,  95, 113,   0, \
         72,  71, 255,  68,  73, 255, 255,  29, \
        255,  70, 255,  69, 255, 255,  35,  34, \
        121, 255, 122, 255,  74, 255, 255,  30, \
          6, 255, 123, 255, 255, 255, 124,  17, \
        255, 255, 255,  67,  26, 255,  27,  28, \
        255,  59, 255, 255, 255, 255, 255,  15, \
        255, 255, 255, 255, 255, 255, 255, 255, \
          5, 255, 255, 255, 110, 255, 111,  16, \
         87,  84, 255,  45,  86,  85, 255,  50, \
        255, 255, 255,  46, 255, 255, 255,  33, \
        255,  83, 255,  44,  75, 255, 255,  31, \
        255, 255, 255, 255, 255, 255, 255,  32, \
        100,  61, 101,  66, 255,  62, 255,  49, \
         99,  60, 255,  47, 255, 255, 255,  48, \
         77,  82,  78,  65,  76,  63, 255,  64, \
         98,  81,  79,  80,  97,  96, 112, 255\
        }


class Encoder: public Module
{
private:
  unsigned int gray_code = 0;             // raw value read from the encoder
  unsigned int position = 255;             // most recent successfully read value
  unsigned int last_error = 255;           // last error value reported (to prevent repeating)
  const unsigned int resolution = \
                  ENCODER_RESOLUTION;     // number of positions for a full circle
  double offset = 0.0;                    // angle between North and encoder zero position
  const byte ENCODER_GRAY2BIN[256] = \
                  ENCODER_GRAY_TO_BIN;    // matrix to decode encoder from gray code without much math
  const int pins[8] = ENCODER_PINS;       // Arduino pins that encoder is connected to
  bool configured = false;                // EEPROM initialed?

public:
  bool inited = false;                    // ever read a good value?
  double azimuth = 0.0;                   // angle to the geographic North (if used with GPS)
  double set_offset = ENCODER_NULL_AZIMUTH;
  double set_azimuth = ENCODER_NULL_AZIMUTH;
  void setup();
  void loop();
  Encoder(){};
};

Encoder* encoder = (Encoder*) ModulesRegistry::add(new Encoder());

#endif  // #ifndef ENCODER_HPP
