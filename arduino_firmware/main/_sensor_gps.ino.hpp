#include <Arduino.h>
#include "modules.hpp"


// Unlike header file (.hpp), module implementation file (.ino.hpp) must not be included multiple times:
#ifdef SENSOR_GPS_INO_HPP
#error The .ino.hpp file of a module can be included only once (and should be included from main.ino). Did you wanted to include the .hpp file instead?
#endif
#define SENSOR_GPS_INO_HPP
#include "_sensor_gps.hpp"


#ifndef LOCATION_HPP
  #warning sensor_gps module compiled without location module
#endif


void SensorGps::setup()
{

    _sensor->begin(SENSOR_GPS_BAUD_RATE);

    // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
    //_gps.sensor.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

    // uncomment this line to turn on only the "minimum recommended" data
    _sensor->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
    // the parser doesn't care about other sentences at this time

    // Set the update rate
    _sensor->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
    // For the parsing code to work nicely and have time to sort thru the data, and
    // print it out we don't suggest using anything higher than 1 Hz

    // Request updates on antenna status, comment out to keep quiet
    _sensor->sendCommand(PGCMD_ANTENNA);

    // the nice thing about this code is you can have a timer0 interrupt go off
    // every 1 millisecond, and read data from the GPS for you. that makes the
    // loop code a heck of a lot easier!

    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  // TODO make _sensor private, make handler method:
  char c = sensor_gps->_sensor->read();
  // if you want to debug, this is a good time to do it!
  #ifdef UDR0
    if (SENSOR_GPS_ECHO)
      if (c) UDR0 = c;
      // writing direct to UDR0 is much much faster than Serial.print
      // but only one character can be written at a time.
  #endif
}


void SensorGps::loop()
{
  // assume there is new data:
  bool got_new_data = true;

  /*** READ SENSOR DATA ***/

  // received data from GPS:
  if (!_sensor->newNMEAreceived())
    got_new_data = false;

  // succesfully parsed the data:
  if (!_sensor->parse(_sensor->lastNMEA()))
    got_new_data = false;

  // have GPS satellite fix:
  if (!_sensor->fix)
    got_new_data = false;

  // publish that module is now inited:
  if (got_new_data)
    inited = true;

  // if we have fix, update (otherwize work with old data)
  // TODO perhaps implement a timeout on the old data?
  if (_sensor->fix) {
      // we work with radians...
      #ifdef LOCATION_HPP
        location->setLat = deg2rad(_sensor->latitudeDegrees);
        location->setLon = deg2rad(_sensor->longitudeDegrees);
      #else
      if (!inited) {
          Serial.print(F("WARNING: sensor_gps module compiled without location module, discarding this data:\n    "));
          Serial.print(_sensor->latitudeDegrees);
          Serial.print(F(", "));
          Serial.print(_sensor->longitudeDegrees);
          Serial.print(F("\n    Future warnings will be silenced.\n"));
        }
      #endif

  }

  // Publish fix
  if (!inited) {
    inited = _sensor->fix;
  }
  fix = _sensor->fix;

}
