#include <Arduino.h>
#include "modules.hpp"
#include "hardware_config.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>


#ifndef MAGNETOMETER_HPP
#define MAGNETOMETER_HPP

#define MAGNETOMETER_READ_INTERVAL 50


class Magnetometer: public Module
{
private:
  Adafruit_LSM303 sensor;  // library object, implements serial
  uint32_t last_read_millis = 0;
public:
  int16_t m_x = 0;
  int16_t m_y = 0;
  int16_t m_z = 0;
  int16_t a_x = 0;
  int16_t a_y = 0;
  int16_t a_z = 0;
  bool inited = false;
  void setup();
  void loop();
  Magnetometer(){};
};

Magnetometer* magnetometer = (Magnetometer*) ModulesRegistry::add(new Magnetometer());

#endif  // #ifndef MAGNETOMETER_HPP
