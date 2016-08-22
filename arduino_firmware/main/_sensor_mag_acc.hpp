#include <Arduino.h>
#include "modules.hpp"


#ifndef SENSOR_MAG_ACC_HPP
#define SENSOR_MAG_ACC_HPP


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>


#define SENSOR_MAG_ACC_HPP_READ_INTERVAL 50


class SensorMagAcc: public Module
{
private:
  Adafruit_LSM303 sensor;  // library object, implements serial
  uint32_t last_read_millis = 0;
public:
  bool connected = false;
  bool inited = false;
  void setup();
  void loop();
};

SensorMagAcc* sensor_mag_acc = (SensorMagAcc*) ModulesRegistry::add(new SensorMagAcc());

#endif  // #ifndef MAGNETOMETER_HPP
