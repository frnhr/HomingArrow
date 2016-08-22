#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef ACCELEROMETER_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define ACCELEROMETER_INO_HPP
#include "_accelerometer.hpp"


void Accelerometer::setup()
{
  Serial.print(F("[accelerometer  ]\t"));
}


void Accelerometer::loop()
{
  // read setters and copy to internal:
  // ... also apply calibration if available:
  if (setX != ACCELEROMETER_NULL_VALUE) {
    _x = setX;
    #ifdef ACC_CALIBRATION_HPP
      if (acc_calibration->calibrated && !acc_calibration->calibrating) {
        _x = (_x - acc_calibration->x_min) * MAGNETOMETER_RESOLUTION / acc_calibration->x_range;
      }
    #endif
    setX = ACCELEROMETER_NULL_VALUE;
  }
  if (setY != ACCELEROMETER_NULL_VALUE) {
    _y = setY;
    #ifdef ACC_CALIBRATION_HPP
      if (acc_calibration->calibrated && !acc_calibration->calibrating) {
        _y = (_y - acc_calibration->y_min) * MAGNETOMETER_RESOLUTION / acc_calibration->y_range;
      }
    #endif
    setY = ACCELEROMETER_NULL_VALUE;
  }
  if (setZ != ACCELEROMETER_NULL_VALUE) {
    _z = setZ;
    #ifdef ACC_CALIBRATION_HPP
      if (acc_calibration->calibrated && !acc_calibration->calibrating) {
        _z = (_z - acc_calibration->z_min) * MAGNETOMETER_RESOLUTION / acc_calibration->z_range;
      }
    #endif
    setY = ACCELEROMETER_NULL_VALUE;
  }

  // copy internal values to public getters:
  // ... on boot internal values will be unset, so check for that as well:
  if (_x != ACCELEROMETER_NULL_VALUE) {
    x = _x;
  }
  if (_y != ACCELEROMETER_NULL_VALUE) {
    y = _y;
  }
  if (_z != ACCELEROMETER_NULL_VALUE) {
    z = _z;
  }

  // when all axes have been set, flag module as initialized:
  if (_x != ACCELEROMETER_NULL_VALUE && _y != ACCELEROMETER_NULL_VALUE && _z != ACCELEROMETER_NULL_VALUE) {
    inited = true;
  }
}
