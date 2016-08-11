
// Code for Wireless Sensor Modules
// main.ino
// -*- mode: C++ -*-


#define RAM_USAGE_AUTO_PRINT false
#define RAM_MEASUREMENTS_N 3

#include "hardware_options.h"
#define HARDWARE HARDWARE_1284
#include "hardware_config.h"

#define MODULE_MAX_N 15
#include "modules.hpp"

#include "_ram_usage.ino.hpp"

#include "_blink.ino.hpp"
#include "_encoder.ino.hpp"
#include "_magnetometer.ino.hpp"
#include "_mag_calibration.ino.hpp"

#include "_compass.ino.hpp"

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
