
// TODO maybe make a single calibartion module and just pass pointers to it?


#include <Arduino.h>
#include "modules.hpp"

#ifndef ACC_CALIBRATION_HPP
#define ACC_CALIBRATION_HPP


#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>


#define ACC_CALIBRATION_FALSE_MAX -5000
#define ACC_CALIBRATION_FALSE_MIN 5000

#ifndef ACC_CALIBRATION_EEPROM_ADDR_BASE
  #define ACC_CALIBRATION_EEPROM_ADDR_BASE 200
#endif
#define ACC_CALIBRATION_EEPROM_ADDR_SIGNATURE (ACC_CALIBRATION_EEPROM_ADDR_BASE)
#define ACC_CALIBRATION_SIGNATURE ((uint8_t)211)
#define ACC_CALIBRATION_EEPROM_ADDR_MAX_X (ACC_CALIBRATION_EEPROM_ADDR_BASE + 4 * 1)
#define ACC_CALIBRATION_EEPROM_ADDR_MIN_X (ACC_CALIBRATION_EEPROM_ADDR_BASE + 4 * 2)
#define ACC_CALIBRATION_EEPROM_ADDR_MAX_Y (ACC_CALIBRATION_EEPROM_ADDR_BASE + 4 * 3)
#define ACC_CALIBRATION_EEPROM_ADDR_MIN_Y (ACC_CALIBRATION_EEPROM_ADDR_BASE + 4 * 4)
#define ACC_CALIBRATION_EEPROM_ADDR_MAX_Z (ACC_CALIBRATION_EEPROM_ADDR_BASE + 4 * 5)
#define ACC_CALIBRATION_EEPROM_ADDR_MIN_Z (ACC_CALIBRATION_EEPROM_ADDR_BASE + 4 * 6)
#define ACC_CALIBRATION_EEPROM_ADDR_END (ACC_CALIBRATION_EEPROM_ADDR_BASE + 4 * 7)


class AccCalibration: public Module
{
private:
public:
  int16_t x_max = ACC_CALIBRATION_FALSE_MAX;
  int16_t x_min = ACC_CALIBRATION_FALSE_MIN;
  int16_t y_max = ACC_CALIBRATION_FALSE_MAX;
  int16_t y_min = ACC_CALIBRATION_FALSE_MIN;
  int16_t z_max = ACC_CALIBRATION_FALSE_MAX;
  int16_t z_min = ACC_CALIBRATION_FALSE_MIN;
  int16_t x_range = 0;
  int16_t y_range = 0;
  int16_t z_range = 0;
  int16_t x_zero = 0;
  int16_t y_zero = 0;
  int16_t z_zero = 0;

  bool calibrating = false;
  bool setStartCalibration = false;
  bool setSaveCalibration = false;
  bool setCancelCalibration = false;
  bool setWriteToEeprom = false;
  bool setClearEeprom = false;
  bool calibrated = false;
  bool inited = false;

  void setup();
  void loop();
  AccCalibration(){};
};

AccCalibration* acc_calibration = (AccCalibration*) ModulesRegistry::add(new AccCalibration());

#endif  // #ifndef ACC_CALIBRATION_HPP
