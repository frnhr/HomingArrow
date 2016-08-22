/** Arrow position

This module is just in interface between module for the hardware encoder and other mudules.

Encoder module is responsible for pushing angle data into this module.
Other modules should read arrow azimuth data only from this module.

*/


#include <Arduino.h>
#include "modules.hpp"


#ifndef ARROW_HPP
#define ARROW_HPP


#include <EEPROM.h>
#include "utils.h"


#ifndef ARROW_EEPROM_BASE_ADDR
  #define ARROW_EEPROM_BASE_ADDR 400
#endif
#define ARROW_EEPROM_ADDR_SIGNATURE ARROW_EEPROM_BASE_ADDR
#define ARROW_EEPROM_ADDR_OFFSET ARROW_EEPROM_BASE_ADDR + 2
#define ARROW_EEPROM_SIGNATURE ((uint8_t) 210)


#define ARROW_NULL_VALUE 500.0
#define ARROW_NULL_EPSOLIN 0.01


class Arrow: public Module
{
private:
  double _offset = 0.0;

public:
  bool inited = false;
  bool configured = false;
  double azimuth = 0.0;                   // angle to the geographic North
  double setOffset = ARROW_NULL_VALUE;
  double setAzimuth = ARROW_NULL_VALUE;
  double setCurrentAzimuth = ARROW_NULL_VALUE;
  void setup();
  void loop();
};

Arrow* arrow = (Arrow*) ModulesRegistry::add(new Arrow());

#endif  // #ifndef ARROW_HPP
