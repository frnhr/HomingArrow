#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef MAGNETOMETER_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define MAGNETOMETER_INO_HPP
#include "_magnetometer.hpp"


void Magnetometer::setup()
{
  Serial.print(F("[magnetometer   ]\t"));
}


void Magnetometer::loop()
{
  // read setters and copy to internal:
  // ... also apply calibration if available:
  if (setX != MAGNETOMETER_NULL_VALUE) {
    _x = setX;
    #ifdef MAG_CALIBRATION_HPP
      if (!mag_calibration->calibrated && !magnetometer->calibrating) {
        _x = (_x - mag_calibration->x_min) * MAGNETOMETER_RESOLUTION / mag_calibration->x_range;
      }
    #endif
    setX = MAGNETOMETER_NULL_VALUE;
  }
  if (setY != MAGNETOMETER_NULL_VALUE) {
    _y = setY;
    #ifdef MAG_CALIBRATION_HPP
      if (!mag_calibration->calibrated && !magnetometer->calibrating) {
        _y = (_y - mag_calibration->y_min) * MAGNETOMETER_RESOLUTION / mag_calibration->y_range;
      }
    #endif
    setY = MAGNETOMETER_NULL_VALUE;
  }
  if (setZ != MAGNETOMETER_NULL_VALUE) {
    _z = setZ;
    #ifdef MAG_CALIBRATION_HPP
      if (!mag_calibration->calibrated && !magnetometer->calibrating) {
        _z = (_z - mag_calibration->z_min) * MAGNETOMETER_RESOLUTION / mag_calibration->z_range;
      }
    #endif
    setY = MAGNETOMETER_NULL_VALUE;
  }

  // copy internal values to public getters:
  // ... on boot internal values will be unset, so check for that as well:
  if (_x != MAGNETOMETER_NULL_VALUE) {
    x = _x;
  }
  if (_y != MAGNETOMETER_NULL_VALUE) {
    y = _y;
  }
  if (_z != MAGNETOMETER_NULL_VALUE) {
    z = _z;
  }

  // when all axes have been set, flag module as initialized:
  if (_x != MAGNETOMETER_NULL_VALUE && _y != MAGNETOMETER_NULL_VALUE && _z != MAGNETOMETER_NULL_VALUE) {
    inited = true;
  }
}
