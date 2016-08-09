#include <Arduino.h>
#include "modules.hpp"
#include "hardware_config.h"

#include <math.h>
#include "motor.h"
#include "utils.h"


#ifndef COMPASS_HPP
#define COMPASS_HPP


#define COMPASS_LOOP_INTERVAL 500  // millis


// Local compass error due to difference between geographic and magnetic North pole.
#define COMPASS_MAGNETIC_DECLINATION 3.2  // In degrees, see: http://www.magnetic-declination.com/

#define COMPASS_AVERAGE_BUFFER 1

#define COMPASS_UNCALIBRATED_MAX 1050;
#define COMPASS_RESOLUTION 1024

#ifndef COMPASS_EEPROM_ADDR
#define COMPASS_EEPROM_ADDR 20
#endif

#define COMPASS_EEPROM_ADDR_SIGNATURE COMPASS_EEPROM_ADDR
#define COMPASS_EEPROM_ADDR_CAL_X COMPASS_EEPROM_ADDR + 1

class Compass: public Module
{
private:
  double phi = 0.0;        // roll
  double theta = 0.0;      // pitch
  double alpha = deg2rad(COMPASS_MAGNETIC_DECLINATION);
  double delta = 0.0;      // magnetic dip
  double psi = 0.0;        // yaw
  long B = 0;              // magnetic vector module
  double Dx = 0.0;         // shortcut
  double Dy = 0.0;         // shortcut
  double average[COMPASS_AVERAGE_BUFFER];
  int16_t average_i = 0;
  int16_t cal_x = 0;
  int16_t cal_y = 0;
  int16_t cal_z = 0;
  uint16_t last_loop = 0;

public:
  double azimuth = 0.0;   // angle away from the north to the east
  bool inited = false;    // device is ready
  bool calibration = false;  // initiate_calibration
  void setup();
  void loop();
  Compass(){};
};

Compass* compass = (Compass*) ModulesRegistry::add(new Compass());

#endif  // #ifndef COMPASS_HPP
