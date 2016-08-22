#include <Arduino.h>
#include "modules.hpp"
#include "_target.hpp"


// Unlike header file (.hpp), module implementation file (.ino.h) must not be included multiple times:
#ifdef TARGET_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .h file instead?
#endif
#define TARGET_INO_HPP


#include "_compass.hpp"
#include "_location.hpp"


void Target::setup()
{

    EEPROM.get(TARGET_EEPROM_LAT, _lat);
    EEPROM.get(TARGET_EEPROM_LON, _lon);
    EEPROM.get(TARGET_EEPROM_ZONE, _radius);
}


void Target::loop()
{
    // read setters:
    if (isSett(setLat, TARGET_NULL_ANGLE_VALUE, TARGET_NULL_ANGLE_EPSILON)) {
        _lat = setLat;
        EEPROM.put(TARGET_EEPROM_LAT, setLat);
        setLat = TARGET_NULL_ANGLE_VALUE;
    }
    if (isSett(setLon, TARGET_NULL_ANGLE_VALUE, TARGET_NULL_ANGLE_EPSILON)) {
        _lon = setLon;
        EEPROM.put(TARGET_EEPROM_LON, setLon);
        setLon = TARGET_NULL_ANGLE_VALUE;
    }
    if (isSett(setRaduis, TARGET_NULL_METERS_VALUE, TARGET_NULL_METERS_EPSILON)) {
        _radius = setRaduis;
        EEPROM.put(TARGET_EEPROM_ZONE, setRaduis);
        setRaduis = TARGET_NULL_METERS_VALUE;
    }


    // update public getters:
    lat = _lat;
    lon = _lon;
    radius = _radius;


    // calculate the remaining getters:

    deltaAzimuth = map_to_half_circle_rad(
      atan2(_lat - location->lat,
            _lon - location->lon
      ) - compass->azimuth
    );

    // Flat Earth approximation:
    // (ok because we only ever use distance for determining if on-target)
    distance = sqrt(
        pow((_lat - location->lat) * TARGET_EARTH_CIRCUMFERRENCE / 2.0 / M_PI, 2)
        +
        pow((_lon - location->lon) * TARGET_EARTH_CIRCUMFERRENCE / 2.0 / M_PI * cos(location->lat), 2)
    );
    onTarget = distance < _radius;
}
