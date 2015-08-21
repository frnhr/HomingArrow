#include "gps.h"

void gps_setup()
{
    _gps.buffer.reserve(100);

    _gps.sensor.begin(GPS_BAUD_RATE);

    // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
    //_gps.sensor.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    // uncomment this line to turn on only the "minimum recommended" data
    _gps.sensor.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
    // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
    // the parser doesn't care about other sentences at this time

    // Set the update rate
    _gps.sensor.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
    // For the parsing code to work nicely and have time to sort thru the data, and
    // print it out we don't suggest using anything higher than 1 Hz

    // Request updates on antenna status, comment out to keep quiet
    _gps.sensor.sendCommand(PGCMD_ANTENNA);

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
  char c = _gps.sensor.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPS_ECHO)
    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif
}


void gps_loop()
{

    if (!_gps.sensor.newNMEAreceived()) return;
    if (!_gps.sensor.parse(_gps.sensor.lastNMEA())) return;
        
    if (!gps.inited && _gps.sensor.fix) {
        gps.inited = true;
    }

    if (_gps.sensor.fix) {
        gps.current_lat = deg2rad(_gps.sensor.latitudeDegrees);
        gps.current_lon = deg2rad(_gps.sensor.longitudeDegrees);
    }

    // calculate azimuth and distance
    if (gps.inited) {
        gps.azimuth = map_to_circle_rad(M_PI / 2 - atan2(
            gps.target_lat - gps.current_lat,
            gps.target_lon - gps.current_lon
        ));

        // Flat Earth approximation (ok because we only ever use distance for determining if on-target)
        gps.distance = sqrt(
            pow((gps.target_lat - gps.current_lat) * GPS_EARTH_CIRCUMFERRENCE /  2 / M_PI, 2) 
            +
            pow((gps.target_lon - gps.current_lon) * GPS_EARTH_CIRCUMFERRENCE /  2 / M_PI * cos(gps.current_lat), 2)
        );

        // is target reached:
        gps.on_target = gps.distance < gps.target_zone;
    }
}
