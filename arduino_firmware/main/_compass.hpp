#include <Arduino.h>
#include "modules.hpp"


#ifndef COMPASS_HPP
#define COMPASS_HPP


#include <math.h>
#include "utils.h"
#include "_magnetometer.hpp"
#include "_accelerometer.hpp"
#include "_mag_calibration.hpp"
#include "_acc_calibration.hpp"


#define COMPASS_LOOP_INTERVAL 500  // millis

#define COMPASS_MAGNETIC_DECLINATION 0.0  // used if declination module is missing

#define COMPASS_AVERAGE_BUFFER 1

#define COMPASS_UNCALIBRATED_MAX 1050;

#ifndef COMPASS_EEPROM_ADDR
  #define COMPASS_EEPROM_ADDR 20
#endif

#define COMPASS_EEPROM_ADDR_SIGNATURE COMPASS_EEPROM_ADDR
#define COMPASS_EEPROM_OFFSET (COMPASS_EEPROM_ADDR + 1)

#define COMPASS_NULL_VALUE -500.0
#define COMPASS_NULL_EPSILON 0.1


class Compass: public Module
{
private:
  double phi = 0.0;        // roll
  double theta = 0.0;      // pitch
  double alpha = deg2rad(COMPASS_MAGNETIC_DECLINATION);
  double delta = 0.0;      // magnetic dip
  double psi = 0.0;        // yaw
  long B = 0;              // magnetic vector modulus
  double Dx = 0.0;         // shortcut
  double Dy = 0.0;         // shortcut
  double average[COMPASS_AVERAGE_BUFFER];
  int16_t average_i = 0;
  uint16_t last_loop = 0;
  double _offset = 0.0;

public:
  bool inited = false;    // device is ready
  double azimuth = 0.0;   // angle away from the north to the east
  double setOffset = COMPASS_NULL_VALUE;
  double offset = 0.0;
  void setup();
  void loop();
};

Compass* compass = (Compass*) ModulesRegistry::add(new Compass());

#endif  // #ifndef COMPASS_HPP
