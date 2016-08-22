#include <Arduino.h>
#include "modules.hpp"


#ifndef INTEL_HPP
#define INTEL_HPP


#include <math.h>
#include "utils.h"



class Intel: public Module
{
private:
public:
  void setup();
  void loop();
};

Intel* intel = (Intel*) ModulesRegistry::add(new Intel());

#endif  // #ifndef INTEL_HPP
