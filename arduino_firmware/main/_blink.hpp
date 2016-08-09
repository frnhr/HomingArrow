#include <Arduino.h>
#include "modules.hpp"


#ifndef BLINK_HPP
#define BLINK_HPP


// blink patterns:
#define BLINK_INTERVALS_N 6
#define BLINK_PATTERNS_N 4

// *****_____*****_____*****_____
#define BLINK_PATTERN_SETUP 100, 400, 0, 0, 0, 0
#define BLINK_PATTERN_SETUP_I 0

// *_________*_________*_________
#define BLINK_PATTERN_IDLE 100, 4900, 0, 0, 0, 0
#define BLINK_PATTERN_IDLE_I 1

// ***___***___*_____
#define BLINK_PATTERN_LOW_BATTERY 500, 500, 500, 500, 100, 900
#define BLINK_PATTERN_LOW_BATTERY_I 2

// *____*____*____
#define BLINK_PATTERN_GPS 100, 400, 100, 400, 100, 400
#define BLINK_PATTERN_GPS_I 3

// all blink patterns, in order:
#define BLINK_PATTERNS \
  BLINK_PATTERN_SETUP, \
  BLINK_PATTERN_IDLE, \
  BLINK_PATTERN_LOW_BATTERY, \
  BLINK_PATTERN_GPS, \
  0


class Blink: public Module
{
private:
  uint16_t * pattern;
  uint8_t pattern_i;
  unsigned long last_blink;

public:
  uint16_t patterns[BLINK_INTERVALS_N * BLINK_PATTERNS_N + 1];
  int8_t set_pattern;
  void setup();
  void loop();
  Blink():
    patterns{BLINK_PATTERNS}
  {};
};

Blink* blink = (Blink*) ModulesRegistry::add(new Blink());

#endif  // #ifndef BLINK_HPP
