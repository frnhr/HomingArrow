#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include "_mag_calibration.hpp"


#ifndef MAGNETOMETER_HPP
#error "mag_calibration" module required "magnetometer" module
#endif
#include "_magnetometer.hpp"


void MagCalibration::setup()
{}


void MagCalibration::loop()
{

  bool just_updated = false;

  // on first run, read from EEPROM:
  if (!inited && !checked_eeprom) {
    checked_eeprom = true;
    bool has_value;
    EEPROM.get(MAG_CALIBRATION_EEPROM_ADDR_BASE, has_value);

    if (has_value) {
      EEPROM.get(MAG_CALIBRATION_EEPROM_ADDR_MAX_X, x_max);
      EEPROM.get(MAG_CALIBRATION_EEPROM_ADDR_MIN_X, x_min);
      EEPROM.get(MAG_CALIBRATION_EEPROM_ADDR_MAX_Y, y_max);
      EEPROM.get(MAG_CALIBRATION_EEPROM_ADDR_MIN_Y, y_min);
      EEPROM.get(MAG_CALIBRATION_EEPROM_ADDR_MAX_Z, z_max);
      EEPROM.get(MAG_CALIBRATION_EEPROM_ADDR_MIN_Z, z_min);
      x_range = x_max - x_min;
      y_range = y_max - y_min;
      z_range = z_max - z_min;
      // TODO one of these two is probably redundant:
      inited = true;
      calibrated = true;
    }
  }

  // clear EEPROM data completely (for testing):
  if (set_clear_eeprom) {
    set_clear_eeprom = false;
    for (uint16_t addr=MAG_CALIBRATION_EEPROM_ADDR_BASE; addr<MAG_CALIBRATION_EEPROM_ADDR_END; addr++) {
      EEPROM.write(addr, 0);
    }
  }


  if (set_start_calibration && !calibrating) {
    // clear setter:
    set_start_calibration = false;
    // clear all values:
    x_max = MAG_CALIBRATION_FALSE_MAX;
    x_min = MAG_CALIBRATION_FALSE_MIN;
    y_max = MAG_CALIBRATION_FALSE_MAX;
    y_min = MAG_CALIBRATION_FALSE_MIN;
    z_max = MAG_CALIBRATION_FALSE_MAX;
    z_min = MAG_CALIBRATION_FALSE_MIN;
    x_range = 0;
    y_range = 0;
    z_range = 0;
    x_zero = 0;
    y_zero = 0;
    z_zero = 0;
    // set flag:
    calibrating = true;
  }

  // handle end-of-calibration commands:
  if (set_cancel_calibration) {
    set_cancel_calibration = false;
    if (calibrating) {
      calibrating = false;
      calibrated = true;
    }
  }
  if (set_save_calibration) {
    set_save_calibration = false;
    if (calibrating) {
      calibrating = false;
      calibrated = true;
    }
    set_write_to_eeprom = true;  // setting own setter!
    inited = true;
    calibrated = true;
  }

  // write to EEPROM:
  if (set_write_to_eeprom) {
    set_write_to_eeprom = false;
    EEPROM.put(MAG_CALIBRATION_EEPROM_ADDR_MAX_X, x_max);
    EEPROM.put(MAG_CALIBRATION_EEPROM_ADDR_MIN_X, x_min);
    EEPROM.put(MAG_CALIBRATION_EEPROM_ADDR_MAX_Y, y_max);
    EEPROM.put(MAG_CALIBRATION_EEPROM_ADDR_MIN_Y, y_min);
    EEPROM.put(MAG_CALIBRATION_EEPROM_ADDR_MAX_Z, z_max);
    EEPROM.put(MAG_CALIBRATION_EEPROM_ADDR_MIN_Z, z_min);
  }


  // only do anything else while calibrating:
  if (! calibrating) return;

  // find min and max values for every axes:

  if (magnetometer->m_x < x_min) {
    x_min = magnetometer->m_x;
    just_updated = true;
  }
  if (magnetometer->m_x > x_max) {
      x_max = magnetometer->m_x;
      just_updated = true;
  }

  if (magnetometer->m_y < y_min) {
      y_min = magnetometer->m_y;
      just_updated = true;
  }
  if (magnetometer->m_y > y_max) {
      y_max = magnetometer->m_y;
      just_updated = true;
  }

  if (magnetometer->m_z < z_min) {
      z_min = magnetometer->m_z;
      just_updated = true;
  }
  if (magnetometer->m_z > z_max) {
      z_max = magnetometer->m_z;
      just_updated = true;
  }

  // store ranges and zero points, for convenience:

  x_range = x_max - x_min;
  y_range = y_max - y_min;
  z_range = z_max - z_min;

  x_zero = (x_max + x_min) / 2.0;
  y_zero = (y_max + y_min) / 2.0;
  z_zero = (z_max + z_min) / 2.0;

  if (just_updated) {
    Serial.print(F("Cal update: ("));
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
