/** Acceleration sensor interface

This module is just in interface between module for the hardware sensor and other mudules.

Sensor module is responsible for pushing acceleration data into this module.
Other modules should read acceleration sensor data only from this module

*/


// TODO accelerometer module should take data from acc_calibration module and correct accordingly!


#include <Arduino.h>
#include "modules.hpp"


#ifndef ACCELEROMETER_HPP
#define ACCELEROMETER_HPP


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>


#define ACCELEROMETER_NULL_VALUE -20999
#define ACCELEROMETER_RESOLUTION 1024


class Accelerometer: public Module
{
private:
  int16_t _x = ACCELEROMETER_NULL_VALUE;
  int16_t _y = ACCELEROMETER_NULL_VALUE;
  int16_t _z = ACCELEROMETER_NULL_VALUE;
public:
  int16_t x = 0;
  int16_t y = 0;
  int16_t z = 0;
  int16_t setX = ACCELEROMETER_NULL_VALUE;
  int16_t setY = ACCELEROMETER_NULL_VALUE;
  int16_t setZ = ACCELEROMETER_NULL_VALUE;
  bool inited = false;
  void setup();
  void loop();
};

Accelerometer* accelerometer = (Accelerometer*) ModulesRegistry::add(new Accelerometer());

#endif  // #ifndef ACCELEROMETER_HPP
