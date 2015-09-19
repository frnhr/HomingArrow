#include "gps.h"

void gps_setup()
{

    EEPROM.get(GPS_EEPROM_ADDR_LAT, gps.target_lat);
    EEPROM.get(GPS_EEPROM_ADDR_LON, gps.target_lon);
    EEPROM.get(GPS_EEPROM_ADDR_ZONE, gps.target_zone);

    gps.set_target_lat = gps.target_lat;
    gps.set_target_lon = gps.target_lon;
    _gps.last_target_lat = gps.target_lat;
    _gps.last_target_lon = gps.target_lon;
    _gps.target_zone = gps.target_zone;

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
    /*** read set_target command ***/
    if (gps.set_target_lat != _gps.last_target_lat || gps.set_target_lon != _gps.last_target_lon) {
        _gps.last_target_lat = gps.set_target_lat;
        _gps.last_target_lon = gps.set_target_lon;
        gps.target_lat = gps.set_target_lat;
        gps.target_lon = gps.set_target_lon;
        EEPROM.put(GPS_EEPROM_ADDR_LAT, gps.set_target_lat);
        EEPROM.put(GPS_EEPROM_ADDR_LON, gps.set_target_lon);
    }

    /*** handle set_zone command ***/
    if (gps.target_zone != _gps.target_zone) {
        _gps.target_zone = gps.target_zone;
        EEPROM.put(GPS_EEPROM_ADDR_ZONE, gps.target_zone);
    }

////////// TEMP ///////////
/*
gps.current_lat = deg2rad(45.29866);
gps.current_lon = deg2rad(13.625536);
gps.inited = true;
*/

    /*** GPS boilerplate ***/
    
    // received data from GPS:
    if (!_gps.sensor.newNMEAreceived()) return;

    // succesfully parsed the data:
    if (!_gps.sensor.parse(_gps.sensor.lastNMEA())) return;

    // have GPS satellite fix:
    if ((!gps.inited) && (!_gps.sensor.fix)) return;
        
    // publish that module is now inited:
    if (!gps.inited) gps.inited = true;

    // if we have fix, update (otherwize work with old data)
    // TODO perhaps implement a timeout on the old data?
    if (_gps.sensor.fix) {
        // we work with radians...
        gps.current_lat = deg2rad(_gps.sensor.latitudeDegrees);
        gps.current_lon = deg2rad(_gps.sensor.longitudeDegrees);
    }

    /*** Calculate Stuff ***/

    gps.azimuth = map_to_circle_rad(M_PI / 2 - atan2(
        gps.target_lat - gps.current_lat,
        cos(gps.target_lat) * (gps.target_lon - gps.current_lon)
    ));

    // Flat Earth approximation
    // it's ok because we only ever use distance for determining if on-target
    gps.distance = sqrt(
        pow((gps.target_lat - gps.current_lat) * GPS_EARTH_CIRCUMFERRENCE / 2.0 / M_PI, 2) 
        +
        pow((gps.target_lon - gps.current_lon) * GPS_EARTH_CIRCUMFERRENCE / 2.0 / M_PI * cos(gps.current_lat), 2)
    );

    // Check if Target Reached
    gps.on_target = gps.distance < _gps.target_zone;

    // Publish fix
    gps.fix = _gps.sensor.fix;
//gps.fix = true; 

}
