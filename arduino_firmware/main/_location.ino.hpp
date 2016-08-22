#include <Arduino.h>
#include "modules.hpp"


#ifdef LOCATION_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define LOCATION_INO_HPP

#include "_location.hpp"


void Location::setup()
{
  // TODO add a home location feature?
  /* possible story:
      Every N minues write current location to EEPROM
      On boot use that location while waiting for GPS fix
    alternatice story:
      Always assume the same home location on boot, and use that location.
      This is basically the same as first story, except that it whites to
      EEPROM only on command (via protocol) rather then every N seconds.
  */
}


void Location::loop()
{
  // handle setters:
  if (isSett(setLat, LOCATION_NULL_ANGLE_VALUE, LOCATION_NULL_ANGLE_EPSILON)) {
    _lat = setLat;
  }
  if (isSett(setLon, LOCATION_NULL_ANGLE_VALUE, LOCATION_NULL_ANGLE_EPSILON)) {
    _lon = setLon;
  }

  // update public getters:
  lat = _lat;
  lon = _lon;

  // raise inited flag:
  if (!inited
      && isSett(_lat, LOCATION_NULL_ANGLE_VALUE, LOCATION_NULL_ANGLE_EPSILON)
      && isSett(_lon, LOCATION_NULL_ANGLE_VALUE, LOCATION_NULL_ANGLE_EPSILON)) {
    inited = true;
  }
}
