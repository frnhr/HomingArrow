#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef ACC_CALIBRATION_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define ACC_CALIBRATION_INO_HPP
#include "_acc_calibration.hpp"

#ifndef ACCELEROMETER_INO_HPP
  #error "acc_calibration" module required "accelerometer" module
#endif


#include "_accelerometer.hpp"


void AccCalibration::setup()
{
  Serial.print(F("[acc_calibration ]\t"));

  uint8_t signature;
  EEPROM.get(ACC_CALIBRATION_EEPROM_ADDR_SIGNATURE, signature);
  if (signature == ACC_CALIBRATION_SIGNATURE) {
    EEPROM.get(ACC_CALIBRATION_EEPROM_ADDR_MAX_X, x_max);
    EEPROM.get(ACC_CALIBRATION_EEPROM_ADDR_MIN_X, x_min);
    EEPROM.get(ACC_CALIBRATION_EEPROM_ADDR_MAX_Y, y_max);
    EEPROM.get(ACC_CALIBRATION_EEPROM_ADDR_MIN_Y, y_min);
    EEPROM.get(ACC_CALIBRATION_EEPROM_ADDR_MAX_Z, z_max);
    EEPROM.get(ACC_CALIBRATION_EEPROM_ADDR_MIN_Z, z_min);
    x_range = x_max - x_min;
    y_range = y_max - y_min;
    z_range = z_max - z_min;
    // TODO one of these is probably redundant:
    inited = true;
    calibrated = true;
  }
}


void AccCalibration::loop()
{

  bool justUpdated = false;

  // clear EEPROM data completely (for testing):
  if (setClearEeprom) {
    setClearEeprom = false;
    for (uint16_t addr=ACC_CALIBRATION_EEPROM_ADDR_BASE; addr<ACC_CALIBRATION_EEPROM_ADDR_END; addr++) {
      EEPROM.write(addr, 0);
    }
  }


  if (setStartCalibration && !calibrating) {
    // clear setter:
    setStartCalibration = false;
    // clear all values:
    x_max = ACC_CALIBRATION_FALSE_MAX;
    x_min = ACC_CALIBRATION_FALSE_MIN;
    y_max = ACC_CALIBRATION_FALSE_MAX;
    y_min = ACC_CALIBRATION_FALSE_MIN;
    z_max = ACC_CALIBRATION_FALSE_MAX;
    z_min = ACC_CALIBRATION_FALSE_MIN;
    x_range = 0;
    y_range = 0;
    z_range = 0;
    x_zero = 0;
    y_zero = 0;
    z_zero = 0;
    // set flag:
    calibrating = true;
    return;  // allow one loop for accelerometer to start providing uncalibrated data
  }

  // handle end-of-calibration commands:
  if (setCancelCalibration) {
    setCancelCalibration = false;
    if (calibrating) {
      calibrating = false;
      calibrated = true;
    }
  }
  if (setSaveCalibration) {
    setSaveCalibration = false;
    if (calibrating) {
      calibrating = false;
      calibrated = true;
    }
    setWriteToEeprom = true;  // setting own setter!
    inited = true;
    calibrated = true;
  }

  // write to EEPROM:
  if (setWriteToEeprom) {
    setWriteToEeprom = false;
    EEPROM.put(ACC_CALIBRATION_EEPROM_ADDR_MAX_X, x_max);
    EEPROM.put(ACC_CALIBRATION_EEPROM_ADDR_MIN_X, x_min);
    EEPROM.put(ACC_CALIBRATION_EEPROM_ADDR_MAX_Y, y_max);
    EEPROM.put(ACC_CALIBRATION_EEPROM_ADDR_MIN_Y, y_min);
    EEPROM.put(ACC_CALIBRATION_EEPROM_ADDR_MAX_Z, z_max);
    EEPROM.put(ACC_CALIBRATION_EEPROM_ADDR_MIN_Z, z_min);
  }


  // only do anything else while calibrating:
  if (! calibrating) return;

  // cancel calibragtion if no accelerometer data:
  if (!accelerometer->inited) {
    calibrating = false;
    return;
  }


  // find min and max values for every axes:

  if (accelerometer->x < x_min) {
    x_min = accelerometer->x;
    justUpdated = true;
  }
  if (accelerometer->x > x_max) {
      x_max = accelerometer->x;
      justUpdated = true;
  }

  if (accelerometer->y < y_min) {
      y_min = accelerometer->y;
      justUpdated = true;
  }
  if (accelerometer->y > y_max) {
      y_max = accelerometer->y;
      justUpdated = true;
  }

  if (accelerometer->z < z_min) {
      z_min = accelerometer->z;
      justUpdated = true;
  }
  if (accelerometer->z > z_max) {
      z_max = accelerometer->z;
      justUpdated = true;
  }

  // store ranges and zero points, for convenience:

  x_range = x_max - x_min;
  y_range = y_max - y_min;
  z_range = z_max - z_min;

  x_zero = (x_max + x_min) / 2.0;
  y_zero = (y_max + y_min) / 2.0;
  z_zero = (z_max + z_min) / 2.0;

  if (justUpdated) {
    Serial.print(F("Acc update: ("));
    Serial.print(x_min);
    Serial.print(F(","));
    Serial.print(x_max);
    Serial.print(F("), ("));
    Serial.print(y_min);
    Serial.print(F(","));
    Serial.print(y_max);
    Serial.print(F("), ("));
    Serial.print(z_min);
    Serial.print(F(","));
    Serial.print(z_max);
    Serial.print(F(")\n"));
  }
}
