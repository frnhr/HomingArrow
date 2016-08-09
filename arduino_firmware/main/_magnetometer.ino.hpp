#include <Arduino.h>
#include "modules.hpp"
#include "hardware_config.h"

#include "_magnetometer.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef MAGNETIMETER_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define MAGNETIMETER_INO_HPP


void Magnetometer::setup()
{
    /* Initialise the sensor */
    if(!sensor.begin()) {
        /* There was a problem detecting the HMC5883 ... check your connections */
        Serial.print(F("No LS303 detected!\n"));
        Serial.flush();
        while(1);
    }
}


void Magnetometer::loop()
{

  // don't read compass while motor is running, because of possible magnetic interference:
  #ifdef MOTOR_H
  if (motor.running) return;
  #endif

  uint16_t now = millis();

  // don't read too often, magnetometer might stall:
  if (now - last_read_millis < MAGNETOMETER_READ_INTERVAL) return;
  last_read_millis = now;


  // set "inited" flag:
  inited = true;

  // get new sensor data:
  sensor.read();

  // store values to module fields, for convenient access:
  m_x = sensor.magData.x;
  m_y = sensor.magData.y;
  m_z = sensor.magData.z;
  a_x = sensor.accelData.x;
  a_y = sensor.accelData.y;
  a_z = sensor.accelData.z;

  // debug output:

  Serial.print(a_x);
  Serial.print("\t");
  Serial.print(a_y);
  Serial.print("\t");
  Serial.print(a_z);
  Serial.print("\t");
  Serial.print("\n");

}
