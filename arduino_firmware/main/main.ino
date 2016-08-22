
// Code for Wireless Sensor Modules
// main.ino
// -*- mode: C++ -*-



#define DEVICE_NAME "HomingArrow"
#define DEVICE_VERSION "2.0.0-alpha.1"


#define RAM_USAGE_AUTO_PRINT false
#define RAM_MEASUREMENTS_N 3

#include "hardware_options.h"
#define HARDWARE HARDWARE_1284
#include "hardware_config.h"

#define MODULE_MAX_N 30
#include "modules.hpp"

#include "_motor.ino.hpp"
#include "_blink.ino.hpp"

#include "_ram_usage.ino.hpp"
#include "_location.ino.hpp"
#include "_arrow.ino.hpp"

#include "_magnetometer.ino.hpp"
#include "_accelerometer.ino.hpp"

#include "_sensor_mag_acc.ino.hpp"
#include "_sensor_encoder.ino.hpp"
#include "_sensor_gps.ino.hpp"

#include "_mag_calibration.ino.hpp"
#include "_acc_calibration.ino.hpp"
#include "_declination.ino.hpp"

#include "_compass.ino.hpp"

#include "_target.ino.hpp"
#include "_intel.ino.hpp"


#include "_protocol.ino.hpp"
#include "_serial_comm.ino.hpp"



void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);  //TODO better handle debugging
  // Call setup() for every module:
  unsigned int i;
  for (i = 0; i < ModulesRegistry::count; i++) {
    ModulesRegistry::modules[i]->setup();
  }
  Serial.println(F("ready"));
}


void loop()
{
  //Serial.println("LOOP start");

  // Call loop() for every module:
  unsigned int i;
  for (i = 0; i < ModulesRegistry::count; i++) {
    // Serial.print("LOOP ");
    // Serial.println(i);
    ModulesRegistry::modules[i]->loop();
  }
  // Serial.println("LOOP end");
}
