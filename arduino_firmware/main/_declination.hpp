#include <Arduino.h>
#include "modules.hpp"


#ifndef DECLINATION_HPP
#define DECLINATION_HPP



class Declination: public Module
{
private:
  uint16_t * pattern;
  uint8_t pattern_i;
  unsigned long last_declination;

public:
  uint16_t patterns[DECLINATION_INTERVALS_N * DECLINATION_PATTERNS_N + 1];
  int8_t set_pattern;
  void setup();
  void loop();
  Declination():
    patterns{DECLINATION_PATTERNS}
  {};
};

Declination* declination = (Declination*) ModulesRegistry::add(new Declination());

#endif  // #ifndef DECLINATION_HPP
