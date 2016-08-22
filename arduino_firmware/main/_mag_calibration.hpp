#include <Arduino.h>
#include "modules.hpp"

#ifndef MAG_CALIBRATION_HPP
#define MAG_CALIBRATION_HPP


#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>


#define MAG_CALIBRATION_FALSE_MAX -5000
#define MAG_CALIBRATION_FALSE_MIN 5000

#ifndef MAG_CALIBRATION_EEPROM_ADDR_BASE
  #define MAG_CALIBRATION_EEPROM_ADDR_BASE 200
#endif
#define MAG_CALIBRATION_EEPROM_ADDR_SIGNATURE (MAG_CALIBRATION_EEPROM_ADDR_BASE)
#define MAG_CALIBRATION_SIGNATURE ((uint8_t)212)
#define MAG_CALIBRATION_EEPROM_ADDR_MAX_X (MAG_CALIBRATION_EEPROM_ADDR_BASE + 4 * 1)
#define MAG_CALIBRATION_EEPROM_ADDR_MIN_X (MAG_CALIBRATION_EEPROM_ADDR_BASE + 4 * 2)
#define MAG_CALIBRATION_EEPROM_ADDR_MAX_Y (MAG_CALIBRATION_EEPROM_ADDR_BASE + 4 * 3)
#define MAG_CALIBRATION_EEPROM_ADDR_MIN_Y (MAG_CALIBRATION_EEPROM_ADDR_BASE + 4 * 4)
#define MAG_CALIBRATION_EEPROM_ADDR_MAX_Z (MAG_CALIBRATION_EEPROM_ADDR_BASE + 4 * 5)
#define MAG_CALIBRATION_EEPROM_ADDR_MIN_Z (MAG_CALIBRATION_EEPROM_ADDR_BASE + 4 * 6)
#define MAG_CALIBRATION_EEPROM_ADDR_END (MAG_CALIBRATION_EEPROM_ADDR_BASE + 4 * 7)


class MagCalibration: public Module
{
private:
public:
  int16_t x_max = MAG_CALIBRATION_FALSE_MAX;
  int16_t x_min = MAG_CALIBRATION_FALSE_MIN;
  int16_t y_max = MAG_CALIBRATION_FALSE_MAX;
  int16_t y_min = MAG_CALIBRATION_FALSE_MIN;
  int16_t z_max = MAG_CALIBRATION_FALSE_MAX;
  int16_t z_min = MAG_CALIBRATION_FALSE_MIN;
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
  MagCalibration(){};
};

MagCalibration* mag_calibration = (MagCalibration*) ModulesRegistry::add(new MagCalibration());

#endif  // #ifndef MAG_CALIBRATION_HPP
