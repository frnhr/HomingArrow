#include <Arduino.h>
#include "modules.hpp"


#ifndef DECLINATION_HPP
#define DECLINATION_HPP


#include <EEPROM.h>
#include "utils.h"


#define DECLINATION_NULL_VALUE 500.0
#define DECLINATION_NULL_EPSILON 0.1

#ifndef DECLINATION_EEPROM_ADDR
  #define DECLINATION_EEPROM_ADDR 500
#endif
#define DECLINATION_EEPROM_VALUE (DECLINATION_EEPROM_ADDR + 1)
#define DECLINATION_SIGN 210.0


class Declination: public Module
{
private:
  float _declination = DECLINATION_NULL_VALUE;

public:
  float setDeclination = DECLINATION_NULL_VALUE;
  float declination = 0.0;
  bool inited = false;
  void setup();
  void loop();
};

Declination* declination = (Declination*) ModulesRegistry::add(new Declination());

#endif  // #ifndef DECLINATION_HPP
