#include <Arduino.h>
#include "modules.hpp"


#ifndef LOCATION_HPP
#define LOCATION_HPP


#include "utils.h"


#define LOCATION_NULL_ANGLE_VALUE -500.0
#define LOCATION_NULL_ANGLE_EPSILON 1.0


class Location: public Module
{
private:
  double _lat = LOCATION_NULL_ANGLE_VALUE;
  double _lon = LOCATION_NULL_ANGLE_VALUE;

public:
  double setLat = LOCATION_NULL_ANGLE_VALUE;
  double setLon = LOCATION_NULL_ANGLE_VALUE;
  double lat = 0.0;
  double lon = 0.0;
  bool inited = false;
  void setup();
  void loop();
};

Location* location = (Location*) ModulesRegistry::add(new Location());

#endif  // #ifndef LOCATION_HPP
