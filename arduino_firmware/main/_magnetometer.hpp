/** Magnetic field sensor interface

This module is just in interface between module for the hardware sensor and other mudules.

Sensor module is responsible for pushing magnetometer data into this module.
Other modules should read magnetometer sensor data only from this module

*/


// TODO magnetometer module should take data from mag_calibration module and correct accordingly!


#include <Arduino.h>
#include "modules.hpp"


#ifndef MAGNETOMETER_HPP
#define MAGNETOMETER_HPP

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>


#define MAGNETOMETER_NULL_VALUE -20999
#define MAGNETOMETER_RESOLUTION 1024


class Magnetometer: public Module
{
private:
  int16_t _x = MAGNETOMETER_NULL_VALUE;
  int16_t _y = MAGNETOMETER_NULL_VALUE;
  int16_t _z = MAGNETOMETER_NULL_VALUE;
public:
  int16_t x = 0;
  int16_t y = 0;
  int16_t z = 0;
  int16_t setX = MAGNETOMETER_NULL_VALUE;
  int16_t setY = MAGNETOMETER_NULL_VALUE;
  int16_t setZ = MAGNETOMETER_NULL_VALUE;
  bool inited = false;
  void setup();
  void loop();
};

Magnetometer* magnetometer = (Magnetometer*) ModulesRegistry::add(new Magnetometer());

#endif  // #ifndef MAGNETOMETER_HPP
