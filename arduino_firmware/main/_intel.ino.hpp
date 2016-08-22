#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef INTEL_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define INTEL_INO_HPP
#include "_intel.hpp"





#include "_motor.hpp"


void Intel::setup()
{
}


void Intel::loop()
{


  motor->setSpeed = 100;
  motor->setAction = MOTOR_UP;
  
}
