#include <Arduino.h>
#include "modules.hpp"


#ifndef TARGET_HPP
#define TARGET_HPP


#include <EEPROM.h>
#include "utils.h"


#ifndef TARGET_EEPROM_ADDR_BASE
  #define TARGET_EEPROM_ADDR_BASE 100
#endif
#define TARGET_EEPROM_LAT (TARGET_EEPROM_ADDR_BASE + 4 * 1)
#define TARGET_EEPROM_LON (TARGET_EEPROM_ADDR_BASE + 4 * 2)
#define TARGET_EEPROM_ZONE (TARGET_EEPROM_ADDR_BASE + 4 * 3)


#define TARGET_NULL_ANGLE_VALUE -500.0
#define TARGET_NULL_ANGLE_EPSILON 1.0
#define TARGET_NULL_METERS_VALUE -500.0
#define TARGET_NULL_METERS_EPSILON 0.1
#define TARGET_EARTH_CIRCUMFERRENCE (6371009 * 2 * M_PI)


class Target: public Module
{
private:
  double _lat = 0.0;
  double _lon = 0.0;
  double _radius = 0.0;

public:
  double lat = 0.0;                                     // current positon, distance from the Equator, negative for S  (radians)
  double lon = 0.0;                                     // cirrent position, distance from the Prime Meridian, negative for W  (radians)
  double radius = 10.0;                                 // radius around target coords that is considered to be "on target" (meters)
  double setLat = TARGET_NULL_ANGLE_VALUE;              // target latitude (radians)
  double setLon = TARGET_NULL_ANGLE_VALUE;              // target longitude (radians)
  double setRaduis = TARGET_NULL_METERS_VALUE;          // radious around target coords that is considered "on target" (meters)
  double deltaAzimuth = 0.0;                            // angle to target  (radians)
  double distance = 0.0;                                // distance to target (meters)
  bool onTarget = false;                                // position within targetRadius
  bool inited = false;
  void setup();
  void loop();
};

Target* target = (Target*) ModulesRegistry::add(new Target());

#endif  // #ifndef TARGET_HPP
