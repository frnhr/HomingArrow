#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef SENSOR_MAG_ACC_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define SENSOR_MAG_ACC_INO_HPP
#include "_sensor_mag_acc.hpp"


#ifndef MAGNETOMETER_HPP
  #warning sensor_mag_acc module compiled without magnetometer module
#endif
#ifndef ACCELEROMETER_HPP
  #warning sensor_mag_acc module compiled without accelerometer module
#endif
// need motor module because this sensor should not take readingsa while motor is running:
#ifndef MOTOR_HPP
  #warning sensor_mag_acc module compiled without motor module
#endif


void SensorMagAcc::setup()
{
    /* Initialise the sensor */
    if(!sensor.begin()) {
        /* There was a problem detecting the HMC5883 ... check your connections */
        Serial.print(F("WARNING: sensor_mag_acc: No LS303 detected!\n"));
    } else {
      connected = true;
    }

    #ifndef MAGNETOMETER_HPP
      Serial.print(F("WARNING: sensor_mag_acc module compiled without magnetometer module, data will be discarded!\n"));
    #endif
    #ifndef ACCELEROMETER_HPP
      Serial.print(F("WARNING: sensor_mag_acc module compiled without accelerometer module, data will be discarded!\n"));
    #endif
    #ifndef MOTOR_H
      Serial.print(F("WARNING: sensor_mag_acc module compiled without motor module!\n"));
    #endif


}


void SensorMagAcc::loop()
{

  if (!connected) return;

  // don't read the seonsor while motor is running, because of possible magnetic interference:
  #ifdef MOTOR_H
    if (motor.running) return;
  #endif

  uint16_t now = millis();

  // don't read too often, magnetometer might stall:
  if (now - last_read_millis < SENSOR_MAG_ACC_HPP_READ_INTERVAL) return;
  last_read_millis = now;


  // set "inited" flag:
  inited = true;

  // get new sensor data:
  sensor.read();

  // store values to module fields, for convenient access:
  // ... magnetometer data:
  #ifdef MAGNETOMETER_HPP
    magnetometer->setX = sensor.magData.x;
    magnetometer->setY = sensor.magData.z;
    magnetometer->setZ = sensor.magData.z;
  #endif
  // ... accelerometer data:
  #ifdef ACCELEROMETER_HPP
    accelerometer->setX = sensor.accelData.x;
    accelerometer->setY = sensor.accelData.y;
    accelerometer->setZ = sensor.accelData.z;
  #endif

  // debug output:
  /*
  Serial.print(a_x);
  Serial.print("\t");
  Serial.print(a_y);
  Serial.print("\t");
  Serial.print(a_z);
  Serial.print("\t");
  Serial.print("\n");
  */
}
